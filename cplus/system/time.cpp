//
// Created by Tursom Ulefits on 2018/5/16.
//

#include <sys/time.h>
#include "./time.h"

#ifndef UNTITLED_TIME_H
#define UNTITLED_TIME_H
namespace cplus {
    namespace system {
        ::cplus::utils::Long getCurrentTime() {
            struct timeval tv;
            gettimeofday(&tv, nullptr);
            return ::cplus::utils::Long(tv.tv_sec * 1000 + tv.tv_usec / 1000);
        }
    }
}
#endif

