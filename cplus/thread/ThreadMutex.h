//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_THREAD_ThreadMutex_H
#define CPLUS_THREAD_ThreadMutex_H


#include <pthread.h>
#include "Runnable.h"

namespace cplus {
    namespace thread {
        class ThreadMutex {
        public:
            ThreadMutex() {
                pthread_mutex_init(&mutex, nullptr);
            }

            int lock() {
                return pthread_mutex_lock(&mutex);
            }

            int unlock() {
                return pthread_mutex_unlock(&mutex);
            }

            template<class T>
            void execute(const Runnable &runnable);

        private:
            pthread_mutex_t mutex;
        };

        template<class T>
        void ThreadMutex::execute(const Runnable &runnableBase) {
            lock();
            runnableBase();
            unlock();
        }
    }
}


#endif //CPLUS_THREAD_ThreadMutex_H
