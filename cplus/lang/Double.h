//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_DOUBLE_H
#define UNTITLED_DOUBLE_H

#include "../tools/class.h"

namespace cplus {
	namespace lang {
		class Float;
		
		CPlusClass(Double) {
		public:
			explicit Double(double value) : value(value) {}
			
			double get() const { return value; }
			
			double &get() { return value; }
			
			String toString() const override;
			
			explicit operator double() const;
			
			static String toString(double value);
			
			Double operator+(const Double &aDouble) const;
			
			Double operator-(const Double &aDouble) const;
			
			Double operator*(const Double &aDouble) const;
			
			Double operator/(const Double &aDouble) const;
			
			Double operator^(const Double &aDouble) const;
		
		private:
			double value;
		};
	}
}

#endif //UNTITLED_DOUBLE_H
