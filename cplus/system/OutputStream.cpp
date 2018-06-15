//
// Created by Tursom Ulefits on 2018/5/17.
//

#include <iostream>

#include "OutputStream.h"
#include "../lang/String.h"
#include "../lang/Long.h"

namespace cplus {
	namespace system {
		const ::cplus::system::OutputStream &
		::cplus::system::OutputStream::operator<<(const ::cplus::lang::Object &object) const {
			(*os) << object.toString().stdString();
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(const char *str) const {
			(*os) << str;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(int value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(unsigned int value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(long value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(unsigned long value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(long long value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(unsigned long long value) const {
			(*os) << value;
			return *this;
		}
		
		const OutputStream &OutputStream::operator<<(double value) const {
			(*os) << value;
			return *this;
		}
		
		OutputStream sout(std::cout);
		::cplus::lang::String endl("\n");
	}
}
