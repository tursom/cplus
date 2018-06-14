//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef CPLUS_UTILS_Float_H
#define CPLUS_UTILS_Float_H

#include <cfloat>
#include "../tools/class.h"
#include "Double.h"

namespace cplus {
	namespace lang {
		CPlusClass(Float) {
		public:
			explicit Float(float f) : value(f) {}
			
			float get() const { return value; }
			
			float &get() { return value; }
			
			String toString() const override;
			
			Float qRSqrt();
			
			explicit operator float() const;
			
			explicit operator Double() { return Double(value); }
			
			static String toString(float value);
		
		private:
			float value;
		};
	}
}

#endif //CPLUS_UTILS_Float_H
