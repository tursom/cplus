#include <cmath>
#include <thread>
#include <iostream>
#include "cplus/utils/String.h"
#include "cplus/utils/Int.h"
#include "cplus/system/time.h"
#include "cplus/system/OutputStream.h"
#include "cplus/utils/Float.h"
#include "cplus/utils/Short.h"
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

int main() {
	Thread thread(Runnable([&]() {
		cplus::thread::Thread::lockOutput();
		sout << "Hello World!" << endl;
		cplus::thread::Thread::unlockOutput();
	}));
	thread.start();
	thread.start();
	thread.join();
	return 0;
}