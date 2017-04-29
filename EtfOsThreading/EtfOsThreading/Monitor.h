#ifndef _etfosthreading_monitor_h_
#define _etfosthreading_monitor_h_

#include <mutex> // mutex

namespace etfosthreading {

	template <typename F> struct FunctionType;
	
	template <typename R, typename Object, typename... Args> struct FunctionType<R(Object::*)(Args...)> {
		typedef R return_type;
	};

	template <typename R, typename Object, typename... Args> struct FunctionType<R(Object::*)(Args...) const> {
		typedef R return_type;
	};

	template <typename Object_> class Monitor {
	public:
		typedef Object_ object_type;

		template <typename F, typename... Args > typename FunctionType<F>::return_type operation(const F& f, Args... args)
		{
			std::unique_lock<std::mutex> lock(mutex_);
			return (object.*f)(args...);
		}

		template <typename F, typename... Args > typename FunctionType<F>::return_type operation(const F& f, Args... args) const
		{
			return const_cast<const Monitor<Object_> &>(this).operation(f, args...);
		}

	private:
		object_type object;
		mutable std::mutex mutex_;
	};

}

#endif
