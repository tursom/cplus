//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Short.h"

namespace cplus {
	namespace lang {
		String Short::toString() const {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}
		
		String Short::toString(int16_t value) {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}
	}
}