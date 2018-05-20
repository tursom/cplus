//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_Thread_H
#define CPLUS_THREAD_Thread_H

#include <pthread.h>
#include "ThreadMutex.h"
#include "Runnable.h"
#include "../utils/ArrayStack.hpp"

namespace cplus {
	namespace thread {
		class Thread {
		public:
			Thread() = default;
			
			explicit Thread(void (*func)(void *)) : func(Runnable([&]() { (*func)(this); })) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			explicit Thread(void (*func)()) : func(Runnable(func)) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			explicit Thread(const Runnable &func) : func(func) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			inline bool start() {
				_start();
				pthread_detach(pthread);
			}
			
			inline void join() {
				pthread_join(pthread, nullptr);
			}
			
			inline void joinAll() {
				pThreadStack.forEach([&]() {
					pthread_join(pThreadStack.get(), nullptr);
				});
			}
			
			inline const pthread_t &getPthread() {
				return pthread;
			}
			
			inline const pid_t &getPID() {
				return pid;
			}

//			inline void lockOutput() const {
//				outputMutex.lock();
//			}
//
//			inline void unlockOutput() const {
//				outputMutex.unlock();
//			}
			
			inline static void lockOutput() {
				outputMutex.lock();
			}
			
			inline static void unlockOutput() {
				outputMutex.unlock();
			}
		
		private:
			pthread_t pthread{};
			Runnable func;
			pid_t pid;
			static ::cplus::utils::ArrayStack<pthread_t> pThreadStack;
			static pid_t pidCount;
			static ThreadMutex pidCountMutex;
			static ThreadMutex outputMutex;
			
			bool _start();
			
			friend void *threadStart(void *thread);
		};
	}
}


#endif //CPLUS_THREAD_Thread_H
