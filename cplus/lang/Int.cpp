//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Int.h"
#include "String.h"

namespace cplus {
	namespace lang {
		String Int::toString() const {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}

		String Int::toString(int32_t value) {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}

		String Int::operator+(const String &string) {
			return this->toString().operator+(string);
		}

		String operator+(const String &string, Int i) {
			return String(string + i.toString());
		}
	}
}