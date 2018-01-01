#include "Semaphore.h"

namespace etfosthreading {

	Semaphore::Semaphore(int value) : value_(value) {}

	void Semaphore::signal() {
		std::unique_lock<std::mutex> lock(mtx_);
		value_++;
		cv_.notify_one();
	}

	void Semaphore::wait() {
		std::unique_lock<std::mutex> lock(mtx_);

		while (value_ == 0) {
			cv_.wait(lock);
		}

		value_--;
	}

}