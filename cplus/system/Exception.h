//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_EXCEPTION_H
#define CPLUS_EXCEPTION_H

#include "../tools/class.h"
#include "../lang/String.h"


namespace cplus {
	namespace lang {
		class String;
	}
	namespace system {
		CPlusClass(Exception) {
		public:
			Exception() : Exception("") {}
			
			explicit Exception(const char *message) : Exception(lang::String(message)) {}
			
			explicit Exception(const lang::String &message) : message(message) {
				stackTrace = getStack();
			}
			
			const lang::String &getMessage() const { return message; }
			
			const lang::String &getStackTrace() const { return stackTrace; }
		
		private:
			static lang::String getStack();
			
			lang::String stackTrace;
			lang::String message;
		};
	}
}

#endif //CPLUS_EXCEPTION_H
