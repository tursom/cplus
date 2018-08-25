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
	namespace lang {
		CPlusClass(Char) {
		public:
			Char();

			explicit Char(char value);

			inline char get() const { return value; }

			inline char &get() { return value; }

			String toString() const override;

			explicit operator char() { return value; }

			static String toString(char value);

		private:
			char value;
		};
	}
}


#endif //UNTITLED_CHAR_H
