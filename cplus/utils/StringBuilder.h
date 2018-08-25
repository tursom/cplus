//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_StringBuilder_H
#define CPLUS_UTILS_StringBuilder_H


#include <string>
#include "../tools/class.h"
#include "../lang/CPlusString.h"

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

			StringBuilder &append(int value);

			StringBuilder &append(unsigned int value);

			StringBuilder &append(double value);

			StringBuilder &append(void *value);

			lang::String toString() const override;

			StringBuilder &append(const lang::CPlusString &value);

			const char *c_str();

		private:
			std::string value;

			StringBuilder &append(char value);

			StringBuilder &append(unsigned char value);
		};
	}
}


#endif //CPLUS_UTILS_StringBuilder_H
