/**
 * file name: OutOfIndexException
 *
 * author: Tursom K. Ulefits
 * email: tursom@foxmail.com
 * qq: 737097096
 * create date:  18-8-25 下午2:40
 */

#ifndef CPLUS_OUTOFINDEXEXCEPTION_H
#define CPLUS_OUTOFINDEXEXCEPTION_H


#include "Exception.h"

namespace cplus {
	namespace system {
		class OutOfIndexException : public Exception {
		public:
			OutOfIndexException();

			explicit OutOfIndexException(const char *message);

			explicit OutOfIndexException(const lang::String &message);
		};
	}
}
#endif //CPLUS_OUTOFINDEXEXCEPTION_H
