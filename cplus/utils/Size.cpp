//
// Created by Tursom Ulefits on 2018/5/19.
//

#include "Size.h"
#include "String.h"

namespace cplus {
	namespace utils {
		String Size::toString() const {
			char str[22];
			sprintf(str, "%li", value);
			return String(str);
		}
		
		inline String Size::toString(size_t value) {
			char str[22];
			sprintf(str, "%li", value);
			return String(str);
		}
	}
}
