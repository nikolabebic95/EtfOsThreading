#include "Thread.h"

namespace etfosthreading {

	void Thread::start() {
		thread_ = std::thread(threadStarter, this);
	}

	void Thread::waitToComplete() {
		thread_.join();
	}

	Thread::~Thread() {}

	void Thread::threadStarter(Thread *thread) {
		thread->run();
	}

}