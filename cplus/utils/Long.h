//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_Long_H
#define CPLUS_UTILS_Long_H


#include <cstdint>
#include "Object.h"
#include "String.h"
#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		class Float;
		
		CPlusClass(Long) {
		public:
			explicit Long(int64_t value) : value(value) {}
			
			inline int64_t get() const { return value; }
			
			inline int64_t &get() { return value; }
			
			String toString() const override;
			
			static String toString(int64_t value);
			
			inline explicit operator int64_t();
		
		private:
			int64_t value;
		};
	}
}


#endif //CPLUS_UTILS_Long_H
