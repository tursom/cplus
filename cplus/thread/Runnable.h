//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_RUNNABLE_H
#define CPLUS_RUNNABLE_H


#include <functional>
#include "RunnableBase.h"

namespace cplus {
	namespace thread {
		class Runnable : public RunnableBase<void *> {
		public:
			Runnable() : RunnableBase() {}
			
			explicit Runnable(std::function<void()> func) : RunnableBase([&](void *) { func(); }) {}
		private:
		
		};
	}
}

#endif //CPLUS_RUNNABLE_H
