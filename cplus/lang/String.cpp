//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "String.h"
#include <set>

namespace cplus {
	namespace lang {
//        std::ostream &operator<<(std::ostream &os, const String &string) {
//            os << *string.value;
//        }
		
		String &String::operator=(const String &string) {
			value = string.value;
			return *this;
		}
		
		String String::toString() const {
			return *this;
		}
		
		String::String(const std::string &str) {
			auto index = getStringSet().emplace(str);
			value = &(*index.first);
		}
		
		String::String(const char *&str) : String(std::string(str)) {}
		
		std::set<std::string> String::getStringSet() {
			static std::set<std::string> stringSet;
			return stringSet;
		}
	}
}