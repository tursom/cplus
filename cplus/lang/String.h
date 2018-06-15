//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_String_H
#define CPLUS_UTILS_String_H

#include <string>
#include <utility>
#include <memory>
#include <set>
#include "../tools/class.h"

namespace cplus {
	namespace lang {
		CPlusClass(String) {
		public:
			explicit String(const char *&str);
			
			explicit String(const std::string &str);
			
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
			
			static std::string binToString(long value, char size = 64) {
//	StringBuilder sb;
				std::string sb;
				for (int i = 0; i < size; i++) {
					sb = (((value >> i) & 0x1) == 0 ? "0" : "1") + sb;
				}
				return sb;
			}
			
			static std::string binToHex(long value, char size = 64) {
//	StringBuilder sb;
				char str[] = {
						'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
				};
				std::string sb;
				for (int i = 0; (i * 4) < size; i++) {
					sb = str[(value >> (i * 4)) & 0xf] + sb;
				}
				return "0x" + sb;
			}
		
		private:
			const std::string *value{};
			
			static inline std::set<std::string> getStringSet();
		};
	}
}


#endif //CPLUS_UTILS_String_H
