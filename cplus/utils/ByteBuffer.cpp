//
// Created by tursom on 2020/5/23.
//

#include <netinet/in.h>
#include "ByteBuffer.h"
#include "../system/OutOfIndexException.h"
#include "../memory/dark_magic.h"

using namespace cplus::system;


namespace cplus {
	namespace utils {
		size_t ByteBuffer::getReadPosition() const {
			return readPosition;
		}
		
		void ByteBuffer::setReadPosition(size_t readPosition) {
			ByteBuffer::readPosition = readPosition;
		}
		
		size_t ByteBuffer::getWritePosition() const {
			return writePosition;
		}
		
		void ByteBuffer::setWritePosition(size_t writePosition) {
			ByteBuffer::writePosition = writePosition;
		}
		
		lang::ByteArray *ByteBuffer::getArray() const {
			return array.get();
		}
		
		void ByteBuffer::put(int8_t byte) {
			if (writePosition + 1 > capacity) {
				throw OutOfIndexException();
			}
			array->operator[](arrayOffset + writePosition++) = byte;
		}
		
		void ByteBuffer::put(int16_t s) {
			if (writePosition + 2 > capacity) {
				throw OutOfIndexException();
			}
			s = ntohs(s);
			array->set(arrayOffset + writePosition, (int8_t *) &s, 2);
		}
		
		void ByteBuffer::put(int32_t i) {
			if (writePosition + 4 > capacity) {
				throw OutOfIndexException();
			}
			i = ntohl(i);
			array->set(arrayOffset + writePosition, (int8_t *) &i, 4);
		}
		
		void ByteBuffer::put(int64_t l) {
			if (writePosition + 8 > capacity) {
				throw OutOfIndexException();
			}
			l = be64toh(l);
			array->set(arrayOffset + writePosition, (int8_t *) &l, 8);
		}
		
		void ByteBuffer::put(float f) {
			put(*((int32_t *) &f));
		}
		
		void ByteBuffer::put(double d) {
			put(*((int64_t *) &d));
		}
		
		size_t ByteBuffer::getArrayOffset() const {
			return arrayOffset;
		}
		
		int8_t ByteBuffer::get() {
			if (readPosition >= writePosition) {
				throw OutOfIndexException();
			}
			return array->operator[](arrayOffset + readPosition++);
		}
		
		size_t ByteBuffer::getCapacity() const {
			return capacity;
		}
		
		int16_t ByteBuffer::getShort() {
			if (readPosition + 2 > writePosition) {
				throw OutOfIndexException();
			}
			int16_t s;
			array->get(arrayOffset + readPosition, (int8_t *) &s, 2);
			readPosition += 2;
			s = htons(s);
			return s;
		}
		
		int32_t ByteBuffer::getInt() {
			if (readPosition + 4 > writePosition) {
				throw OutOfIndexException();
			}
			int32_t i;
			array->get(arrayOffset + readPosition, (int8_t *) &i, 4);
			readPosition += 4;
			i = htonl(i);
			return i;
		}
		
		int64_t ByteBuffer::getLong() {
			if (readPosition + 8 > writePosition) {
				throw OutOfIndexException();
			}
			int64_t l;
			array->get(arrayOffset + readPosition, (int8_t *) &l, 8);
			readPosition += 8;
			l = htobe64(l);
			return l;
		}
		
		float ByteBuffer::getFloat() {
			auto f = getInt();
			return *((float *) &f);
		}
		
		double ByteBuffer::getDouble() {
			auto d = getLong();
			return *((double *) &d);
		}
		
		const char *ByteBuffer::getBuffer() const {
			return array->getBuffer();
		}
		
		char *ByteBuffer::getBuffer() {
			return array->getBuffer() + arrayOffset;
		}
		
		char *ByteBuffer::getReadBuffer() {
			return array->getBuffer() + arrayOffset + readPosition;
		}
		
		char *ByteBuffer::getWriteBuffer() {
			return array->getBuffer() + arrayOffset + writePosition;
		}
		
		size_t ByteBuffer::getReadableSize() const {
			return writePosition - readPosition;
		}
		
		size_t ByteBuffer::getWriteableSize() const {
			return capacity - writePosition;
		}
		
		const char *ByteBuffer::getReadBuffer() const {
			return array->getBuffer() + arrayOffset + readPosition;
		}
		
		ByteBuffer::ByteBuffer(
				std::shared_ptr<cplus::lang::ByteArray> array,
				size_t arrayOffset,
				size_t capacity,
				size_t readPosition,
				size_t writePosition
		) : array(array),
		    arrayOffset(arrayOffset),
		    capacity(capacity),
		    readPosition(readPosition),
		    writePosition(writePosition) {
			if (capacity < 0) {
				cplus::memory::copy(array->getSize(), this->capacity);
			}
		}
		
		lang::String ByteBuffer::getString() {
			return lang::String(getReadBuffer(), readSize(getReadableSize()));
		}
		
		size_t ByteBuffer::readSize(size_t size) const {
			size_t position = readPosition;
			cplus::memory::copy(readPosition + size, readPosition);
			return position;
		}
		
		size_t ByteBuffer::writeSize(size_t size) const {
			size_t position = writePosition;
			cplus::memory::copy(writePosition + size, writePosition);
			return position;
		}
	}
}
