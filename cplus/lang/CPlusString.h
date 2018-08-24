//
// Created by Tursom Ulefits on 2018/6/16.
//

#ifndef CPLUS_CPLUSSTRING_H
#define CPLUS_CPLUSSTRING_H


#include <cstring>
#include "../tools/class.h"

namespace cplus {
	namespace lang {
		class ByteArray;
		
		CPlusClass(CPlusString) {
		public:
			CPlusString();
			
			explicit CPlusString(const char *str);
			
			explicit CPlusString(const std::string &str);
			
			CPlusString(const CPlusString &str);
			
			explicit CPlusString(const ByteArray &str);
			
			~CPlusString();
			
			friend std::ostream &operator<<(std::ostream &os, const CPlusString &string);
			
			void setToNull();
			
			void setStr(char *str, size_t bufferSize);
			
			size_t getBufferSize() const;
			
			size_t getSize() const;
			
			bool operator==(const CPlusString &rhs) const;
			
			bool operator!=(const CPlusString &rhs) const;
			
			bool operator<(const CPlusString &rhs) const;
			
			bool operator>(const CPlusString &rhs) const;
			
			bool operator<=(const CPlusString &rhs) const;
			
			bool operator>=(const CPlusString &rhs) const;
			
			char *getStr() const;
			
			u_int16_t getCited() const;
		
		private:
			char *str{};
			size_t bufferSize{};
			u_int16_t cited;
		};
	}
}

#endif //CPLUS_CPLUSSTRING_H
