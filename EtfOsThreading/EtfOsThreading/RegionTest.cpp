#include "Region.h"
#include <mutex>
#include <iostream>

namespace osthreadingtest {

	static std::mutex mutex;

	static const size_t NUM_OF_THREADS_REGION_TEST = 5;

	static void unsynchronizedThread(int i) {
		std::cout << "Unsynchronized" << " " << "output" << " " << i << std::endl;
	}

	static void synchronizedThread(int i) {
		region (mutex) {
			std::cout << "Synchronized" << " " << "output" << " " << i << std::endl;
		}
	}

	void testRegion() {
		std::thread threads[NUM_OF_THREADS_REGION_TEST];
		for (auto i = 0; i < NUM_OF_THREADS_REGION_TEST; i++) {
			threads[i] = std::thread(unsynchronizedThread, i);
		}

		for (auto i = 0; i < NUM_OF_THREADS_REGION_TEST; i++) {
			threads[i].join();
		}

		for (auto i = 0; i < NUM_OF_THREADS_REGION_TEST; i++) {
			threads[i] = std::thread(synchronizedThread, i);
		}

		for (auto i = 0; i < NUM_OF_THREADS_REGION_TEST; i++) {
			threads[i].join();
		}
	}
}
