//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_RUNNABLE_H
#define CPLUS_RUNNABLE_H


#include <functional>
#include <utility>

namespace cplus {
	namespace thread {
		class Runnable {
		public:
			Runnable() : Runnable(nullptr) {}
			
			explicit Runnable(const void(*func)()) : func(func) {}
			
#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
			explicit Runnable(const std::function<void()> func) : func(func) {}
#pragma clang diagnostic pop
			
			virtual void run() const {
				if (func != nullptr)func();
			}
			
			void operator()() const;
			
			const std::function<void()> &getFunc() const;
		
		private:
			const std::function<void()> func;
		};
	}
}

#endif //CPLUS_RUNNABLE_H
