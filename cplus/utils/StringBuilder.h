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
			inline StringBuilder &append(const String &string);
			
			inline StringBuilder &append(const char *string);
			
			inline StringBuilder &append(Object value);
			
			inline StringBuilder &append(long value);
			
			inline StringBuilder &append(unsigned long value);
			
			inline StringBuilder &append(double value);
			
			String toString() const override;
		
		private:
			std::string value;
			
		};
	}
}


#endif //CPLUS_UTILS_StringBuilder_H
