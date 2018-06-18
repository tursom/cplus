//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "StringBuilder.h"
#include "../lang/Long.h"
#include "../lang/Double.h"
#include "../lang/String.h"
#include "../lang/CPlusString.h"


namespace cplus {
	namespace utils {
		StringBuilder &StringBuilder::append(const ::cplus::lang::String &string) {
			value.append(string.c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(const char *string) {
			value.append(string);
			return *this;
		}
		
		::cplus::lang::String StringBuilder::toString() const {
			return ::cplus::lang::String(value);
		}
		
		StringBuilder &StringBuilder::append(Object value) {
			this->value.append(value.toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(long value) {
			this->value.append(::cplus::lang::Long(value).toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(double value) {
			this->value.append(::cplus::lang::Double(value).toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(unsigned long value) {
			char str[20];
			sprintf(str, "%lu", value);
			this->value.append(str);
			return *this;
		}
		
		StringBuilder &StringBuilder::append(const lang::CPlusString &value) {
			this->value.append(value.getStr());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(void *value) {
			char str[20];
			sprintf(str, "%p", value);
			this->value.append(str);
			return *this;
		}
		
		StringBuilder &StringBuilder::append() {
			return *this;
		}
	}
}
