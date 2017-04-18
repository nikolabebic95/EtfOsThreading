#ifndef _etfosthreading_thread_h_
#define _etfosthreading_thread_h_

#include <thread> // thread

namespace etfosthreading {

	/**
	 * \brief Class implementing the Thread
	 * \details Threads exist in standard C++, but on ETF in OS
	 *          classes, the teachers use a java-like interface.
	 *          The purpose of this class is to provide that kind
	 *          of interface, and help solve various school problems
	 *          
	 * \author Nikola Bebic
	 * \version 1.0.0.0.
	 * \date 18-Apr-2017
	 * \copyright MIT Licence
	 */
	class Thread {
	public:

		/**
		 * \brief Starts the Thread
		 */
		void start();

		/**
		 * \brief Waits for the thread to end
		 */
		void waitToComplete();

		/**
		 * \brief Destroys the thread
		 */
		virtual ~Thread();

	protected:
		/**
		 * \brief The body of the thread
		 * \details This method should be overriden in all user threads
		 */
		virtual void run() = 0;

	private:
		std::thread thread_;

		static void threadStarter(Thread *);
	};
}

#endif
