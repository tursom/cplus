//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "StringBuilder.h"
#include "../lang/Long.h"
#include "../lang/Double.h"
#include "../lang/String.h"
#include "../lang/CPlusString.h"
#include "Set.hpp"
#include "Map.hpp"


namespace cplus {
	namespace utils {
		/**
		 * 将字符串转移
		 * @param buffer 缓冲区
		 * @param oldStr 旧字符串
		 * @param strSize 旧字符串大小。请保证缓冲区的大小至少为旧字符串长度的两倍。
		 */
		void escapeString(char *buffer, const char *oldStr, size_t strSize) {
			size_t index = 0;
			for (size_t i = 0; i < strSize; ++i) {
				switch (oldStr[i]) {
					case '\a':
						buffer[index++] = '\\';
						buffer[index++] = 'a';
						break;
					case '\b':
						buffer[index++] = '\\';
						buffer[index++] = 'b';
						break;
					case '\f':
						buffer[index++] = '\\';
						buffer[index++] = 'f';
						break;
					case '\n':
						buffer[index++] = '\\';
						buffer[index++] = 'n';
						break;
					case '\r':
						buffer[index++] = '\\';
						buffer[index++] = 'r';
						break;
					case '\t':
						buffer[index++] = '\\';
						buffer[index++] = 't';
						break;
					case '\v':
						buffer[index++] = '\\';
						buffer[index++] = 'v';
						break;
					case '\\':
						buffer[index++] = '\\';
						buffer[index++] = '\\';
						break;
					case '\?':
						buffer[index++] = '\\';
						buffer[index++] = '\?';
						break;
					case '\'':
						buffer[index++] = '\\';
						buffer[index++] = '\'';
						break;
					case '\"':
						buffer[index++] = '\\';
						buffer[index++] = '\"';
						break;
					default:
						buffer[index++] = oldStr[i];
						break;
				}
			}
			buffer[index] = 0;
		}
		
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
			auto strSize = value.getSize();
			auto *buffer = new char[strSize * 2];
			auto str = value.getStr();
			escapeString(buffer, value.getStr(), strSize);
			this->value.append(buffer);
			delete buffer;
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
