//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_OUTPUTSTREAM_H
#define UNTITLED_OUTPUTSTREAM_H

#include "../tools/class.h"

namespace cplus {
	namespace system {
		CPlusClass(OutputStream) {
		public:
			explicit OutputStream(std::ostream &os) : os(&os) {}
			
			const OutputStream &operator<<(const ::cplus::utils::Object &object) const;
			
			const OutputStream &operator<<(const char *str) const;
			
			const OutputStream &operator<<(int value) const;
			
			const OutputStream &operator<<(unsigned int value) const;
			const OutputStream &operator<<(long value) const;
			
			const OutputStream &operator<<(unsigned long value) const;
			
			const OutputStream &operator<<(long long value) const;
			
			const OutputStream &operator<<(unsigned long long value) const;
			
			const OutputStream &operator<<(double value) const;
		
		private:
			std::ostream *os;
		};
		
		extern OutputStream sout;
		extern ::cplus::utils::String endl;
	}
}


#endif //UNTITLED_OUTPUTSTREAM_H
