#include <cstdlib>
#include <time.h>

namespace osthreadingtest {
	void testSemaphores();
	void testThreads();
	void testBoundedBuffer();
	void testRegion();
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	
	osthreadingtest::testSemaphores();
	osthreadingtest::testThreads();
	osthreadingtest::testBoundedBuffer();
	osthreadingtest::testRegion();
}
