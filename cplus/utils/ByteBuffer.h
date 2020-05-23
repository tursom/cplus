//
// Created by tursom on 2020/5/23.
//

#ifndef CPLUS_BYTEBUFFER_H
#define CPLUS_BYTEBUFFER_H

#include <cstddef>
#include <cstdlib>
#include "../tools/class.h"
#include "../lang/ByteArray.h"


namespace cplus {
	namespace utils {
		CPlusClass(ByteBuffer) {
		public:
			size_t getReadPosition() const;
			
			void setReadPosition(size_t readPosition);
			
			size_t getWritePosition() const;
			
			void setWritePosition(size_t writePosition);
			
			lang::ByteArray *getArray() const;
			
			const char *getBuffer() const;
			
			char *getBuffer();
			
			size_t getArrayOffset() const;
			
			size_t getCapacity() const;
			
			void put(int8_t byte);
			
			void put(int16_t s);
			
			void put(int32_t i);
			
			void put(int64_t l);
			
			void put(float f);
			
			void put(double d);
			
			int8_t get();
			
			int16_t getShort();
			
			int32_t getInt();
			
			int64_t getLong();
			
			float getFloat();
			
			double getDouble();
		
		private:
			cplus::lang::ByteArray *array{};
			const size_t arrayOffset{0};
			const size_t capacity{array->getSize()};
			size_t readPosition{0};
			size_t writePosition{0};
		};
	}
}

#endif //CPLUS_BYTEBUFFER_H
