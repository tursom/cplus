//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_Thread_H
#define CPLUS_THREAD_Thread_H

#include <pthread.h>
#include <utility>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include "ThreadMutex.h"
#include "Runnable.h"
#include "../system/Exception.h"
#include "../utils/List.hpp"

namespace cplus {
	namespace thread {
		CPlusClass(Thread) {
		public:
			
			explicit Thread(Runnable func) : func(std::move(func)) {
				pidCountMutex.lock();
				pid = pidCount++;
				pidCountMutex.unlock();
			}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-value-param"
			
			explicit Thread(std::function<void(void)> func) : func(func) {
			}

#pragma clang diagnostic pop
			
			~Thread();
			
			/**
			 * 启动线程
			 * @return 是否创建成功
			 */
			bool start();
			
			/**
			 * 释放线程
			 */
			static void detach(const Thread &thread1);
			
			static void join(const Thread &thread1) {
				pthread_join(thread1.getPthread(), nullptr);
			}
			
			inline const pthread_t &getPthread() const;
			
			inline const pid_t &getPID() const;
			
			static pthread_t run(std::function<void()> func);
			
			/**
			 * 锁定标准输出
			 */
			static void lockOutput();
			
			/**
			 * 解锁标准输出
			 */
			static void unlockOutput();
			
			/**
			 * @param secs 休眠的毫秒数
			 */
			static void msleep(unsigned int secs);
			
			/**
			 * @param secs 休眠的微秒数
			 */
			static void usleep(unsigned int secs);
			
			/**
			 * @param secs 休眠的秒数
			 */
			static void sleep(unsigned int secs);
			
			/**
			 * 退出当前线程
			 * @warning 主函数请务必使用本函数退出
			 */
			static void exitThread();
			
			class ThreadException : public system::Exception {
			public:
				ThreadException() = default;
				
				explicit ThreadException(const char *message);
				
				explicit ThreadException(const lang::String &message);
			};
		
		private:
			pthread_t pthread{};
			const Runnable func;
			pid_t pid;
			static pid_t pidCount;
			static ThreadMutex pidCountMutex;
			static ThreadMutex outputMutex;
			
			friend void *threadStart(void *thread);
		};
	}
}


#endif //CPLUS_THREAD_Thread_H
