//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Int.h"

cplus::utils::String cplus::utils::Int::toString() const {
	char str[12];
	sprintf(str, "%d", value);
	return String(str);
}

cplus::utils::String cplus::utils::Int::toString(int32_t value) {
	char str[12];
	sprintf(str, "%d", value);
	return String(str);
}
