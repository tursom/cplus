//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "String.h"
#include <set>
#include "ByteArray.h"

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
		
		String::String(const char *str) : String(std::string(str)) {}
		
		std::set<std::string> String::getStringSet() {
			static std::set<std::string> stringSet;
			return stringSet;
		}
		
		String::String() : String("") {
		}
		
		String operator+(const std::string &str1, const String &str2) {
			return String(str1 + *str2.value);
		}
		
		String String::operator+(const std::string &str1) {
			return String(*value + str1);
		}
		
		bool String::operator==(const String &rhs) const {
			return value == rhs.value;
		}
		
		bool String::operator!=(const String &rhs) const {
			return !(rhs == *this);
		}
		
		inline size_t min(size_t s1, size_t s2) {
			return s1 < s2 ? s1 : s2;
		}
		
		String::String(const ByteArray &buffer) {
			auto size = min(buffer.getSize(), buffer.indexOf(0));
		}
	}
}