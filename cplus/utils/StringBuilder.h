//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_StringBuilder_H
#define CPLUS_UTILS_StringBuilder_H


#include <string>
#include "../tools/class.h"

namespace cplus {
	namespace utils {
		CPlusClass(StringBuilder) {
		public:
			StringBuilder &append();
			
			StringBuilder &append(const ::cplus::lang::String &string);
			
			StringBuilder &append(const char *string);
			
			StringBuilder &append(Object value);
			
			StringBuilder &append(long value);
			
			StringBuilder &append(unsigned long value);
			
			StringBuilder &append(double value);
			
			StringBuilder &append(void *value);
			
			::cplus::lang::String toString() const override;
			
			StringBuilder &append(const lang::CPlusString &value);
		
		private:
			std::string value;
		};
	}
}


#endif //CPLUS_UTILS_StringBuilder_H
