//
// Created by Tursom Ulefits on 2018/5/16.
//

#include <iostream>
#include "Long.h"
#include "Float.h"

namespace cplus {
	namespace utils {
		String Long::toString() const {
			char str[22];
			sprintf(str, "%li", value);
			return String(str);
		}
		
		String Long::toString(int64_t value) {
			char str[22];
			sprintf(str, "%li", value);
			return String(str);
		}
		
		inline Long::operator int64_t() {
			return value;
		}
	}
}