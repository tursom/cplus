#include <cmath>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <map>
#include <algorithm>
#include "cplus/lang/String.h"
#include "cplus/lang/Int.h"
#include "cplus/system/time.h"
#include "cplus/system/OutputStream.h"
#include "cplus/lang/Float.h"
#include "cplus/lang/Short.h"
#include "cplus/utils/List.hpp"
#include "cplus/utils/ArrayList.hpp"
#include "cplus/utils/ArrayStack.hpp"
#include "cplus/test/utils.h"
#include "cplus/thread/Thread.h"

using namespace cplus::utils;
using namespace cplus::system;
using namespace cplus::thread;

CPlusClass(BigInteger) {
public:
	BigInteger() : n() {}
	
	int operator[](int n) { return (n % 2 == 1) ? this->n[n >> 1].n1 : this->n[n >> 1].n2; }
	
	CPlusClass(DoubleIntBit) {
	public:
		DoubleIntBit() : DoubleIntBit(0) {}
		
		DoubleIntBit(int n1) : n1(n1), n2(0) {}
		
		DoubleIntBit(int n1, int n2) : n1(n1), n2(n2) {}
		
		char n1:4;
		char n2:4;
	};
	
	ArrayList<DoubleIntBit> n;
};

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

union DtoS {
	double d;
	unsigned long l;
	struct {
		unsigned long mantissa:52;
		unsigned long exponent:11;
		unsigned long sign:1;
	} s;
};

std::string binToString(long value, char size = 64) {
//	StringBuilder sb;
	std::string sb;
	for (int i = 0; i < size; i++) {
		sb = (((value >> i) & 0x1) == 0 ? "0" : "1") + sb;
	}
	return sb;
}

std::string binToHex(long value, char size = 64) {
//	StringBuilder sb;
	char str[] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	std::string sb;
	for (int i = 0; (i * 4) < size; i++) {
		sb = str[(value >> (i * 4)) & 0xf] + sb;
	}
	return "0x" + sb;
}

template<typename T>
void println(const T &message) {
	Thread::lockOutput();
	std::cout << "println: " << message << std::endl;
	Thread::unlockOutput();
}

class TestClass {
public:
	TestClass() : outList([=]() {
		arrayStack.forEach([](int &i) {
			std::cout << i << std::endl;
		});
	}), arrayStack() {
		for (int i = 0; i < 100; i++) arrayStack.append(i);
	}
	
	ArrayList<int> arrayStack;
	Thread outList;
};

static TestClass testClass;

int main() {
	testClass.outList.start();
	testClass.outList.start();
	testClass.outList.detachAll();
	pthread_exit(nullptr);
//	println(arrayStack[5]);

//		auto func = [](void *) -> void * {
//		static int times = 0;
//		Thread::lockOutput();
//		try {
//			std::cout << "Hello World! in " << times++ << " times!" << std::endl;
//		} catch (std::exception e) {
//			std::cerr << e.what();
//		}
//		Thread::unlockOutput();
//	};
//	pthread_t pthread1;
//	pthread_create(&pthread1, nullptr, func, nullptr);
//	pthread_create(&pthread1, nullptr, func, nullptr);
//	pthread_create(&pthread1, nullptr, func, nullptr);
	/*Thread thread([]() {
		static int times = 0;
		Thread::lockOutput();
		std::cout << "Hello World! in " << times++ << " times!" << std::endl;
		Thread::unlockOutput();
	});
	for (int i = 0; i < 100; i++)
		thread.start();
	usleep(1000 * 1000);
	std::cout << "thread start comply" << std::endl;
//	thread.joinAll();
	usleep(1000 * 1000);
	std::cout << "thread sleep comply" << std::endl;*/
	return 0;
}