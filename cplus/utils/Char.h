//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_CHAR_H
#define UNTITLED_CHAR_H

#include <cstdint>
#include "Short.h"
#include "Int.h"
#include "Long.h"
#include "../tools/class.h"

namespace cplus {
	namespace utils {
		CPlusClass(Char) {
		public:
			Char() : Char(0) {}
			
			explicit Char(int8_t value) : value(value) {}
			
			inline int8_t get() const { return value; }
			
			inline int8_t &get() { return value; }
			
			String toString() const override;
			
			explicit operator int8_t() { return value; }
			
			static String toString(int8_t value);
		
		private:
			int8_t value;
		};
	}
}


#endif //UNTITLED_CHAR_H
