//
// Created by Tursom Ulefits on 2018/5/18.
//

#ifndef CPLUS_UTILS_ListArray_HPP
#define CPLUS_UTILS_ListArray_HPP

#include <functional>
#include "StringBuilder.h"
#include "List.hpp"
#include "../tools/Class.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ListArray) {
		public:
			ListArray() : ListArray(128) {}
			
			explicit ListArray(size_t unitSize) : unitSize(unitSize), endSize(0), unitArrayList(new T[unitSize]),
			                                      usingState(0) {}
			
			~ListArray() {
				unitArrayList.forEach([&]() {
					delete[] unitArrayList.get();
				});
			}
			
			void append(const T &value) {
				if (endSize == unitSize) {
					unitArrayList.append(new T[unitSize]);
					endSize = 0;
				}
				unitArrayList.end()[endSize] = value;
				++endSize;
			}
			
			inline T &get() { return unitArrayList.get()[usingState]; }
			
			inline const T &get() const { return unitArrayList.get()[usingState]; }
			
			void next() {
				++usingState;
				if (usingState >= unitSize) {
					unitArrayList.next();
					usingState = 0;
				} else if (usingState == endSize && unitArrayList.isEnd()) {
					reset();
				}
			}
			
			void prev() {
				if (usingState == 0) {
					unitArrayList.prev();
					usingState = unitArrayList.isBegin() ? endSize : unitSize;
				}
				--usingState;
			}
			
			inline size_t size() { return unitSize * (unitArrayList.size() - 1) + endSize; }
			
			// used memory size
			inline size_t usedSize() {
				return sizeof(*this) + unitArrayList.usedSize() +
				       sizeof(T) * unitSize * unitArrayList.size();
			}
			
			inline void reset() {
				unitArrayList.reset();
				usingState = 0;
			}
			
			inline bool isBegin() { return usingState == 0 && unitArrayList.isBegin(); }
			
			inline bool isEnd() { return usingState == endSize && unitArrayList.isEnd(); }
			
			void forEach(const std::function<void(void)> &func) {
				saveState();
				reset();
				do {
					func();
					next();
				} while (!isBegin());
				loadState();
			}
			
			//主要是糊弄IDE（Clion）用
			inline void forEach(void(*func)()) { forEach([&]() { func(); }); }
			
			//加载上次保存时的状态
			inline void loadState() {
				unitArrayList.loadState();
				usingState = stateSave;
			}
			
			//保存状态
			void saveState() {
				stateSave = usingState;
			}
		
		private:
			const size_t unitSize;
			size_t endSize;
			size_t usingState;
			size_t stateSave; //用于储存上一次保存时的状态
			List<T *> unitArrayList;
		};
	}
}
#endif //CPLUS_UTILS_ListArray_HPP
