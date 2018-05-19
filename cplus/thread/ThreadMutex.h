//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_ThreadMutex_H
#define CPLUS_THREAD_ThreadMutex_H


#include <pthread.h>

namespace cplus{
	namespace thread{
		class ThreadMutex {
		public:
			ThreadMutex() {
				pthread_mutex_init(&mutex, nullptr);
			}
			
			void lock() {
				pthread_mutex_lock(&mutex);
			}
			
			void unlock() {
				pthread_mutex_unlock(&mutex);
			}
		
		private:
			pthread_mutex_t mutex;
		};
	}
}


#endif //CPLUS_THREAD_ThreadMutex_H
