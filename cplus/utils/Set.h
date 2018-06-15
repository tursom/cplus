//
// Created by Tursom Ulefits on 2018/6/15.
//

#ifndef CPLUS_SET_H
#define CPLUS_SET_H

#include "../tools/class.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(Set) {
		public:
		
		private:
			class Three {
			public:
				static inline bool red() { return false; }
				
				static inline bool black() { return true; }
				
				bool color = static_cast<bool>(black);
				Set *parent = nullptr;
				Set *left = nullptr;
				Set *right = nullptr;
				T *key = nullptr;
			};
			
			Three *root;
		};
	}
}

#endif //CPLUS_SET_H
