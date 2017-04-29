#ifndef _etfosthreading_region_h_
#define _etfosthreading_region_h_

#include <mutex> // unique_lock
#include <unordered_map> // unordered_map
#include <string> //to_string

namespace etfosthreading {
	extern std::unordered_map<std::string, std::mutex> region_mutexes_map;
}

#define VARIABLE_NAME(x) (std::string(#x))

#define VARIABLE_ADDRESS(x) (std::to_string(reinterpret_cast<unsigned long long>(&x)))

#define NAME_IN_MAP(x) (VARIABLE_NAME(x) + VARIABLE_ADDRESS(x))

#define region(variable)	\
	auto flag = true;		\
	for (std::unique_lock<std::mutex> lock(etfosthreading::region_mutexes_map[NAME_IN_MAP(variable)]); flag; flag = false)	

#endif
