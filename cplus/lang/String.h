//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_String_H
#define CPLUS_UTILS_String_H

#include <string>
#include <set>
#include "../tools/class.h"

namespace cplus {
	namespace lang {
		class ByteArray;
		
		CPlusClass(String) {
		public:
			String();
			
			explicit String(const char *str);
			
			explicit String(const std::string &str);
			
			explicit String(const ByteArray &buffer);
			
			String toString() const override;
			
			
			/**
			 * 目前实现方式是使用标准库string的c_str函数，
			 * 不保证时间复杂度位常数
			 * @return
			 */
			const char *c_str() const { return value->c_str(); }
			
			String &operator=(const String &string);
			
			/**
			 * 返回一个标准库的string对象
			 * 不保证返回的绝对是const引用
			 * 不保证向下兼容性
			 * @return 一个对应的标准库的string对象
			 */
			const std::string &stdString() const { return *value; }
			
			bool operator==(const String &rhs) const;
			
			bool operator!=(const String &rhs) const;
			
			String operator+(const std::string &str1);
			
			friend String operator+(const std::string &str1, const String &str2);
		
		private:
			const std::string *value{};
			
			static inline std::set<std::string> getStringSet();
		};
	}
}


#endif //CPLUS_UTILS_String_H
