//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_Thread_H
#define CPLUS_THREAD_Thread_H

#include <pthread.h>
#include <utility>
#include <unistd.h>
#include "ThreadMutex.h"
#include "RunnableBase.h"
#include "../utils/List.hpp"
#include "Runnable.h"

namespace cplus {
	namespace thread {
		CPlusClass(Thread) {
		public:
			Thread() = default;

//			explicit Thread(void (*func)()) : Thread((RunnableBase) VoidCall(func)) {}
			
			explicit Thread(std::function<void()> func) : Thread(RunnableBase<void *>([&](void *) { func(); })) {}
			
			explicit Thread(Runnable func) : Thread((RunnableBase<void *>) func) {}
			
			explicit Thread(RunnableBase<void *> func) : func(std::move(func)) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}
			
			/**
			 * 启动线程
			 * @return 是否创建成功
			 */
			bool start();
			
			/**
			 * 释放利用本对象最近创建的线程
			 */
			inline void detach() {
				pthread_join(pthread, nullptr);
			}
			
			/**
			 * 释放所有线程
			 */
			static void detachAll() {
				pThreadStack.forEach([&](pthread_t pthread1) {
					pthread_detach(pthread1);
				});
			}
			
			/**
			 * 合并本对象最近创建的线程
			 */
			inline void join() {
				pthread_join(pthread, nullptr);
			}
			
			/**
			 * 逐一合并线程
			 */
			static inline void joinAll() {
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
			
			/**
			 * 锁定标准输出
			 */
			inline static void lockOutput() {
				outputMutex.lock();
			}
			
			/**
			 * 解锁标准输出
			 */
			inline static void unlockOutput() {
				outputMutex.unlock();
			}
			
			/**
			 * @param secs 休眠的毫秒数
			 */
			static void msleep(unsigned int secs) {
				timeval tval{};
				tval.tv_sec = secs / 1000;
				tval.tv_usec = (secs * 1000) % 1000000;
				select(0, nullptr, nullptr, nullptr, &tval);
			}
			
			/**
			 * @param secs 休眠的微秒数
			 */
			inline static void usleep(unsigned int secs) {
				::usleep(secs);
			}
			
			/**
			 * @param secs 休眠的秒数
			 */
			inline static void sleep(unsigned int secs) {
				::sleep(secs);
			}
			
			/**
			 * 退出当前线程
			 * @warning 主函数请务必使用本函数退出
			 */
			static void exitThread() {
				pthread_exit(nullptr);
			}
		
		private:
			pthread_t pthread{};
			RunnableBase<void *> func;
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
