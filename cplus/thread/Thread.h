//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_Thread_H
#define CPLUS_THREAD_Thread_H

#include <pthread.h>
#include "ThreadMutex.h"

namespace cplus {
	namespace thread {
		typedef void *(*Func)(void *);
		
		class Thread {
		public:
			Thread() = default;
			
			explicit Thread(void *func(void *)) : func(func) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			inline void start() {
				_start();
				pthread_detach(pthread);
			}
			
			inline void join() {
				pthread_join(pthread, nullptr);
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
			Func func;
			pid_t pid;
			static pid_t pidCount;
			static ThreadMutex pidCountMutex;
			static ThreadMutex outputMutex;
			
			void _start() {
				pthread_create(&pthread, nullptr, func, this);
			}
		};
	}
}


#endif //CPLUS_THREAD_Thread_H
