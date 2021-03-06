//
// Created by Tursom Ulefits on 2018/5/19.
//

#ifndef CPLUS_ARRAYSTACK_H
#define CPLUS_ARRAYSTACK_H

#include <functional>
#include "Stack.h"
#include "../tools/class.h"
#include "../memory/dark_magic.h"

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(ArrayStack) {
		public:
			ArrayStack() : ArrayStack(128) {}
			
			explicit ArrayStack(cplus_queue_size_t blockSize) : ArrayStack(blockSize, 800) {}
			
			explicit ArrayStack(cplus_queue_size_t blockSize, cplus_queue_size_t maxBlock)
					: blockSize(blockSize), endPoint(0),
					  blockArrayStack(maxBlock) {
//				std::cout << "ArrayStack: ArrayStack(): blockSize:" << blockSize << std::endl;
				last = new T[blockSize];
				blockArrayStack.push(last);
			}
			
			~ArrayStack() {
//				std::cout << "ArrayStack: ~ArrayStack(): endpoint:" << endPoint << std::endl;
				blockArrayStack.forEach([&](T *block) { //遍历每一个数据块
					//释放每一个数据块的内存
					delete[] block;
				});
			}
			
			bool push(const T &value) {
//				std::cout << "ArrayStack: bool push(const K &key): endpoint:" << endPoint << std::endl;
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
			
			T *pop() {
//				std::cout << "ArrayStack: K *pop(): endpoint:" << endPoint << std::endl;
				static T *lastValue = (T *) malloc(sizeof(T));
				//检查是否还有剩余元素
				if (endPoint == 0) return nullptr; //如果没有则返回 nullptr
				pop(*lastValue);
				return lastValue;
			}
			
			bool pop(const T &buffer) {
//				std::cout << "ArrayStack: bool pop(const K &buffer): endpoint:" << endPoint << std::endl;
				//检查是否还有剩余元素
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
					} else {
						return false;
					}
				}
				
				//使用黑魔法获取和更新数据
				::cplus::memory::copy(last[--endPoint], buffer);
				return true; //至少pop是成功的
			}
			
			void pop(T *&buffer) {
//				std::cout << "ArrayStack: void pop(K *&buffer): endpoint:" << endPoint << std::endl;
				//检查是否还有剩余元素
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
					} else {
						buffer = nullptr;
						return;
					}
				}
				
				//获取和更新数据
				buffer = last[--endPoint];
			}
			
			bool isFull() { return endPoint == blockSize && blockArrayStack.isFull(); }
			
			inline T &get() { return last[endPoint]; }
			
			inline const T &get() const { return last[endPoint]; }
			
			inline cplus_queue_size_t size() { return blockSize * (blockArrayStack.size() - 1) + endPoint; }
			
			// used memory size
			inline cplus_queue_size_t usedSize() {
				return sizeof(*this) + blockArrayStack.usedSize() + sizeof(T) * blockSize * blockArrayStack.size();
			}
			
			cplus_queue_size_t getBlockSize() { return blockSize; }
			
			void forEach(const std::function<void(T &value)> &func) const {
				cplus_queue_size_t endPoint;
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
			
			cplus_queue_size_t size() const { return blockSize * (blockArrayStack.size() - 1) + endPoint - 1; }
			
			inline ::cplus::lang::String toString() const override {
				StringBuilder stringBuilder;
				stringBuilder.append("cplus::utils::ArrayStack(");
				stringBuilder.append("size:");
				stringBuilder.append((long) size());
				stringBuilder.append(")");
				return stringBuilder.toString();
			}
		
		private:
			const cplus_queue_size_t blockSize;
			cplus_queue_size_t endPoint;
			T *last;
			T *lastState;
			Stack<T *> blockArrayStack;
		};
	}
}
#endif //CPLUS_ARRAYSTACK_H
