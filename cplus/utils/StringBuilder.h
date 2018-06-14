//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_StringBuilder_H
#define CPLUS_UTILS_StringBuilder_H


#include <string>
#include "../tools/class.h"
#include "../lang/String.h"

namespace cplus {
	namespace utils {
		CPlusClass(StringBuilder) {
		public:
			StringBuilder &append(const ::cplus::lang::String &string);
			
			StringBuilder &append(const char *string);
			
			StringBuilder &append(Object value);
			
			StringBuilder &append(long value);
			
			StringBuilder &append(unsigned long value);
			
			StringBuilder &append(double value);
			
			::cplus::lang::String toString() const override;
		
		private:
			std::string value;
			
		};
	}
}


#endif //CPLUS_UTILS_StringBuilder_H
