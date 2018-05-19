//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_Object_H
#define CPLUS_UTILS_Object_H


#include <ostream>

namespace cplus {
	namespace utils {
		class String;
		
		class Object {
		public:
			virtual String toString() const;
			
			explicit virtual operator ::cplus::utils::String() const;

//            friend std::ostream &operator<<(std::ostream &os, const Object &object);
		};
	}
}

#endif //CPLUS_UTILS_Object_H
