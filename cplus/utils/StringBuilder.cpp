//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "StringBuilder.h"
#include "Long.h"
#include "Double.h"


namespace cplus {
	namespace utils {
		StringBuilder &StringBuilder::append(const String &string) {
			value.append(string.c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(const char *string) {
			value.append(string);
			return *this;
		}
		
		String StringBuilder::toString() const {
			return String(value);
		}
		
		StringBuilder &StringBuilder::append(Object value) {
			this->value.append(value.toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(long value) {
			this->value.append(Long(value).toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(double value) {
			this->value.append(Double(value).toString().c_str());
			return *this;
		}
		
		StringBuilder &StringBuilder::append(unsigned long value) {
			char str[20];
			sprintf(str, "%lu", value);
			this->value.append(str);
			return *this;
		}
	}
}
