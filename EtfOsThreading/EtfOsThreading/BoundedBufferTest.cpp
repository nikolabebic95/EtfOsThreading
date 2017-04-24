#include "BoundedBuffer.h"
#include "mutex"
#include <iostream>
#include <cstdlib>

namespace osthreadingtest {

	static const size_t BUFFER_SIZE = 15;

	static const size_t NUM_OF_ITEMS = 100;

	static const size_t NUM_OF_BLOCKS = 10;
	static const size_t BLOCK_SIZE = 10;

	static const auto SLEEP_TIME_SINGLE_ELEMENT_LOWER = 10;
	static const auto SLEEP_TIME_SINGLE_ELEMENT_UPPER = 50;

	static const auto SLEEP_TIME_BUFFER_LOWER = SLEEP_TIME_SINGLE_ELEMENT_LOWER * 10;
	static const auto SLEEP_TIME_BUFFER_UPPER = SLEEP_TIME_SINGLE_ELEMENT_UPPER * 10;

	etfosthreading::BoundedBuffer<int> buffer(BUFFER_SIZE);

	std::mutex output_mutex;

	int randomInt(int lower, int upper) {
		return static_cast<int>(rand() / (static_cast<double>(RAND_MAX) + 1)) * (upper - lower + 1) + lower;
	}

	void write(int element) {
		output_mutex.lock();
		std::cout << element << std::endl;
		output_mutex.unlock();
	}

	void write(int block[], size_t size) {
		output_mutex.lock();
		for (size_t i = 0; i < size; i++) {
			std::cout << block[i] << " ";
		}

		std::cout << std::endl;
		output_mutex.unlock();
	}

	void putThread() {
		for (size_t i = 0; i < NUM_OF_ITEMS; i++) {
			buffer.put(i);
			auto sleep_time = std::chrono::milliseconds(randomInt(SLEEP_TIME_SINGLE_ELEMENT_LOWER, SLEEP_TIME_SINGLE_ELEMENT_UPPER));
			std::this_thread::sleep_for(sleep_time);
		}
	}

	void getThread() {
		for (auto i = 0; i < NUM_OF_ITEMS; i++) {
			auto element = buffer.get();
			write(element);
			auto sleep_time = std::chrono::milliseconds(randomInt(SLEEP_TIME_SINGLE_ELEMENT_LOWER, SLEEP_TIME_SINGLE_ELEMENT_UPPER));
			std::this_thread::sleep_for(sleep_time);
		}
	}

	void putBlockThread() {
		int block[BLOCK_SIZE];
		for (size_t i = 0; i < NUM_OF_BLOCKS; i++) {
			for (size_t j = 0; j < BLOCK_SIZE; j++) {
				block[j] = -static_cast<int>(i) * BLOCK_SIZE - j;
			}

			buffer.put(block, BLOCK_SIZE);
			auto sleep_time = std::chrono::milliseconds(randomInt(SLEEP_TIME_BUFFER_LOWER, SLEEP_TIME_BUFFER_UPPER));
			std::this_thread::sleep_for(sleep_time);
		}
	}

	void getBlockThread() {
		int block[BLOCK_SIZE];
		for (size_t i = 0; i < NUM_OF_BLOCKS; i++) {
			buffer.get(block, BLOCK_SIZE);
			write(block, BLOCK_SIZE);
			auto sleep_time = std::chrono::milliseconds(randomInt(SLEEP_TIME_BUFFER_LOWER, SLEEP_TIME_BUFFER_UPPER));
			std::this_thread::sleep_for(sleep_time);
		}
	}

	void testBoundedBuffer() {
		auto putThreadObject = std::thread(putThread);
		auto putBlockThreadObject = std::thread(putBlockThread);
		auto getThreadObject = std::thread(getThread);
		auto getBlockThreadObject = std::thread(getBlockThread);

		putThreadObject.join();
		putBlockThreadObject.join();
		getThreadObject.join();
		getBlockThreadObject.join();
	}
}
