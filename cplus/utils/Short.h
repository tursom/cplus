//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_SHORT_H
#define UNTITLED_SHORT_H

#include <cstdint>
#include "String.h"
#include "Int.h"
#include "Long.h"
#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		CPlusClass(Short) {
		public:
			explicit Short(int16_t value) : value(value) {}
			
			int16_t get() const { return value; }
			
			int16_t &get() { return value; }
			
			String toString() const override;
			
			explicit operator int16_t() { return value; }
			
			explicit operator Int() { return Int(value); }
			
			explicit operator Long() { return Long(value); }
			
			static String toString(int16_t value);
		
		private:
			int16_t value;
		};
	}
}


#endif //UNTITLED_SHORT_H
