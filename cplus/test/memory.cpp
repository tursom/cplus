//
// Created by Tursom Ulefits on 2018/6/14.
//
#include "memory.h"
#include "../lang/String.h"
#include "../memory/dark_magic.h"
#include "../system/OutputStream.h"

using namespace cplus::system;

namespace cplus {
	namespace memory {
		
		/**
 		 * 测试用类
 		 */
		CPlusClass(Test) {
		public:
			Test() : Test(0, 0.0, 0, 0) {};
			
			Test(int i, double d, const int constI, const double constDouble)
					: i(i), d(d), constI(constI), constDouble(constDouble) {};
			
			int i;
			double d;
			const int constI;
			const double constDouble;
			
			friend const ::cplus::system::OutputStream &operator<<(const ::cplus::system::OutputStream &os, Test t);
		};
		
		/**
 		 * 辅助输出函数
 		 * @param os
 		 * @param t
		 * @return
		 */
		const ::cplus::system::OutputStream &operator<<(const ::cplus::system::OutputStream &os, Test t) {
			os << "i:" << t.i << "; d" << t.d << "; const i:" << t.constI << "; const d:" << t.constDouble;
			return os;
		}
		
		/**
		 * testMemory_dark_magic()
		 * 用于完整测试dark_magic下的宏与函数的功能，从标准输出输出测试数据
		 */
		void testMemory_dark_magic() {
			/**
			 * 定义测试用变量
			 */
			int a = 1, b = 2;
			double d1 = 1.0;
			double d2 = 2.0;
			const int constA = 1, constB = 2;
			const double constD1 = 1.0, constD2 = 2.0;
			Test test1(1, 1, 1, 1), test2(2, 2, 2, 2);
			const Test constTest1(1, 1, 1, 1), constTest2(2, 2, 2, 2);
			/**
			 * swap test start
			 */
			//提示开始swap方法测试
			sout << "swap test:" << endl;
			//输出测试前变量的状态
			sout << "a:" << a << " b:" << b << endl;
			//测试非const变量的__SWAP宏
			__SWAP(a, b)
			sout << "a:" << a << " b:" << b << endl;
			//测试非const变量的swap函数
			::cplus::memory::swap(a, b);
			sout << "a:" << a << " b:" << b << endl;
			
			//输出测试前变量的状态
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			//测试非const变量的__SWAP宏
			__SWAP(d1, d2)
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			//测试非const变量的swap函数
			::cplus::memory::swap(d1, d2);
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			
			//输出测试前变量的状态
			sout << "const a:" << constA << " const b:" << constB << endl;
			//测试const变量的__SWAP宏
			__SWAP(constA, constB)
			sout << "const a:" << constA << " const b:" << constB << endl;
			//测试const变量的swap函数
			::cplus::memory::swap(constA, constB);
			sout << "const a:" << constA << " const b:" << constB << endl;
			
			//输出测试前变量的状态
			sout << "const d1:" << constD1 << " const d2:" << constD2 << endl;
			//测试const变量的__SWAP宏
			__SWAP(constD1, constD2)
			sout << "d1:" << constD1 << " d2:" << constD2 << endl;
			//测试const变量的swap函数
			::cplus::memory::swap(constD1, constD2);
			sout << "d1:" << d1 << " d2:" << constD2 << endl;
			
			//输出测试前变量的状态
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			//测试非const变量的__SWAP宏
			__SWAP(test1, test2)
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			//测试非const变量的swap函数
			::cplus::memory::swap(test1, test2);
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			
			//输出测试前变量的状态
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			//测试const变量的__SWAP宏
			__SWAP(constTest1, constTest2)
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			//测试const变量的swap函数
			::cplus::memory::swap(constTest1, constTest2);
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			/**
			 * swap test end
			 */
			
			/**
			 * copy test start
			 */
			//提示开始copy方法测试
			sout << endl << "copy test:" << endl;
			
			//输出测试前变量的状态
			sout << "a:" << a << " b:" << b << endl;
			//测试非const变量的__COPY宏
			__COPY(a, b)
			sout << "a:" << a << " b:" << b << endl;
			//测试非const变量的copy函数
			::cplus::memory::copy(a, b);
			sout << "a:" << a << " b:" << b << endl;
			
			//输出测试前变量的状态
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			//测试非const变量的__COPY宏
			__COPY(d1, d2)
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			//测试非const变量的copy函数
			::cplus::memory::copy(d1, d2);
			sout << "d1:" << d1 << " d2:" << d2 << endl;
			
			
			//输出测试前变量的状态
			sout << "const a:" << constA << " const b:" << constB << endl;
			//测试const变量的__COPY宏
			__SWAP(constA, constB)
			sout << "const a:" << constA << " const b:" << constB << endl;
			//测试const变量的copy函数
			::cplus::memory::swap(constA, constB);
			sout << "const a:" << constA << " const b:" << constB << endl;
			
			//输出测试前变量的状态
			sout << "const d1:" << constD1 << " const d2:" << constD2 << endl;
			//测试const变量的__COPY宏
			__SWAP(constD1, constD2)
			sout << "d1:" << constD1 << " d2:" << constD2 << endl;
			//测试const变量的copy函数
			::cplus::memory::swap(constD1, constD2);
			sout << "d1:" << d1 << " d2:" << constD2 << endl;
			
			//输出测试前变量的状态
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			//测试非const变量的__COPY宏
			__COPY(test1, test2)
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			//测试非const变量的copy函数
			::cplus::memory::copy(test1, test2);
			sout << "test1:" << test1 << endl << "test2:" << test2 << endl;
			
			//输出测试前变量的状态
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			//测试const变量的__COPY宏
			__COPY(constTest1, constTest2)
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			//测试const变量的copy函数
			::cplus::memory::copy(constTest1, constTest2);
			sout << "const test1:" << constTest1 << endl << "const test2:" << constTest2 << endl;
			/**
			 * copy test end
			 */
		}
	}
}