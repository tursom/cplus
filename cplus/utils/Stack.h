//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_STACK_H
#define CPLUS_STACK_H

#include <functional>
#include "StringBuilder.h"
#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(Stack) {
		public:
			Stack() : Stack(1024) {}
			
			explicit Stack(size_t maxSize) : state(nullptr), stackSize(0), maxSize(maxSize) {}
			
			~Stack() {
				auto stateSave = state;
				while (state != nullptr) {//遍历所有元素
					auto state = this->state; //next只调用state的函数，对于上一个元素只需要地址即可
					this->state = this->state->prev();
					delete state; //删除上一个元素
				}
			}
			
			bool push(const T &value) {
				if (stackSize < maxSize) {
					state = new StackPoint(state, value);
					++stackSize;
					return true;
				} else {
					return false;
				}
			}
			
			const T &pop() {
				if (stackSize != 0) {
					lastValue = this->state->get();
					auto state = this->state;
					this->state = this->state->prev();
					delete state;
					--stackSize;
				}
				return lastValue;
			}
			
			inline size_t size() const { return stackSize; }
			
			inline T &get() { return lastValue; }
			
			inline const T &get() const { return lastValue; }
			
			inline void set(const T &value) { if (state != nullptr)state->set(value); }
			
			void forEach(const std::function<void(void)> &func) {
				StackPoint *state = this->state;
				while (state != nullptr) {
					lastValue = state->get();
					state = state->prev();
					func();
				}
			}
			
			bool isVoid() { return stackSize == 0; }
			
			//主要是糊弄IDE（Clion）用
			inline void forEach(void(*func)()) const { forEach([&]() { func(); }); }
			
			inline size_t pointSize() { return sizeof(StackPoint); }
			
			inline size_t usedSize() {
				return sizeof(*this) + sizeof(StackPoint) * size();
			}
			
			inline String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::Stack(");
				stringBuilder.append("stack size:");
				stringBuilder.append(size());
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
		
		private:
			/**
			 *单向链表节点
			 */
			CPlusClass(StackPoint) {
			public:
				StackPoint() : preview(nullptr) {}
				
				StackPoint(StackPoint *prev, const T &value) : preview(prev), value(value) {}
				
				inline void del(StackPoint *next) { next->preview = preview; }
				
				inline T &get() { return value; }
				
				inline const T &get() const { return value; }
				
				inline void set(const T &value) { this->value = value; }
				
				inline StackPoint *prev() { return preview; }
				
				inline void setPrev(StackPoint *prev) { this->preview = prev; }
			
			private:
				T value;
				StackPoint *preview;
			};
			
			size_t maxSize;
			StackPoint *state;
			T lastValue;
			size_t stackSize;
		};
	}
}


#endif //CPLUS_STACK_H
