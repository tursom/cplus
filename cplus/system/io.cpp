//
// Created by Tursom Ulefits on 2018/5/17.
//

#include <cstdio>
#include <cstdarg>
#include "io.h"
#include "../thread/Thread.h"

namespace cplus {
	namespace system {
		void print(int n, const lang::Object *message, ...) {
			va_list pArgs;  //定义va_list类型的指针pArgs，用于存储参数地址

			va_start(pArgs, message); //初始化pArgs指针，使其指向第一个可变参数。该宏第二个参数是变参列表的前一个参数，即最后一个固定参数

			thread::Thread::lockOutput();
			while (--n) {
				lang::String temp = va_arg(pArgs, lang::String);
				printf("%s", temp.c_str());
			}
			thread::Thread::unlockOutput();

			/* Code Block using variable arguments */
//			printf(message, *pArgs);

			va_end(pArgs);  //将指针pArgs置为无效，结束变参的获取
		}

		void print(int n, const char *message, ...) {
			va_list pArgs;  //定义va_list类型的指针pArgs，用于存储参数地址

			va_start(pArgs, message); //初始化pArgs指针，使其指向第一个可变参数。该宏第二个参数是变参列表的前一个参数，即最后一个固定参数

			thread::Thread::lockOutput();
			while (--n) {
				char *temp = va_arg(pArgs, char*);
				printf("%s", temp);
			}
			thread::Thread::unlockOutput();

			/* Code Block using variable arguments */
//			printf(message, *pArgs);

			va_end(pArgs);  //将指针pArgs置为无效，结束变参的获取
		}


		void println(const char *message) {
			printf("%s\n", message);
		}

		void println(int n, const lang::Object *message, ...) {
			va_list pArgs;  //定义va_list类型的指针pArgs，用于存储参数地址

			va_start(pArgs, message); //初始化pArgs指针，使其指向第一个可变参数。该宏第二个参数是变参列表的前一个参数，即最后一个固定参数

			thread::Thread::lockOutput();
			while (--n) {
				lang::Object *temp = va_arg(pArgs, lang::Object*);
				printf("%s", temp->toString().c_str());
			}
			printf("\n");
			thread::Thread::unlockOutput();

			/* Code Block using variable arguments */
//			printf(message, *pArgs);

			va_end(pArgs);  //将指针pArgs置为无效，结束变参的获取
		}

		void println(int n, const char *message, ...) {
			va_list pArgs;  //定义va_list类型的指针pArgs，用于存储参数地址

			va_start(pArgs, message); //初始化pArgs指针，使其指向第一个可变参数。该宏第二个参数是变参列表的前一个参数，即最后一个固定参数

			thread::Thread::lockOutput();
			while (--n) {
				const char *temp = va_arg(pArgs, const char*);
				printf("%s", temp);
			}
			printf("\n");
			thread::Thread::unlockOutput();

			/* Code Block using variable arguments */
//			printf(message, *pArgs);

			va_end(pArgs);  //将指针pArgs置为无效，结束变参的获取
		}
	}
}