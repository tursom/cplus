//
// Created by Tursom Ulefits on 2018/5/16.
//

#ifndef CPLUS_UTILS_String_H
#define CPLUS_UTILS_String_H

#include <string>
#include <utility>
#include <memory>
#include "Object.h"

namespace cplus {
    namespace lang {
        class String : public Object {
        public:
            explicit String(const char *&str) { value = std::make_shared<std::string>(str); }

            explicit String(const std::string &str) { value = std::make_shared<std::string>(str); }

            String toString() const override;


            /**
             * 目前实现方式是使用标准库string的c_str函数，
             * 不保证时间复杂度位常数
             * @return
             */
            const char *c_str() const { return value->c_str(); }

            String &operator=(const String &string);

            /**
             * 返回一个标准库的string对象
             * 不保证返回的绝对是const引用
             * 不保证向下兼容性
             * @return 一个对应的标准库的string对象
             */
            const std::string &__stdString() const { return *value; }

        private:

            std::shared_ptr<const std::string> value;
        };
    }
}


#endif //CPLUS_UTILS_String_H
