//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Object.h"
#include "String.h"
#include "Long.h"

namespace cplus {
	namespace utils {
		String Object::toString() const {
			std::string s;
			s.append(typeid(*this).name());
			s.append(":");
			char str[22];
			sprintf(str, "%p", this);
			s.append(str);
			return String(s);
		}
		
		Object::operator ::cplus::utils::String() const {
			return toString();
		}
	}
}
