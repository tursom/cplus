//
// Created by Tursom Ulefits on 2018/5/19.
//

#include "../utils/List.hpp"
#include "../system/OutputStream.h"
#include "../utils/ArrayList.hpp"
#include "../lang/Char.h"

using namespace ::cplus::lang;
using namespace ::cplus::utils;
using ::cplus::system::sout;
using ::cplus::system::endl;

namespace cplus {
	namespace utils {
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
				list.forEach([&](int i) {
					sout << i << endl;
				});
			}
			sout << list.usedSize() << endl;
		}
		
		void testArrayList() {
			ArrayList<int> list;
			size_t listSize = 24;
			for (int i = 0; i < listSize; ++i) {
				list.append(i);
				list.forEach([&](int i) {
					sout << i << endl;
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
					ArrayList<int> list(sizeOfListArray, 2097152 / sizeOfListArray + 1);
					for (int i = 0; i < listSize; ++i) {
						list.append(i);
					}
					listArratMemorySize = list.usedSize();
				}
				{
					List<int> list(2097152);
					for (int i = 0; i < listSize; ++i) {
						list.append(i);
					}
					listMemorySize = list.usedSize();
				}
				sout << listArratMemorySize << ":" << listMemorySize << endl
				     << "ArrayList saved memory :" << (1 - (float) listArratMemorySize / listMemorySize) << "%" << endl
				     << "ArrayList " << ((listMemorySize > listArratMemorySize) ? "saved" : "wasted") << " memory :"
				     << ((listMemorySize > listArratMemorySize) ?
				         (listMemorySize - listArratMemorySize) :
				         (listArratMemorySize - listMemorySize)) / 1024.0
				     << "KB"
				     << endl;
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
			stack.forEach([&](int value) {
				sout << value << " ";
			});
			sout << endl;
			for (int i = stackSize; i > 0; --i) {
				stack.push(i);
			}
			stack.forEach([&](int value) {
				sout << value << " ";
			});
			sout << endl;
			sout << stack.usedSize() << endl;
		}
	}
}