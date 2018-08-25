//
// Created by Tursom Ulefits on 2018/6/14.
//

#include "Runnable.h"

namespace cplus {
    namespace thread {
        void Runnable::operator()() const {
            run();
        }
    }
}