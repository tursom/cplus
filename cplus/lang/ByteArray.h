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
			ByteArray() : ByteArray(0) {}
			
			ByteArray(const char *buffer, size_t size) : ByteArray(size) {
				//初始化buffer
				for (size_t n = 0; n < size; n++) {
					this->buffer[n] = buffer[n];
				}
			}
			
			ByteArray(size_t size) : buffer(new char[size]), size(size), bufferSize(size) {}
			
			~ByteArray() {
				delete buffer;
			}
			
			void fillWithZero() {
				for (int index = 0; index < size; index++)
					buffer[index] = 0;
			}
			
			size_t indexOf(int8_t byte)const {
				for (size_t index = 0; index < size; index++) {
					if (buffer[index] == byte)
						return index;
				}
				return size;
			}
			
			char operator[](size_t index) {
				if (index < size) return buffer[index];
				else throw OutOfIndexException();
			}
			
			char *getBuffer() const { return buffer; }
			
			size_t getSize() const { return size; }
			
			class OutOfIndexException : public std::exception {
			};
			
			void setSize(size_t size) {
				if (size < bufferSize) {
					this->size = size;
				} else {
					auto newBuffer = new char[size];
					auto minSize = (size < this->size) ? size : this->size;
					for (size_t index = 0; index < minSize; index++) {
						newBuffer[index] = buffer[index];
					}
					delete buffer;
					buffer = newBuffer;
					bufferSize = size;
					ByteArray::size = size;
				}
			}
			
			void freeMemory() {
				if (size != bufferSize) {
					auto newBuffer = new char[size];
					for (size_t index = 0; index < size; index++) {
						newBuffer[index] = buffer[index];
					}
					delete buffer;
					buffer = newBuffer;
					bufferSize = size;
				}
			}
			
			lang::String toHexString() const {
				auto *buffer = new char[size * 3 + 1];
				buffer[size * 3] = 0;
				for (int index = 0; index < size; index++) {
					binToHex(this->buffer[index], buffer + index * 3);
					buffer[index * 3 + 2] = ' ';
				}
				auto ret = lang::String(buffer);
				delete buffer;
				return ret;
			}
			
			lang::String toBinString() const {
				auto *buffer = new char[size * 9 + 1];
				buffer[size * 9] = 0;
				for (int index = 0; index < size; index++) {
					binToString(this->buffer[index], buffer + index * 9);
					buffer[index * 9 + 8] = ' ';
				}
				auto ret = lang::String(buffer);
				delete buffer;
				return ret;
			}
			
			lang::String toString() const override {
				return toHexString();
			}
			
			static void binToString(char value, char *buffer) {
				buffer[7] = ((value & 0x1) == 0 ? '0' : '1');
				buffer[6] = ((value & 0x2) == 0 ? '0' : '1');
				buffer[5] = ((value & 0x4) == 0 ? '0' : '1');
				buffer[4] = ((value & 0x8) == 0 ? '0' : '1');
				buffer[3] = ((value & 0x10) == 0 ? '0' : '1');
				buffer[2] = ((value & 0x20) == 0 ? '0' : '1');
				buffer[1] = ((value & 0x40) == 0 ? '0' : '1');
				buffer[0] = ((value & 0x80) == 0 ? '0' : '1');
			}
			
			static inline void binToHex(char value, char *buffer) {
				static char str[] = {
						'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
				};
				buffer[1] = str[value & 0xf];
				buffer[0] = str[(value >> 4) & 0xf];
			}
		
		private:
			char *buffer;
			size_t size;
			size_t bufferSize;
		};
	}
}

#endif //CPLUS_BYTEARRAY_H
