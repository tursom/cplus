//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Short.h"

cplus::utils::String cplus::utils::Short::toString() const {
	char str[12];
	sprintf(str, "%d", value);
	return String(str);
}

cplus::utils::String cplus::utils::Short::toString(int16_t value) {
	char str[12];
	sprintf(str, "%d", value);
	return String(str);
}
