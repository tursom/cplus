//
// Created by Tursom Ulefits on 2018/5/18.
//

#ifndef CPLUS_UTILS_ListArray_HPP
#define CPLUS_UTILS_ListArray_HPP

#include <cmath>
#include <functional>
#include "StringBuilder.h"
#include "List.hpp"
#include "../tools/class.h"
#include "../thread/Runnable.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ArrayList) {
		public:
			ArrayList() : ArrayList(128) {}
			
			explicit ArrayList(size_t unitSize) : ArrayList(unitSize, 800) {}
			
			explicit ArrayList(size_t blockSize, size_t maxBlock)
					: blockSize(blockSize), endPoint(0), unitArrayList(new T[blockSize], maxBlock), usingState(0),
					  array(nullptr) {}
			
			~ArrayList() {
				unitArrayList.forEach([&]() {
					delete[] unitArrayList.get();
				});
				if (array != nullptr) delete[] array;
			}
			
			bool append(const T &value) {
				if (endPoint == blockSize) {
					if (!unitArrayList.append(new T[blockSize])) return false;
					endPoint = 0;
				}
				::cplus::memory::copy(value, unitArrayList.end()[endPoint]);
				++endPoint;
				return true;
			}
			
			inline T &get() { return unitArrayList.get()[usingState]; }
			
			inline const T &get() const { return unitArrayList.get()[usingState]; }
			
			void next() {
				++usingState;
				if (usingState >= blockSize) {
					unitArrayList.next();
					usingState = 0;
				} else if (usingState == endPoint && unitArrayList.isEnd()) {
					reset();
				}
			}
			
			void prev() {
				if (usingState == 0) {
					unitArrayList.prev();
					usingState = unitArrayList.isBegin() ? endPoint : blockSize;
				}
				--usingState;
			}
			
			inline size_t size() { return blockSize * (unitArrayList.size() - 1) + endPoint; }
			
			// used memory size
			inline size_t usedSize() {
				return sizeof(*this) + unitArrayList.usedSize() + sizeof(T) * blockSize * unitArrayList.size() +
				       stateSave.usedSize();
			}
			
			inline void reset() {
				unitArrayList.reset();
				usingState = 0;
			}
			
			inline bool isBegin() { return usingState == 0 && unitArrayList.isBegin(); }
			
			inline bool isEnd() { return usingState == endPoint && unitArrayList.isEnd(); }
			
			void forEach(const std::function<void(void)> &func) {
				saveState();
				reset();
				do {
					func();
					next();
				} while (!isBegin());
				loadState();
			}
			
			
			void forEach(cplus::thread::Runnable runnable) {
				saveState();
				reset();
				do {
					runnable.run();
					next();
				} while (!isBegin());
				loadState();
			}
			
			T *toArray() {
				if (array != nullptr) delete array;
				array = new T[size()];
				size_t p = 0;
				forEach([&]() {
					::cplus::memory::copy(get(), array[p++]);
				});
				return array;
			};
			
			std::unique_ptr<T[]> toSmartArray() {
				std::unique_ptr<T[]> array(new T[size()]);
				size_t p = 0;
				forEach([&]() {
					::cplus::memory::copy(get(), array[p++]);
				});
				return array;
			};
			
			T &operator[](size_t location) {
				saveState();
				reset();
				for (size_t n = static_cast<size_t>(floor((double) ((float) location) / blockSize)); n > 0; --n) {
					next();
				}
				size_t locate = location % blockSize;
				loadState();
				return unitArrayList.end()[locate];
			}
			
			size_t getBlockSize() { return blockSize; }
			
			//加载上次保存时的状态
			inline void loadState() {
				if (stateSave.size() == 0) return;
				unitArrayList.loadState();
				usingState = stateSave.pop();
			}
			
			//保存状态
			void saveState() {
				stateSave.push(usingState);
			}
		
		private:
			T *array;
			const size_t blockSize;
			size_t endPoint;
			size_t usingState;
			Stack <size_t> stateSave; //用于储存上一次保存时的状态
			List<T *> unitArrayList;
		};
	}
}
#endif //CPLUS_UTILS_ListArray_HPP
