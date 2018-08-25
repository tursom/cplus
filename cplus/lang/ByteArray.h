//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_BYTEARRAY_H
#define CPLUS_BYTEARRAY_H


#include <cstdlib>
#include <exception>
#include "String.h"
#include "../tools/class.h"
#include "../utils/StringBuilder.h"

namespace cplus {
	namespace lang {
		CPlusClass(ByteArray) {
		public:
			ByteArray();

			ByteArray(const char *buffer, size_t size);

			explicit ByteArray(size_t size);

			ByteArray(const ByteArray &byteArray);

			~ByteArray();

			void fillWithZero();

			size_t indexOf(int8_t byte) const;

			char operator[](size_t index);

			char *getBuffer() const;

			size_t getSize() const;

			void setSize(size_t size);

			void freeMemory();

			lang::String toHexString() const;

			lang::String toBinString() const;

			lang::String toString() const override;

			static void binToString(char value, char *buffer);

			static void binToHex(char value, char *buffer);

		private:
			char *buffer;
			size_t size;
			size_t bufferSize;
		};
	}
}

#endif //CPLUS_BYTEARRAY_H
