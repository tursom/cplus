//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_SIZE_H
#define CPLUS_SIZE_H

#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		CPlusClass(Size) {
		public:
			explicit Size(size_t value) : value(value) {}
			
			inline size_t get() const { return value; }
			
			inline size_t &get() { return value; }
			
			String toString() const override;
			
			inline static String toString(size_t value);
			
			inline explicit operator size_t() { return value; }
		
		private:
			size_t value;
		};
	}
}


#endif //CPLUS_SIZE_H
