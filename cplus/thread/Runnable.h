//
// Created by Tursom Ulefits on 2018/5/20.
//

#ifndef CPLUS_RUNNABLE_H
#define CPLUS_RUNNABLE_H

#include <functional>
#include <iostream>
#include "../tools/class.h"

namespace cplus {
	namespace thread {
		CPlusClass(Runnable) {
		public:
			Runnable() : func(nullptr) {}
			
			
			Runnable(void(*func)()) : func(func) {}
			
			Runnable(std::function<void()> func) : func(func) {}
			
			virtual void run() {
				if (func != nullptr)func();
			}
			
			void operator()() { run(); }
		
		private:
			std::function<void()> func;
		};
	}
}


#endif //CPLUS_RUNNABLE_H
