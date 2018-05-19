//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "String.h"

namespace cplus {
    namespace utils {
//        std::ostream &operator<<(std::ostream &os, const String &string) {
//            os << *string.value;
//        }

        String &String::operator=(const String &string) {
            value = string.value;
            return *this;
        }

        String String::toString() const {
            return *this;
        }
    }
}