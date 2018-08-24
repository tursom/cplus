//
// Created by Tursom Ulefits on 2018/5/17.
//

#include "Short.h"
#include "../utils/Set.hpp"

namespace cplus {
	namespace lang {
		String Short::toString() const {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}

		String Short::toString(int16_t value) {
			char str[12];
			sprintf(str, "%d", value);
			return String(str);
		}

		const Short &Short::get(short value) {
			static utils::Set<Short> shortSet;
			return *shortSet.get(Short(value));
		}

		bool Short::operator<(const Short &rhs) const {
			return value < rhs.value;
		}

		bool Short::operator>(const Short &rhs) const {
			return rhs < *this;
		}

		bool Short::operator<=(const Short &rhs) const {
			return !(rhs < *this);
		}

		bool Short::operator>=(const Short &rhs) const {
			return !(*this < rhs);
		}

		bool Short::operator==(const Short &rhs) const {
			return value == rhs.value;
		}

		bool Short::operator!=(const Short &rhs) const {
			return !(rhs == *this);
		}
	}
}