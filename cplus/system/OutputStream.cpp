//
// Created by Tursom Ulefits on 2018/5/17.
//

#include <iostream>

#include "OutputStream.h"
#include "../utils/String.h"
#include "../utils/Long.h"

namespace cplus {
	namespace system {
		inline const ::cplus::system::OutputStream &
		::cplus::system::OutputStream::operator<<(const ::cplus::utils::Object &object) const {
			(*os) << object.toString().__stdString();
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(const char *str) const {
			(*os) << str;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(int value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(unsigned int value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(long value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(unsigned long value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(long long value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(unsigned long long value) const {
			(*os) << value;
			return *this;
		}
		
		inline const OutputStream &OutputStream::operator<<(double value) const {
			(*os) << value;
			return *this;
		}
		
		OutputStream sout(std::cout);
		::cplus::utils::String endl("\n");
	}
}
