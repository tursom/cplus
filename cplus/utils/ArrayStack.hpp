//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_ARRAYSTACK_H
#define CPLUS_ARRAYSTACK_H

#include <functional>
#include "Stack.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"
#include "../thread/RunnableBase.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ArrayStack) {
		public:
			ArrayStack() : ArrayStack(128) {}
			
			explicit ArrayStack(cplus_stack_size_t blockSize) : ArrayStack(blockSize, 800) {}
			
			explicit ArrayStack(cplus_stack_size_t blockSize, cplus_stack_size_t maxBlock)
					: blockSize(blockSize), endPoint(0),
					  blockArrayStack(maxBlock) {
				last = new T[blockSize];
				blockArrayStack.push(last);
			}
			
			~ArrayStack() {
				blockArrayStack.forEach([&](T *block) { //遍历每一个数据块
					//释放每一个数据块的内存
					delete[] block;
				});
			}
			
			bool push(const T &value) {
				//检查是否已到数据块边界
				if (endPoint == blockSize) {
					//保存last状态
					auto lastSave = last;
					//释放内存
					if (lastState != nullptr) {
						delete lastState;
						lastState = nullptr;
					}
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
				if (endPoint == 0) return nullptr; //如果没有则返回最后的缓存
				
				T lastValue;
				//使用黑魔法获取数据
				::cplus::memory::copy(last[--endPoint], lastValue);
				
				//检查是否已到数据块边界
				if (endPoint == 0) {
					//释放内存
					if (lastState != nullptr) {
						delete lastState;
						lastState = nullptr;
					}
					
					//更新last状态
					lastState = blockArrayStack.pop();
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
				::cplus::memory::copy(last[--endPoint], buffer);
				
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
			
			inline T &get() { return last[endPoint]; }
			
			inline const T &get() const { return last[endPoint]; }
			
			inline cplus_stack_size_t size() { return blockSize * (blockArrayStack.size() - 1) + endPoint; }
			
			// used memory size
			inline cplus_stack_size_t usedSize() {
				return sizeof(*this) + blockArrayStack.usedSize() + sizeof(T) * blockSize * blockArrayStack.size();
			}
			
			cplus_stack_size_t getBlockSize() { return blockSize; }
			
			void forEach(const std::function<void(T &value)> &func) const {
				cplus_stack_size_t endPoint;
				bool isEndPoint = true;
				blockArrayStack.forEach([&](T *&block) {
					if (isEndPoint) {
						endPoint = this->endPoint;
						isEndPoint = false;
					} else endPoint = this->blockSize;
					while (endPoint > 0) {
						func(block[--endPoint]);
					}
				});
			}
			
			cplus_stack_size_t size() const { return blockSize * (blockArrayStack.size() - 1) + endPoint - 1; }
			
			inline ::cplus::lang::String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::ArrayStack(");
				stringBuilder.append("size:");
				stringBuilder.append((long) size());
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
		
		private:
			const cplus_stack_size_t blockSize;
			cplus_stack_size_t endPoint;
			T *last;
			T *lastState;
			Stack<T *> blockArrayStack;
		};
	}
}
#endif //CPLUS_ARRAYSTACK_H
