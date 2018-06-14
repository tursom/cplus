//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_Thread_H
#define CPLUS_THREAD_Thread_H

#include <pthread.h>
#include <utility>
#include <unistd.h>
#include "ThreadMutex.h"
#include "Runnable.h"
#include "../utils/List.hpp"

namespace cplus {
	namespace thread {
		CPlusClass(Thread) {
		public:
			Thread() = default;

//			explicit Thread(void (*func)()) : Thread((Runnable) VoidCall(func)) {}
			
			explicit Thread(std::function<void()> func) : func(std::move(func)) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			bool start();
			
			inline void detach() {
				pthread_join(pthread, nullptr);
			}
			
			void detachAll() {
				pThreadStack.forEach([&](pthread_t pthread1) {
					pthread_detach(pthread1);
				});
			}
			
			inline void join() {
				pthread_join(pthread, nullptr);
			}
			
			inline void joinAll() {
				pThreadStack.forEach([&](pthread_t pthread1) {
					pthread_join(pthread1, nullptr);
				});
			}
			
			inline const pthread_t &getPthread() {
				return pthread;
			}
			
			inline const pid_t &getPID() {
				return pid;
			}
			
			static pthread_t run(std::function<void()> func);
			
			inline static void lockOutput() {
				outputMutex.lock();
			}
			
			inline static void unlockOutput() {
				outputMutex.unlock();
			}
			
			//休眠secs毫秒
			static void msleep(unsigned int secs) {
				timeval tval{};
				tval.tv_sec = secs / 1000;
				tval.tv_usec = (secs * 1000) % 1000000;
				select(0, nullptr, nullptr, nullptr, &tval);
			}
			
			//休眠secs微秒
			inline static void usleep(unsigned int secs) {
				::usleep(secs);
			}
			
			//休眠secs秒
			inline static void sleep(unsigned int secs) {
				::sleep(secs);
			}
		
		private:
			/*class VoidCall : Runnable<void *> {
			public:
				VoidCall(void(*func)()) : func(func) {}

				void run() override {
					if (func != nullptr)func();
				}

			private:
				void (*func)();
			};*/
			
			pthread_t pthread;
			std::function<void()> func;
			pid_t pid;
			static ::cplus::utils::List<pthread_t> pThreadStack;
			static pid_t pidCount;
			static ThreadMutex pidCountMutex;
			static ThreadMutex outputMutex;
			
			friend void *threadStart(void *thread);
		};
		
		template<typename T>
		CPlusClass(SThread) {
		};
	}
}


#endif //CPLUS_THREAD_Thread_H
