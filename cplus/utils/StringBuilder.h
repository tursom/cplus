//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_StringBuilder_H
#define CPLUS_UTILS_StringBuilder_H


#include <string>
#include "Object.h"
#include "String.h"

namespace cplus {
	namespace utils {
		class StringBuilder : Object {
		public:
			StringBuilder &append(const String &string);
			
			StringBuilder &append(const char *string);
			
			StringBuilder &append(Object value);
			
			StringBuilder &append(long value);
			
			StringBuilder &append(unsigned long value);
			
			StringBuilder &append(double value);
			
			String toString() const override;
		
		private:
			std::string value;
			
		};
	}
}


#endif //CPLUS_UTILS_StringBuilder_H
