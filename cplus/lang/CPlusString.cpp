//
// Created by Tursom Ulefits on 2018/6/16.
//

#include <iostream>
#include "CPlusString.h"
#include "ByteArray.h"

namespace cplus {
	namespace lang {
		CPlusString::CPlusString(const ByteArray &str)
				: bufferSize(str.getSize()), str((char *) malloc(bufferSize)) {
			strcpy(this->str, str.getBuffer());
		}
		
		CPlusString::CPlusString(const CPlusString &str)
				: bufferSize(str.bufferSize), str((char *) malloc(bufferSize)) {
			strcpy(this->str, str.getStr());
		}
		
		CPlusString::CPlusString(const std::string &str)
				: bufferSize(str.size() + 1), str((char *) malloc(bufferSize)) {
			strcpy(this->str, str.c_str());
		}
		
		CPlusString::CPlusString(const char *str) : bufferSize(strlen(str) + 1) {
			this->str = (char *) malloc(bufferSize);
			strcpy(this->str, str);
		}
		
		CPlusString::CPlusString() : str((char *) malloc(1)) {
			str[0] = 0;
		}
		
		CPlusString::~CPlusString() {
//			std::cout << "CPlusString: ~CPlusString(): " << (void *) str << ": "
//			          << (str == nullptr ? " [ str is null! ] " : str) << std::endl;
			if (str != nullptr) free(str);
		}
		
		std::ostream &operator<<(std::ostream &os, const CPlusString &string) {
			os << "str: " << string.str;
			return os;
		}
		
		void CPlusString::setToNull() {
			str = nullptr;
			bufferSize = 0;
		}
		
		bool CPlusString::operator==(const CPlusString &rhs) const {
			if (&rhs == this)return true;
			else return !strcmp(rhs.str, this->str);
		}
		
		bool CPlusString::operator!=(const CPlusString &rhs) const {
			return !(rhs == *this);
		}
		
		bool CPlusString::operator<(const CPlusString &rhs) const {
			if (str < rhs.str)
				return true;
			return strcmp(rhs.str, str) < 0;
		}
		
		bool CPlusString::operator>(const CPlusString &rhs) const {
			return rhs < *this;
		}
		
		bool CPlusString::operator<=(const CPlusString &rhs) const {
			return !(rhs < *this);
		}
		
		bool CPlusString::operator>=(const CPlusString &rhs) const {
			return !(*this < rhs);
		}
		
		char *CPlusString::getStr() const {
			return str;
		}
		
		void CPlusString::setStr(char *str, size_t bufferSize) {
			CPlusString::str = str;
			CPlusString::bufferSize = bufferSize;
		}
		
		size_t CPlusString::getBufferSize() const {
			return bufferSize;
		}
		
		u_int16_t CPlusString::getCited() const {
			return cited;
		}
	}
}