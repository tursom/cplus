//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_Int_H
#define CPLUS_UTILS_Int_H

#include "Object.h"
#include "Long.h"
#include <cstdint>

namespace cplus {
	namespace lang {
		class Int : public Object {
		public:
			explicit Int(int32_t value) : value(value) {}
			
			int32_t get() const { return value; }
			
			int32_t &get() { return value; }
			
			String toString() const override;
			
			explicit operator Long() { return Long(value); }
			
			static String toString(int32_t value);
		
		private:
			int32_t value;
		};
	}
}

#endif //CPLUS_UTILS_Int_H
