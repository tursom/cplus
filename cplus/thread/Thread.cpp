//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Thread.h"

namespace cplus {
	namespace thread {
		pid_t Thread::pidCount = 0;
		ThreadMutex Thread::pidCountMutex = ThreadMutex();
		ThreadMutex Thread::outputMutex = ThreadMutex();
		::cplus::utils::List<pthread_t>  Thread::pThreadStack(16);
		
		void *threadStart(void *thread) {
			((Thread *) thread)->func();
		}
		
		void *staticThreadStart(void *thread) {
			((std::function<void()> *) thread)->operator()();
		}
		
		pthread_t Thread::run(std::function<void()> func) {
			if (pThreadStack.isFull()) return nullptr;
			pthread_t pthread1;
			pthread_create(&pthread1, nullptr, staticThreadStart, (void *) &func);
			pThreadStack.append(pthread1);
			return pthread1;
		}
		
		bool Thread::start() {
			if (pThreadStack.isFull()) return false;
			pthread_create(&pthread, nullptr, threadStart, this);
			pThreadStack.append(pthread);
			return true;
		}
	}
}
