//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "StringBuffer.h"
#include "../lang/String.h"

namespace cplus {
	namespace utils {
		StringBuffer &StringBuffer::append(const ::cplus::lang::String &string) {
			mutex.lock();
			value.append(string.__stdString());
			mutex.unlock();
			return *this;
		}
		
		::cplus::lang::String StringBuffer::toString() const {
			return ::cplus::lang::String(value);
		}
	}
}
