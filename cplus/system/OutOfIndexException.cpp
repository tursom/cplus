/**
 * file name: OutOfIndexException
 *
 * author: Tursom K. Ulefits
 * email: tursom@foxmail.com
 * qq: 737097096
 * create date:  18-8-25 下午2:40
 */

#include "OutOfIndexException.h"

namespace cplus {
	namespace system {
		OutOfIndexException::OutOfIndexException() : Exception() {}

		OutOfIndexException::OutOfIndexException(const char *message)
				: Exception(message) {}

		OutOfIndexException::OutOfIndexException(const lang::String &message)
				: Exception(message) {}
	}
}