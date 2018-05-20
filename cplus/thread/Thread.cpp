//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Thread.h"

namespace cplus {
	namespace thread {
		pid_t Thread::pidCount = 0;
		ThreadMutex Thread::pidCountMutex = ThreadMutex();
		ThreadMutex Thread::outputMutex = ThreadMutex();
		::cplus::utils::ArrayStack<pid_t>  Thread::pThreadStack(16, 16);
		
		void *threadStart(void *thread) {
			((Thread *) thread)->func();
		}
		
		bool Thread::_start() {
			if (pThreadStack.isFull()) return false;
			pthread_create(&pthread, nullptr, threadStart, this);
			pThreadStack.push(pthread);
		}
	}
}
