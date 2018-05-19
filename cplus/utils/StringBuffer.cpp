//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "StringBuffer.h"
#include "String.h"

namespace cplus {
	namespace utils {
		StringBuffer &StringBuffer::append(const String &string) {
			mutex.lock();
			value.append(string.__stdString());
			mutex.unlock();
			return *this;
		}
		
		String StringBuffer::toString() const {
			return String(value);
		}
	}
}
