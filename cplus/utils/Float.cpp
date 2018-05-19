//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Float.h"
#include "String.h"

namespace cplus {
	namespace utils {
		String Float::toString() const {
			char str[20];
			sprintf(str, "%e", value);
			return String(str);
		}
		
		Float::operator float() const {
			return value;
		}
		
		String Float::toString(float value) {
			char str[20];
			sprintf(str, "%e", value);
			return String(str);
		}
		
		Float Float::qRSqrt() {
			long i;
			float x2 = value * 0.5F;
			float y = value;
//			static const float threehalfs = 1.5F;
			
			i = *(long *) &y;                        // evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);               // what the fuck?
			y = *(float *) &i;
//			y = y * (threehalfs - (x2 * y * y));   // 1st iteration
//			y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed
			return Float(y);
		}
	}
}
