//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_String_H
#define CPLUS_UTILS_String_H

#include <string>
#include "../tools/class.h"

namespace cplus {
	namespace lang {
		class ByteArray;
		
		class CPlusString;
		
		CPlusClass(String) {
		public:
			String();
			
			String(const String &str);
			
			explicit String(const char *str);
			
			explicit String(const std::string &str);
			
			explicit String(const ByteArray &buffer);
			
			virtual ~String();
			
			/**
			 * @return 当前String
			 */
			String toString() const override;
			
			/**
			 * 将 String 转换为 const* char
			 * 时间复杂度位常数为常数 O(1)
			 * @return 当前字符串的C标准版本
			 */
			const char *c_str() const;
			
			String &operator=(const String &string);
			
			/**
			 * 返回一个标准库的string对象
			 * @return 一个对应的标准库的string对象
			 */
			std::string stdString() const;
			
			bool operator==(const String &rhs) const;
			
			bool operator!=(const String &rhs) const;
			
			String operator+(const std::string &str1);
			
			friend String operator+(const std::string &str1, const String &str2);
			
			/**
			 * 获取字符串池内的所有字符串的数据
			 * @return 所有字符串的JSON数据
			 */
			static char *allString();
			
			static char *bufferStruct();
		
			static size_t usedSize();
		private:
			CPlusString *value{};
		};
		
		/**
		 * 将字符串转义
		 * @param buffer 缓冲区
		 * @param oldStr 旧字符串
		 * @param strSize 旧字符串大小。请保证缓冲区的大小至少为旧字符串长度的两倍。
		 */
		void escapeString(char *buffer, const char *oldStr, size_t strSize);
	}
}


#endif //CPLUS_UTILS_String_H
