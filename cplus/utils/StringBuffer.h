//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_STRINGBUFFER_H
#define UNTITLED_STRINGBUFFER_H

#include "../tools/class.h"
#include "../thread/ThreadMutex.h"

namespace cplus {
	namespace utils {
		CPlusClass(StringBuffer) {
		public:
			StringBuffer &append(const ::cplus::lang::String &string);
			
			::cplus::lang::String toString() const override;
		
		private:
			::cplus::thread::ThreadMutex mutex;
			::std::string value;
		};
	}
}


#endif //UNTITLED_STRINGBUFFER_H
