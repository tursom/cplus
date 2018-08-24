//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef CPLUS_SYSTEM_IO_H
#define CPLUS_SYSTEM_IO_H

#include "../lang/String.h"

namespace cplus {
	namespace system {
		void print(int n, const lang::Object *message, ...);

		void print(int n, const char *message, ...);

		void println(int n, const lang::Object *message, ...);

		void println(int n, const char *message, ...);
	}
}

#endif //CPLUS_SYSTEM_IO_H
