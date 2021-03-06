//
// Created by Tursom Ulefits on 2018/6/15.
//

#include "Byte.h"

namespace cplus {
	namespace lang {
		int8_t Byte::get() const {
			return value;
		}

		void Byte::set(int8_t value) {
			this->value = value;
		}

		void Byte::set(Byte value) {
			this->value = value.value;
		}

		String Byte::toBinString() const {
			char buffer[9];
			buffer[8] = 0;
			binToString(value, buffer);
			return String(buffer);
		}

		String Byte::toHexString() const {
			char buffer[3];
			buffer[2] = 0;
			binToHex(value, buffer);
			return String(buffer);
		}

		String Byte::toString() const {
			return toHexString();
		}

		void Byte::binToString(char value, char *buffer) {
			buffer[7] = ((value & 0x1) == 0 ? '0' : '1');
			buffer[6] = ((value & 0x2) == 0 ? '0' : '1');
			buffer[5] = ((value & 0x4) == 0 ? '0' : '1');
			buffer[4] = ((value & 0x8) == 0 ? '0' : '1');
			buffer[3] = ((value & 0x10) == 0 ? '0' : '1');
			buffer[2] = ((value & 0x20) == 0 ? '0' : '1');
			buffer[1] = ((value & 0x40) == 0 ? '0' : '1');
			buffer[0] = ((value & 0x80) == 0 ? '0' : '1');
		}

		void Byte::binToHex(char value, char *buffer) {
			static char str[] = {
					'0', '1', '2', '3', '4', '5', '6', '7',
					'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
			};
			buffer[1] = str[value & 0xf];
			buffer[0] = str[(value >> 4) & 0xf];
		}

		Byte::Byte() : Byte(0) {}

		Byte::Byte(int8_t value) : value(value) {}
	}
}