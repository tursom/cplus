//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Char.h"

namespace cplus {
	namespace lang {
		String Char::toString() const {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}

		String Char::toString(char value) {
			return String(value);
		}

		Char::Char() : Char(0) {}

		Char::Char(char value) : value(value) {}
	}
}