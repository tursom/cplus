//
// Created by Tursom Ulefits on 2018/5/19.
//

#include "../utils/List.hpp"
#include "../system/OutputStream.h"
#include "../utils/ArrayList.hpp"
#include "../utils/Char.h"

using namespace ::cplus::utils;
using ::cplus::system::sout;
using ::cplus::system::endl;

void testChar() {
	Char aChar;
	Char a('a');
	sout << aChar << endl
	     << a << endl;
	sout << a << endl;
}

void testList() {
	List<int> list;
	size_t listSize = 24;
	for (int i = 0; i < listSize; ++i) {
		list.append(i);
		list.forEach([&]() {
			sout << list.get() << endl;
		});
	}
	sout << list.usedSize() << endl;
}

void testArrayList() {
	ArrayList<int> list;
	size_t listSize = 24;
	for (int i = 0; i < listSize; ++i) {
		list.append(i);
		list.forEach([&]() {
			sout << list.get() << endl;
		});
	}
	sout << list.usedSize() << endl;
}

void sizeOfListAndListArray() {
	size_t listSize = 1;
	size_t sizeOfListArray = 128;
	size_t listMemorySize, listArratMemorySize;
	for (int j = 0; j < 22; ++j) {
		sout << "list huge:" << listSize << endl;
		{
			ArrayList<int> list(sizeOfListArray);
			for (int i = 0; i < listSize; ++i) {
				list.append(i);
			}
			listArratMemorySize = list.usedSize();
		}
		{
			List<int> list;
			for (int i = 0; i < listSize; ++i) {
				list.append(i);
			}
			listMemorySize = list.usedSize();
		}
		sout << listArratMemorySize << ":" << listMemorySize << endl
		     << "memory size times:" << ((float) listMemorySize / listArratMemorySize) << endl;
		listSize *= 2;
	}
}

void testStack() {
	int stackSize = 100;
	sout << "stack size:" << stackSize << endl;
	Stack<int> stack;
	for (int i = 0; i < stackSize; ++i) {
		stack.push(i);
	}
	stack.forEach([&]() {
		sout << stack.pop() << " ";
	});
	sout << endl;
	for (int i = stackSize; i > 0; --i) {
		stack.push(i);
	}
	stack.forEach([&]() {
		sout << stack.pop() << " ";
	});
	sout << endl;
	sout << stack.usedSize() << endl;
}
