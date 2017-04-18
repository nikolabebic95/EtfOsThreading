#ifndef _etfosthreading_semaphore_h_
#define _etfosthreading_semaphore_h_

#include <mutex> // mutex, unique_lock, condition_variable

namespace etfosthreading {

	/**
	* \brief Class implementing the Semaphore
	* \details Semaphores do not exist in standard C++, but they
	*          are easily implemented, and can be used in various
	*          school problems.
	*
	* \author Nikola Bebic
	* \version 1.0.0.0.
	* \date 18-Apr-2017
	* \copyright MIT Licence
	*/
	class Semaphore {
	public:

		/**
		* \brief Initialize the semaphore
		* \param value Initial value of the semaphore
		*/
		explicit Semaphore(int value = 0);

		/**
		* \brief Signal on semaphore
		*/
		void signal();

		/**
		* brief Wait on semaphore
		*/
		void wait();

	private:
		std::mutex mtx_;
		std::condition_variable cv_;
		int value_;
	};
}

#endif
