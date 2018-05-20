//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_MEMORY_TOOLS_H
#define CPLUS_MEMORY_TOOLS_H

#include <cstdlib>

#ifndef __SWAP
#define __SWAP(a, b)\
{\
    char *swapA = (char *) &a;\
    char *swapB = (char *) &b;\
    for (size_t loopTime = sizeof(a); loopTime > 0; loopTime--)\
    {\
        (*swapA) = (*swapA) ^ (*swapB);\
        (*swapB) = (*swapA) ^ *(swapB);\
        (*swapA) = (*swapA) ^ *(swapB);\
        ++swapA;\
        ++swapB;\
    }\
}
#endif

#ifndef __COPY
#define __COPY(a, b)\
{\
    char *swapA = (char *) &a;\
    char *swapB = (char *) &b;\
	size_t sizeOfA = sizeof(a);\
	size_t sizeOfB = sizeof(b);\
    for (size_t loopTime = (sizeOfA < sizeOfB) ? sizeOfA : sizeOfB; loopTime > 0; loopTime--)\
    {\
        (*swapB) = (*swapA);\
        ++swapA;\
        ++swapB;\
    }\
}
#endif

namespace cplus {
	namespace memory {
		/**
		 * 邪恶的魔法，交换a和b的所有内容，即使两个变量都是const变量
		 * @tparam T
		 * @param a
		 * @param b
		 */
		template<typename T>
		void swap(const T &a, const T &b) {
			char *swapA = (char *) &a;
			char *swapB = (char *) &b;
			for (size_t swapTime = sizeof(a); swapTime > 0; swapTime--) {
				(*swapA) = (*swapA) ^ (*swapB);
				(*swapB) = (*swapA) ^ *(swapB);
				(*swapA) = (*swapA) ^ *(swapB);
				++swapA;
				++swapB;
			}
		}
		
		/**
		 * 邪恶的魔法，交换a和b的所有内容，即使两个变量都是const变量，并且类型也不一样
		 * @tparam T1
		 * @tparam T2
		 * @param a
		 * @param b
		 * @param size
		 */
		template<typename T1, typename T2>
		void swap(const T1 *a, const T2 *b) {
			char *swapA = (char *) a;
			char *swapB = (char *) b;
			size_t sizeOfA = sizeof(a);
			size_t sizeOfB = sizeof(b);
			for (size_t loopTIme = (sizeOfA < sizeOfB) ? sizeOfA : sizeOfB; loopTIme > 0; --loopTIme) {
				(*swapA) = (*swapA) ^ (*swapB);
				(*swapB) = (*swapA) ^ *(swapB);
				(*swapA) = (*swapA) ^ *(swapB);
				++swapA;
				++swapB;
			}
		}
		
		/**
		 * 邪恶的魔法，将a中的内容拷贝到b中，即使两个变量都是const变量
		 * @tparam T
		 * @param a
		 * @param b
		 */
		template<typename T>
		void copy(const T &a, const T &b) {
			char *swapA = (char *) &a;
			char *swapB = (char *) &b;
			for (size_t loopTIme = sizeof(a); loopTIme > 0; loopTIme--) {
				(*swapB) = (*swapA);
				++swapA;
				++swapB;
			}
		}
		
		/**
		 * 邪恶的魔法，将a中的内容拷贝到b中，即使两个变量都是const变量，并且类型也不一样
		 * @tparam T1
		 * @tparam T2
		 * @param a
		 * @param b
		 * @param size
		 */
		template<typename T1, typename T2>
		void copy(const T1 *a, const T2 *b) {
			char *swapA = (char *) a;
			char *swapB = (char *) b;
			size_t sizeOfA = sizeof(a);
			size_t sizeOfB = sizeof(b);
			for (size_t loopTIme = (sizeOfA < sizeOfB) ? sizeOfA : sizeOfB; loopTIme > 0; --loopTIme) {
				(*swapB) = (*swapA);
				++swapA;
				++swapB;
			}
		}
	}
}

#endif //CPLUS_MEMORY_TOOLS_H
