#ifndef _etfosthreading_boundedbuffer_h_
#define _etfosthreading_boundedbuffer_h_

#include "Semaphore.h" // Semaphore
#include <mutex> // mutex

namespace etfosthreading {

	/**
	* \brief Class implementing the Bounded Buffer
	* \details Bounded Buffers are a common syncronization
	*          problem. They are typically solved using semaphores,
	*          and they can be used in various other threading
	*          problems. This implementation uses semaphores
	*          from this library, and mutexes from the standard
	*          C++ library.
	*
	* \author Nikola Bebic
	* \version 1.0.0.0.
	* \date 23-Apr-2017
	* \copyright MIT Licence
	*/
	template <typename T> class BoundedBuffer {
	public:

		/**
		 * \brief Initialize the buffer
		 * \param capacity Size of the buffer
		 */
		explicit BoundedBuffer(int capacity);

		/**
		 * \brief Destroy the buffer
		 */
		~BoundedBuffer();

		/**
		 * \brief Get one item from the buffer
		 * \details Gets the item that was put into the buffer the
		 *          earliest. Removes that item. If
		 *          there is nothing in the buffer, blocks the caller
		 *          thread until at least one item is put into the buffer
		 *          
		 * \return Item at the front of the buffer
		 */
		T get();

		/**
		 * \brief Put one item into the buffer
		 * \details Puts the item at the back of the buffer. If there
		 *          is no more space in the buffer, blocks the caller
		 *          thread until at least one item is removed from the buffer
		 *          
		 * \param element An item that should be put into the buffer
		 */
		void put(T element);

		/**
		 * \brief Gets a block of data from the buffer
		 * \details Gets a continous block of data from the buffer.
		 *          If there is notning in the buffer, blocks the caller
		 *          thread until at least one item is put into the buffer.
		 *          Another thread can't get anytning from the buffer while
		 *          one block of data is read
		 *          
		 * \param buff Pointer to block where the data should be written
		 * \param size Size of the block
		 */
		void get(T *buff, size_t size);

		/**
		 * \brief Puts a block of data into the buffer
		 * \details Puts a continous block of data to the back of the buffer.
		 *          If there is no more space in the buffer, block the caller 
		 *          thread until at least one item is removed from the buffer.
		 *          Another thread can't put anything into the buffer while
		 *          one block of data is put
		 *          
		 * \param buff Pointer to block from where the data should be read
		 * \param size Size of the block
		 */
		void put(T *buff, size_t size);

	private:
		/**
		 * \brief Internal implementation of the putting into the buffer
		 * \param element Element that is put into the buffer
		 */
		void putElement(T element);

		/**
		 * \brief Internal implementation of the getting from the buffer
		 * \return Element that was get from the buffer
		 */
		T getElement();

		BoundedBuffer(BoundedBuffer<T> &) = delete;
		void operator=(BoundedBuffer<T> &) = delete;

		Semaphore space_available_;
		Semaphore item_available_;
		std::mutex mutex_get_;
		std::mutex mutex_put_;
		int capacity_;
		T *array_;
		int first_ = 0;
		int last_ = 0;
	};

	template <typename T> BoundedBuffer<T>::BoundedBuffer(int capacity): space_available_(capacity), capacity_(capacity) {
		array_ = new T[capacity];
	}

	template <typename T> BoundedBuffer<T>::~BoundedBuffer() {
		delete[] array_;
	}

	template<typename T> T BoundedBuffer<T>::get() {
		mutex_get_.lock();

		T e = getElement();

		mutex_get_.unlock();
		return e;
	}

	template <typename T> void BoundedBuffer<T>::put(T element) {
		mutex_put_.lock();

		putElement(element);

		mutex_put_.unlock();
	}

	template <typename T> void BoundedBuffer<T>::get(T *buff, size_t size) {
		mutex_get_.lock();

		for (size_t i = 0; i < size; i++)
			buff[i] = getElement();

		mutex_get_.unlock();
	}

	template <typename T> void BoundedBuffer<T>::put(T *buff, size_t size) {
		mutex_put_.lock();

		for (size_t i = 0; i < size; i++) {
			putElement(buff[i]);
		}

		mutex_put_.unlock();
	}

	template <typename T> void BoundedBuffer<T>::putElement(T element) {
		space_available_.wait();

		array_[last_] = element;
		last_ = (last_ + 1) % capacity_;

		item_available_.signal();
	}

	template <typename T> T BoundedBuffer<T>::getElement() {
		item_available_.wait();

		T ret = array_[first_];
		first_ = (first_ + 1) % capacity_;

		space_available_.signal();
		return ret;
	}
}

#endif
