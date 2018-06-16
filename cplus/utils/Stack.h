//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_STACK_H
#define CPLUS_STACK_H

#include <functional>
#include "StringBuilder.h"
#include "../lang/String.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"
#include "../thread/RunnableBase.h"

typedef unsigned int cplus_queue_size_t;

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
			explicit Stack(cplus_queue_size_t maxSize) : state(nullptr), stackSize(0), maxSize(maxSize) {}
			
			/**
			 * Stack析构函数
			 * 遍历每一个节点并
			 */
			~Stack() {
				if (lastState != nullptr) {
					delete lastState;
					lastState = nullptr;
				}
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
				if (lastState != nullptr) {
					delete lastState;
					lastState = nullptr;
				}
				if (stackSize != 0) {
					lastState = this->state;
					this->state = this->state->prev();
					--stackSize;
				}
				return lastState->get();
			}
			
			bool pop(const T &buffer) {
				if (lastState != nullptr) {
					delete lastState;
					lastState = nullptr;
				}
				if (stackSize != 0) {
					::cplus::memory::copy(this->state->get(), buffer);
					lastState = this->state;
					this->state = this->state->prev();
					--stackSize;
					return true;
				} else {
					return false;
				}
			}
			
			inline cplus_queue_size_t size() const { return stackSize; }
			
			cplus_queue_size_t getMaxSize() const {
				return maxSize;
			}
			
			inline T &get() { return state->get(); }
			
			inline const T &get() const { return state->get(); }
			
			inline void set(const T &value) { if (state != nullptr)state->set(value); }
			
			void forEach(std::function<void(T &)> func) const {
				StackPoint *state = this->state;
				while (state != nullptr) {
					func(state->get());
					state = state->prev();
				}
			}
			
			bool isFull() const { return stackSize == maxSize; }
			
			bool isVoid() const { return stackSize == 0; }
			
			inline cplus_queue_size_t pointSize() const { return sizeof(StackPoint); }
			
			inline cplus_queue_size_t usedSize() const {
				return sizeof(*this) + sizeof(StackPoint) * size();
			}
			
			inline ::cplus::lang::String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::Stack(");
				stringBuilder.append("stack size:");
				stringBuilder.append((long) size());
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
			
			
			cplus_queue_size_t maxSize;
			StackPoint *state;
			StackPoint *lastState;
			cplus_queue_size_t stackSize;
		};
	}
}

#endif //CPLUS_STACK_H
