//
// Created by Tursom Ulefits on 2018/5/18.
//

#ifndef CPLUS_UTILS_LIST_HPP
#define CPLUS_UTILS_LIST_HPP

#include <functional>
#include "StringBuilder.h"
#include "Stack.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"
#include "../thread/RunnableBase.h"

typedef unsigned int cplus_list_size_t;

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(List) {
		public:
			
			List() : List(10240) {}
			
			explicit List(cplus_list_size_t maxSize) : state(nullptr), listSize(0), maxSize(maxSize), array(nullptr) {
				listBegin = state;
				listEnd = state;
				preview = state;
			}
			
			~List() {
				reset(); //指针复位
				while (state != listEnd) {
					next(); //next只调用state的函数，对于上一个元素只需要地址即可
					delete preview; //删除上一个元素
				}
				if (state != nullptr)delete state; //遍历所有元素
				if (array != nullptr) delete[] array;
			}
			
			bool append(const T &value) {
				if (state == nullptr) {
					state = new ListPoint(listEnd, listBegin, value);
					listEnd = listBegin = preview = state;
				} else if (listSize != maxSize) {
					listEnd = new ListPoint(listEnd, listBegin, value);
					++listSize;
				} else {
					return false;
				}
				return true;
			}
			
			inline cplus_list_size_t size() const { return listSize; }
			
			inline void reset() {
				state = listBegin;
				preview = listEnd;
			}
			
			inline T &get() { return state->get(); }
			
			inline const T &get() const { return state->get(); }
			
			inline T &begin() { return listBegin->get(); }
			
			inline const T &begin() const { return listBegin->get(); }
			
			T &end() { return listEnd->get(); }
			
			const T &end() const { return listEnd->get(); }
			
			inline bool isBegin() const { return state == listBegin; }
			
			inline bool isEnd() const { return state == listEnd; }
			
			inline void next() {
				auto next = state->next(preview);
				preview = state;
				state = next;
			}
			
			inline void prev() {
				auto next = state;
				state = preview;
				preview = state->prev(next);
			}
			
			void forEach(const std::function<void(T &)> &func) const {
				auto state = listBegin;
				auto preview = listEnd;
				if (state != nullptr) {
					do {
						func(state->get());
						auto next = state->next(preview);
						preview = state;
						state = next;
					} while (state != listBegin);
				}
			}
			
			void forEach(cplus::thread::RunnableBase<T &> runnable) const {
				auto state = listBegin;
				auto preview = listEnd;
				if (state != nullptr) {
					do {
						runnable(state->get());
						auto next = state->next(preview);
						preview = state;
						state = next;
					} while (state != listBegin);
				}
			}
			
			inline cplus_list_size_t pointSize() const { return sizeof(ListPoint); }
			
			inline cplus_list_size_t usedSize() const {
				return sizeof(*this) + sizeof(ListPoint) * size();
			}
			
			T *toArray() {
				if (array != nullptr) delete array;
				array = new T[size()];
				cplus_list_size_t p = 0;
				forEach([&](T &value) {
					::cplus::memory::copy(value, array[p++]);
				});
				return array;
			};
			
			std::unique_ptr<T[]> toSmartArray() {
				std::unique_ptr<T[]> array(new T[size()]);
				cplus_list_size_t p = 0;
				forEach([&](T &value) {
					::cplus::memory::copy(value, array[p++]);
				});
				return array;
			};
			
			inline ::cplus::lang::String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::List(");
				stringBuilder.append("size:");
				stringBuilder.append((long) size());
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
			
			bool isFull() {
				return listSize >= maxSize;
			}
		
		private:
			/**
			 * 双向链表节点
			 */
			class ListPoint {
			public:
				ListPoint() : nextAndPrev(nullptr) {}
				
				ListPoint(ListPoint *prev, ListPoint *next, const T &value) : nextAndPrev(
						reinterpret_cast<ListPoint *>((intptr_t) next ^ (intptr_t) prev)), value(value) {
					if (next != nullptr) {
						next->setNextAndPrev(next->next(prev), this);
					}
					if (prev != nullptr) {
						prev->setNextAndPrev(this, prev->prev(next));
					}
				}
				
				inline T &get() { return value; }
				
				inline const T &get() const { return value; }
				
				inline void set(const T &value) { this->value = value; }
				
				inline ListPoint *next(ListPoint *prev) {
					return reinterpret_cast<ListPoint *>((intptr_t) nextAndPrev ^ (intptr_t) prev);
				}
				
				inline ListPoint *prev(ListPoint *next) {
					return reinterpret_cast<ListPoint *>((intptr_t) nextAndPrev ^ (intptr_t) next);
				}
				
				inline void setNextAndPrev(ListPoint *prev, ListPoint *next) {
					nextAndPrev = reinterpret_cast<ListPoint *>((intptr_t) next ^ (intptr_t) prev);
				}
			
			private:
				T value;
				ListPoint *nextAndPrev;
			};
			
			inline void constReset() const {
				::cplus::memory::copy(listBegin, state);
				::cplus::memory::copy(listEnd, preview);
			}
			
			inline void constNext() const {
				auto next = state->next(preview);
				::cplus::memory::copy(state, preview);
				::cplus::memory::copy(next, state);
			}
			
			
			T *array;
			ListPoint *listBegin;
			ListPoint *listEnd;
			ListPoint *preview;
			ListPoint *state;
			cplus_list_size_t listSize;
			cplus_list_size_t maxSize;
		};
	}
}

#endif //CPLUS_UTILS_LIST_HPP
