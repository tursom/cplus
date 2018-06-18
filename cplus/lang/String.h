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
			
			String toString() const override;
			
			/**
			 * 时间复杂度位常数为常数 O(1)
			 * @return
			 */
			const char *c_str() const;
			
			String &operator=(const String &string);
			
			/**
			 * 返回一个标准库的string对象
			 * 不保证返回的绝对是const引用
			 * 不保证向下兼容性
			 * @return 一个对应的标准库的string对象
			 */
			std::string stdString() const;
			
			bool operator==(const String &rhs) const;
			
			bool operator!=(const String &rhs) const;
			
			String operator+(const std::string &str1);
			
			friend String operator+(const std::string &str1, const String &str2);
			
			static String allString();
		
		private:
			CPlusString *value{};
		};
	}
}


#endif //CPLUS_UTILS_String_H
