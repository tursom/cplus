//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_STACK_H
#define CPLUS_STACK_H

#include <functional>
#include "StringBuilder.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"
#include "../thread/Runnable.h"

namespace cplus {
	namespace utils {
		/**
		 * <h5>Stack 堆栈</h5>
		 * 堆栈结构，内部使用单向链表实现。如果仅仅是需要堆栈结构，推荐使用ArrayStack，更加节省内存<br>
		 * 为防止内存溢出，添加了最大节点数限制<br>
		 * @tparam T
		 */
		template<typename T>
		CPlusClass(Stack) {
		public:
			/**
			 * Stack默认构造函数<br>
			 * 将构造任务传递给Stack(1024)，实现默认最大节点数为1024<br>
			 */
			Stack() : Stack(1024) {}
			
			/**
			 * @param maxSize 最大节点数量
			 */
			explicit Stack(size_t maxSize) : state(nullptr), stackSize(0), maxSize(maxSize) {}
			
			/**
			 * Stack析构函数
			 * 遍历每一个节点并
			 */
			~Stack() {
				auto stateSave = state;
				while (state != nullptr) {//遍历所有元素
					auto next = state; //储存上一个元素的地址
					state = state->prev();
					delete next; //释放上一个元素占用的内存
				}
			}
			
			/**
			 * 压值入栈
			 * @param value 压入栈的值
			 * @return 成功与否
			 */
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
					::cplus::memory::copy(this->state->get(), lastValue);
					auto state = this->state;
					this->state = this->state->prev();
					delete state;
					--stackSize;
				}
				return lastValue;
			}
			
			bool pop(const T &buffer) {
				if (stackSize != 0) {
					::cplus::memory::copy(this->state->get(), lastValue);
					auto state = this->state;
					this->state = this->state->prev();
					delete state;
					--stackSize;
					::cplus::memory::copy(lastValue, buffer);
					return true;
				} else {
					return false;
				}
			}
			
			inline size_t size() const { return stackSize; }
			
			inline T &get() { return lastValue; }
			
			inline const T &get() const { return lastValue; }
			
			inline void set(const T &value) { if (state != nullptr)state->set(value); }
			
			void forEach(const std::function<void(void)> &func) {
				StackPoint *state = this->state;
				while (state != nullptr) {
					::cplus::memory::copy(state->get(), lastValue);
					state = state->prev();
					func();
				}
			}
			
			void forEach(cplus::thread::Runnable runnable) {
				StackPoint *state = this->state;
				while (state != nullptr) {
					::cplus::memory::copy(state->get(), lastValue);
					state = state->prev();
					runnable.run();
				}
			}
			
			bool isFull() { return stackSize == maxSize; }
			
			bool isVoid() { return stackSize == 0; }
			
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
				
				StackPoint(StackPoint *prev, const T &value) : preview(prev) {
					cplus::memory::copy(value, this->value);
				}
				
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
