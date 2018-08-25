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
			/**
			 * 默认构造函数调用Exception("")进行初始化
			 */
			Exception();

			explicit Exception(const char *message);

			explicit Exception(const lang::String &message);

			const lang::String &getMessage();

			const lang::String getStackTrace();

			const lang::String getStackTrace() const;

		private:
			static int getStack(void **ary);

			lang::String getStack() const;

			void *ary[256];
			int stack_count;

			lang::String *stackTrace = nullptr;
			const lang::String message;
		};
	}
}

#endif //CPLUS_EXCEPTION_H
