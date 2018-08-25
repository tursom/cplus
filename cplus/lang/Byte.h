//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_BYTE_H
#define CPLUS_BYTE_H

#include "../tools/class.h"
#include "String.h"

namespace cplus {
	namespace lang {
		CPlusClass(Byte) {
		public:
			Byte();

			explicit Byte(int8_t value);

			int8_t get() const;

			void set(int8_t value);

			void set(Byte value);

			String toBinString() const;

			String toHexString() const;

			String toString() const override;

			static void binToString(char value, char *buffer);

			static inline void binToHex(char value, char *buffer);

		private:
			int8_t value{};
		};
	}
}

#endif //CPLUS_BYTE_H
