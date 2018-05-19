//
// Created by Tursom Ulefits on 2018/5/18.
//

#ifndef CPLUS_UTILS_LIST_HPP
#define CPLUS_UTILS_LIST_HPP

#include <functional>
#include "StringBuilder.h"
#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(List) {
		public:
			List() : state(new ListPoint()), liseSize(1) {
				listBegin = state;
				listEnd = state;
				preview = state;
			}
			
			explicit List(const T &value) : state(new ListPoint()), liseSize(1) {
				listBegin = state;
				listEnd = state;
				preview = state;
				state->set(value);
			}
			
			~List() {
				reset(); //指针复位
				do {
					next(); //next只调用state的函数，对于上一个元素只需要地址即可
					delete preview; //删除上一个元素
				} while (state != listBegin); //遍历所有元素
			}
			
			inline List &append(const T &value) {
				listEnd = new ListPoint(listEnd, listBegin, value);
				++liseSize;
				return *this;
			}
			
			inline size_t size() const { return liseSize; }
			
			inline void reset() {
				state = listBegin;
				preview = listEnd;
			}
			
			inline T &get() { return state->get(); }
			
			inline const T &get() const { return state->get(); }
			
			inline T &begin() { return listBegin->get(); }
			
			inline const T &begin() const { return listBegin->get(); }
			
			inline T &end() { return listEnd->get(); }
			
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
			
			void forEach(const std::function<void(void)> &func) {
				saveState();
				reset();
				do {
					func();
					next();
				} while (state != listBegin);
				loadState();
			}
			
			//主要是糊弄IDE（Clion）用
			inline void forEach(void(*func)()) { forEach([&]() { func(); }); }
			
			inline void loadState() {
				preview = prevSave;
				state = stateSave;
			}
			
			inline void saveState() {
				prevSave = preview;
				stateSave = state;
			}
			
			inline size_t pointSize() { return sizeof(ListPoint); }
			
			inline size_t usedSize() {
				return sizeof(*this) + sizeof(ListPoint) * size();
			}
			
			inline String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::List(");
				stringBuilder.append("size:");
				stringBuilder.append(size());

//				ListPoint *preview = this->preview;
//				ListPoint *state = this->state;
//				ListPoint *next;
//				do {
//					stringBuilder.append(state->toString());
//					next = state->next(preview);
//					preview = state;
//					state = next;
//				} while (state != listBegin);
				
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
		
		private:
			/**
			 * 双向链表节点
			 */
			CPlusClass(ListPoint) {
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
			
			ListPoint *listBegin;
			ListPoint *listEnd;
			ListPoint *preview;
			ListPoint *state;
			ListPoint *prevSave; //用于储存上一次保存时的状态
			ListPoint *stateSave; //用于储存上一次保存时的状态
			size_t liseSize;
		};
	}
}

#endif //CPLUS_UTILS_LIST_HPP
