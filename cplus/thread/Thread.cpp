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
			((Thread *) thread)->func(thread);
		}

		void *staticThreadStart(void *thread) {
			((std::function<void()> *) thread)->operator()();
		}

		pthread_t Thread::run(std::function<void()> func) {
			if (pThreadStack.isFull())throw ThreadException("thread stack is full");
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

		Thread::ThreadException::ThreadException(const char *message) : Exception(message) {}

		Thread::ThreadException::ThreadException(const lang::String &message) : Exception(
				message) {}
	}
}
