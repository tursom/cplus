//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Char.h"

namespace cplus {
	namespace utils {
		String Char::toString() const {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}
		
		String Char::toString(int8_t value) {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}
	}
}