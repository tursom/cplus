//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_EXCEPTION_H
#define CPLUS_EXCEPTION_H

#include "../tools/class.h"
#include "../lang/String.h"


namespace cplus {
	namespace system {
		CPlusClass(Exception), public std::exception {
		public:
			Exception() = default;
			
			explicit Exception(const char *message) : Exception(lang::String(message)) {}
			
			explicit Exception(const lang::String &message) : message(message) {}
			
			const lang::String &getMessage() const { return message; }
		
		private:
			lang::String message;
		};
	}
}

#endif //CPLUS_EXCEPTION_H
