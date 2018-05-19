//
// Created by Tursom Ulefits on 2018/5/17.
//

#ifndef UNTITLED_OUTPUTSTREAM_H
#define UNTITLED_OUTPUTSTREAM_H

#include "../tools/Class.h"

namespace cplus {
	namespace system {
		CPlusClass(OutputStream) {
		public:
			explicit OutputStream(std::ostream &os) : os(&os) {}
			
			inline const OutputStream &operator<<(const ::cplus::utils::Object &object) const;
			
			inline const OutputStream &operator<<(const char *str) const;
			
			inline const OutputStream &operator<<(int value) const;
			
			inline const OutputStream &operator<<(unsigned int value) const;
			inline const OutputStream &operator<<(long value) const;
			
			inline const OutputStream &operator<<(unsigned long value) const;
			
			inline const OutputStream &operator<<(long long value) const;
			
			inline const OutputStream &operator<<(unsigned long long value) const;
			
			inline const OutputStream &operator<<(double value) const;
		
		private:
			std::ostream *os;
		};
		
		extern OutputStream sout;
		extern ::cplus::utils::String endl;
	}
}


#endif //UNTITLED_OUTPUTSTREAM_H
