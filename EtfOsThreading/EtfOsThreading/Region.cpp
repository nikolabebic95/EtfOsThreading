#include "Region.h"

namespace etfosthreading {

	std::unordered_map<std::string, std::mutex> region_mutexes_map;

}