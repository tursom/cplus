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
        int Exception::getStack(void **ary) {
            static int max_size = 256;
            return backtrace(ary, max_size);
        }

        lang::String Exception::getStack() const {
            auto buffer = backtrace_symbols(ary, stack_count);
            utils::StringBuilder sb;
            for (int i = 0; i < stack_count; i++) {
                sb.append(buffer[i]);
                sb.append("\n");
            }
            return sb.toString();
        }

        Exception::Exception(const lang::String &message) : message(message) {
            stack_count = getStack(ary);
        }

        Exception::Exception(const char *message) : Exception(lang::String(message)) {}

        Exception::Exception() : Exception("") {}


        const lang::String Exception::getStackTrace() const {
            return stackTrace == nullptr ? lang::String("null") : *stackTrace;
        }

        const lang::String Exception::getStackTrace() {
            if (stackTrace == nullptr) {
                stackTrace = getStack().getPointer();
            }
            return *stackTrace;
        }

        const lang::String &Exception::getMessage() {
            return message;
        }
    }
}