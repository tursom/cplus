//
// Created by Tursom Ulefits on 2018/5/17.
//

#include <cmath>
#include "Double.h"
#include "String.h"
#include "Float.h"

namespace cplus {
	namespace lang {
		String Double::toString() const {
			char str[20];
			sprintf(str, "%e", value);
			return String(str);
		}
		
		Double::operator double() const {
			return value;
		}
		
		String Double::toString(double value) {
			char str[20];
			sprintf(str, "%e", value);
			return String(str);
		}
		
		Double Double::operator+(const Double &aDouble) const {
			return Double(value + aDouble.value);
		}
		
		Double Double::operator-(const Double &aDouble) const {
			return Double(value - aDouble.value);
		}
		
		Double Double::operator*(const Double &aDouble) const {
			return Double(value * aDouble.value);
		}
		
		Double Double::operator/(const Double &aDouble) const {
			return Double(value / aDouble.value);
		}
		
		Double Double::operator^(const Double &aDouble) const {
			return Double(pow(value, aDouble.value));
		}
	}
}
