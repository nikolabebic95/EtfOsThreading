#include "Semaphore.h"
#include <iostream>
#include <thread>

namespace osthreadingtest {
	const size_t NUM_OF_ITERATIONS = 10;

	etfosthreading::Semaphore s1(1);
	etfosthreading::Semaphore s2(0);

	void f1() {
		for (auto i = 0; i < NUM_OF_ITERATIONS; i++) {
			s1.wait();
			std::cout << "Thread 1" << std::endl;
			s2.signal();
		}
	}

	void f2() {
		for (auto i = 0; i < NUM_OF_ITERATIONS; i++) {
			s2.wait();
			std::cout << "Thread 2" << std::endl;
			s1.signal();
		}
	}

	void testSemaphores() {
		std::thread t1(f1);
		std::thread t2(f2);

		t1.join();
		t2.join();
	}
}
