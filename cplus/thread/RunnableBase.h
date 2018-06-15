//
// Created by Tursom Ulefits on 2018/5/20.
//

#ifndef CPLUS_RUNNABLE_BASE_H
#define CPLUS_RUNNABLE_BASE_H

#include <functional>
#include <iostream>
#include <utility>
#include "../tools/class.h"

namespace cplus {
	namespace thread {
		template<typename T>
		CPlusClass(RunnableBase) {
		public:
			RunnableBase() : func(nullptr) {}
			
			explicit RunnableBase(std::function<void(T)> func) : func(func) {}
			
			virtual void run(T value) const {
				if (func != nullptr)func(value);
			}
			
			void operator()(T &value) const { run(value); }
		
		private:
			std::function<void(T)> func;
		};
	}
}


#endif //CPLUS_RUNNABLE_H
