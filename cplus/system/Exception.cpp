//
// Created by Tursom Ulefits on 2018/6/15.
//

#include <execinfo.h>
#include "Exception.h"
#include "../lang/String.h"
#include "../utils/StringBuilder.h"
#include "../lang/CPlusString.h"
#include "../thread/ThreadMutex.h"

namespace cplus {
	namespace system {
		lang::String Exception::getStack() {
			int max_size = 256;
			void *ary[256] = {0};
			int stack_count;
			stack_count = backtrace(ary, max_size);
			auto buffer = backtrace_symbols(ary, stack_count);
			utils::StringBuilder sb;
//			sb.append("stack_count=");
//			sb.append(stack_count);
//			sb.append("\n");
			for (int i = 0; i < stack_count; i++) {
//				sb.append("Stack[");
//				sb.append(i);
//				sb.append("]=");
				sb.append(buffer[i]);
				sb.append("\n");
			}
			return sb.toString();
		}

		Exception::Exception(const lang::String &message) : Exception(message, true) {}

		Exception::Exception(const char *message) : Exception(lang::String(message)) {}

		Exception::Exception() : Exception("") {}

		Exception::Exception(const char *message, bool saveStack)
				: Exception(lang::String(message), saveStack) {}

		Exception::Exception(const lang::String &message, bool saveStack) : message(message) {
			if (saveStack) {
				stackTrace = getStack();
			} else {
				stackTrace = lang::String("DO NOT SAVE STACK TRANCE");
			}
		}
	}
}