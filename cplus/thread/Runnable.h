//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_RUNNABLE_H
#define CPLUS_RUNNABLE_H


#include <functional>

namespace cplus {
    namespace thread {
        class Runnable {
        public:
            Runnable() : Runnable(nullptr) {}

            explicit Runnable(void(*func)()) : func(func) {}

            virtual void run() const {
                if (func != nullptr)func();
            }

            void operator()() const;

        private:
            void (*func)();
        };
    }
}

#endif //CPLUS_RUNNABLE_H
