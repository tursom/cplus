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

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ArrayList) {
		public:
			ArrayList() : ArrayList(128) {}
			
			explicit ArrayList(cplus_list_size_t unitSize) : ArrayList(unitSize, 800) {}
			
			explicit ArrayList(cplus_list_size_t blockSize, cplus_list_size_t maxBlock)
					: blockSize(blockSize), endPoint(blockSize), unitArrayList(maxBlock), usingState(0),
					  array(nullptr) {}
			
			~ArrayList() {
				unitArrayList.forEach([&](T *block) {
					delete[] block;
				});
				if (array != nullptr) delete[] array;
			}
			
			bool append(const T &value) {
				if (endPoint == blockSize) {
					if (!unitArrayList.append(new T[blockSize]))
						return false;
					endPoint = 0;
				}
				::cplus::memory::copy(value, unitArrayList.end()[endPoint]);
				++endPoint;
				return true;
			}
			
			T &get() { return unitArrayList.get()[usingState]; }
			
			const T &get() const { return unitArrayList.get()[usingState]; }
			
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
			
			cplus_list_size_t size() { return blockSize * (unitArrayList.size() - 1) + endPoint; }
			
			// used memory size
			cplus_list_size_t usedSize() const {
				return sizeof(*this) + unitArrayList.usedSize() + sizeof(T) * blockSize * unitArrayList.size();
			}
			
			inline void reset() {
				unitArrayList.reset();
				usingState = 0;
			}
			
			inline bool isBegin() const { return usingState == 0 && unitArrayList.isBegin(); }
			
			inline bool isEnd() const { return usingState == endPoint && unitArrayList.isEnd(); }
			
			void forEach(const std::function<void(T &)> &func) const {
				List<T *> unitArrayList = this->unitArrayList;
				int loopTime = 0;
				unitArrayList.forEach([&](T *block) {
					cplus_list_size_t usingState = 0;
					cplus_list_size_t blockSize = loopTime == unitArrayList.size() ? this->endPoint : this->blockSize;
					while (usingState != blockSize) {
						func(block[usingState]);
						++usingState;
					}
					++loopTime;
				});
				::cplus::memory::copy(List<T *>(), unitArrayList);
			}
			
			
			void forEach(cplus::thread::Runnable runnable) {
				List<T *> unitArrayList = this->unitArrayList;
				int loopTime = 0;
				unitArrayList.forEach([&](T *block) {
					cplus_list_size_t usingState = 0;
					cplus_list_size_t blockSize = loopTime == unitArrayList.size() ? this->endPoint : this->blockSize;
					while (usingState != blockSize) {
						runnable(block[usingState]);
						++usingState;
					}
					++loopTime;
				});
				::cplus::memory::copy(List<T *>(), unitArrayList);
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
				::cplus::memory::copy(List<T *>(), unitArrayList);
				return array;
			};
			
			T &operator[](cplus_list_size_t location) const {
				auto usingState = 0;
				auto unitArrayList = this->unitArrayList;
				unitArrayList.reset();
				for (cplus_list_size_t n = static_cast<cplus_list_size_t>(floor((double) location / blockSize)); n > 0; --n) {
					//to next
					++usingState;
					if (usingState >= blockSize) {
						unitArrayList.next();
						usingState = 0;
					} else if (usingState == endPoint && unitArrayList.isEnd()) {
						break;
					}
				}
				cplus_list_size_t locate = location % blockSize;
				auto block = unitArrayList.get();
				::cplus::memory::copy(List<T *>(), unitArrayList);
				return block[locate];
			}
			
			cplus_list_size_t getBlockSize() { return blockSize; }
		
		private:
			T *array;
			const cplus_list_size_t blockSize;
			unsigned int endPoint;
			cplus_list_size_t usingState;
			List<T *> unitArrayList;
		};
	}
}
#endif //CPLUS_UTILS_ListArray_HPP
