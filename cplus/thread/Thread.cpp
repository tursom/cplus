//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Thread.h"

namespace cplus {
	namespace thread {
		pid_t Thread::pidCount = 0;
		ThreadMutex Thread::pidCountMutex = ThreadMutex();
		ThreadMutex Thread::outputMutex = ThreadMutex();
	}
}
