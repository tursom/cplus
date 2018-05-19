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
#include "cplus/utils/ArrayStack.h"

using namespace cplus::utils;
using namespace cplus::system;

/*
** float q_rsqrt( float number )
*/
float Q_rsqrt(float number) {
	long i;
	float x2, y;
	static const float threehalfs = 1.5F;
	
	x2 = number * 0.5F;
	y = number;
	i = *(long *) &y;                        // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck?
	y = *(float *) &i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed
	return y;
}

String string() {
	char c[] = "11;";
	return String(c);
}

#define SWAP_INIT \
char *__SWAP_A = NULL, *__SWAP_B = NULL

#define SWAP(a, b)\
{\
    char *__SWAP_A = (char *) &a;\
    char *__SWAP_B = (char *) &b;\
    for (size_t size = sizeof(a); size > 0; size--)\
    {\
        (*__SWAP_A) = (*__SWAP_A) ^ (*__SWAP_B);\
        (*__SWAP_B) = (*__SWAP_A) ^ *(__SWAP_B);\
        (*__SWAP_A) = (*__SWAP_A) ^ *(__SWAP_B);\
        ++__SWAP_A;\
        ++__SWAP_B;\
    }\
}

template<typename T>
void swap(T &a, T &b) {
	char *__SWAP_A = (char *) &a;
	char *__SWAP_B = (char *) &b;
	for (size_t __SWAP_TIME = sizeof(a); __SWAP_TIME > 0; __SWAP_TIME--) {
		(*__SWAP_A) = (*__SWAP_A) ^ (*__SWAP_B);
		(*__SWAP_B) = (*__SWAP_A) ^ *(__SWAP_B);
		(*__SWAP_A) = (*__SWAP_A) ^ *(__SWAP_B);
		++__SWAP_A;
		++__SWAP_B;
	}
}

//CPlusClass(BigInteger) {
//public:
//	BigInteger() : n(128) {}
//
//	const int get() const { return n[1].n1; }
//
//	int operator[](int n) { return (n % 2 == 1) ? this->n[n >> 1].n1 : this->n[n >> 1].n2; }
//
//	CPlusClass(DoubleIntBit) {
//	public:
//		DoubleIntBit() : DoubleIntBit(0) {}
//
//		DoubleIntBit(int n1) : n1(n1), n2(0) {}
//
//		DoubleIntBit(int n1, int n2) : n1(n1), n2(n2) {}
//
//		char n1:4;
//		char n2:4;
//	};
//
//	ListArray<DoubleIntBit> n;
//};

int main() {
	Stack<int> list;
	size_t listSize = 100;
	list.forEach([&]() {
		sout << list.pop() << endl;
	});
	for (int i = 0; i < listSize; ++i) {
		list.push(i);
	}
	list.forEach([&]() {
		sout << list.pop() << endl;
	});
	sout << list.usedSize() << endl;
	return 0;
}