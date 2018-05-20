//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_ARRAYSTACK_H
#define CPLUS_ARRAYSTACK_H

#include <functional>
#include "Stack.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"
#include "../thread/Runnable.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ArrayStack) {
		public:
			ArrayStack() : ArrayStack(128) {}
			
			explicit ArrayStack(size_t blockSize) : ArrayStack(blockSize, 800) {}
			
			explicit ArrayStack(size_t blockSize, size_t maxBlock)
					: blockSize(blockSize), endPoint(0),
					  blockArrayStack(maxBlock) {
				last = new T[blockSize];
				blockArrayStack.push(last);
			}
			
			~ArrayStack() {
				blockArrayStack.forEach([&]() { //遍历每一个数据块
					//释放每一个数据块的内存
					delete[] blockArrayStack.pop();
				});
			}
			
			bool push(const T &value) {
				//检查是否已到数据块边界
				if (endPoint == blockSize) {
					//保存last状态
					auto lastSave = last;
					//分配内存
					last = new T[blockSize];
					//压入数据块栈
					if (!blockArrayStack.push(last)) {
						//如果失败
						//释放内存
						delete last;
						//还原last状态
						last = lastSave;
						//返回false表示失败
						return false;
					} else {
						//如果成功
						//更新endPoint指针状态
						endPoint = 0;
					}
				}
				//压数据入栈
				::cplus::memory::copy(value, last[endPoint++]);
				//返回true表示成功
				return true;
			}
			
			const T &pop() {
				//检查是否还有剩余元素
				if (endPoint == 0) return lastValue; //如果没有则返回最后的缓存
				
				//使用黑魔法获取数据
				::cplus::memory::copy(last[--endPoint], lastValue);
				
				//检查是否已到数据块边界
				if (endPoint == 0) {
					//释放内存
					auto t = blockArrayStack.pop();
					delete t;
					
					//更新last状态
					if (blockArrayStack.pop(last)) {
						//成功
						blockArrayStack.push(last);
						//更新endPoint指针状态
						endPoint = blockSize;
					}
				}
				//返回数据
				return lastValue;
			}
			
			bool pop(const T &buffer) {
				//检查是否还有剩余元素
				if (endPoint == 0) return false; //如果没有则返回最后的缓存
				
				//使用黑魔法获取和更新数据
				::cplus::memory::copy(last[--endPoint], lastValue);
				::cplus::memory::copy(lastValue, buffer);
				
				//检查是否已到数据块边界
				if (endPoint == 0) {
					//释放内存
					auto t = blockArrayStack.pop();
					delete t;
					
					//更新last状态
					if (blockArrayStack.pop(last)) {
						//成功
						blockArrayStack.push(last);
						//更新endPoint指针状态
						endPoint = blockSize;
						//返回数据
						return true;
					} else {
						//更新last状态失败
						return true; //至少pop是成功的
					}
				}
			}
			
			bool isFull() { return endPoint == blockSize && blockArrayStack.isFull(); }
			
			inline T &get() { return lastValue; }
			
			inline const T &get() const { return lastValue; }
			
			inline size_t size() { return blockSize * (blockArrayStack.size() - 1) + endPoint; }
			
			// used memory size
			inline size_t usedSize() {
				return sizeof(*this) + blockArrayStack.usedSize() + sizeof(T) * blockSize * blockArrayStack.size();
			}
			
			size_t getBlockSize() { return blockSize; }
			
			void forEach(const std::function<void(void)> &func) {
				blockArrayStack.forEach([&]() {
					size_t state = blockSize;
					if (blockArrayStack.get() == last) {
						state = endPoint;
					}
					while (state > 0) {
						::cplus::memory::copy(blockArrayStack.get()[state - 1], lastValue);
						func();
						state--;
					}
				});
			}
			
			void forEach(cplus::thread::Runnable runnable) {
				blockArrayStack.forEach([&]() {
					size_t state = blockSize;
					if (blockArrayStack.get() == last) {
						state = endPoint;
					}
					while (state > 0) {
						::cplus::memory::copy(blockArrayStack.get()[state - 1], lastValue);
						runnable.run();
						state--;
					}
				});
			}
			
			size_t size() const { return blockSize * (blockArrayStack.size() - 1) + endPoint - 1; }
			
			inline String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::ArrayStack(");
				stringBuilder.append("size:");
				stringBuilder.append(size());
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
		
		private:
			const size_t blockSize;
			size_t endPoint;
			T *last;
			T lastValue;
			Stack<T *> blockArrayStack;
		};
	}
}
#endif //CPLUS_ARRAYSTACK_H
