#ifndef _etfosthreading_region_h_
#define _etfosthreading_region_h_

#include <mutex> // unique_lock

#define region(mutex_type)														\
	auto flag = true;															\
	for (std::unique_lock<std::mutex> lock(mutex_type); flag; flag = false)	

#endif
