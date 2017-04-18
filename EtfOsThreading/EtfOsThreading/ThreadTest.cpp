#include "Thread.h"
#include <iostream>

namespace osthreadingtest {
	class Child : public etfosthreading::Thread {
	public:
		explicit Child(int count) {
			count_ = count;
		}

		int result() const {
			return result_;
		}
	protected:
		void run() override {
			for (auto i = 0; i < count_; i++) {
				result_ += i;
			}
		}
	private:
		int count_;
		int result_ = 0;
	};

	void testThreads() {
		Child child_thread(100);
		child_thread.start();
		child_thread.waitToComplete();
		std::cout << child_thread.result() << std::endl;
	}
}