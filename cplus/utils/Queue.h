//
// Created by Tursom Ulefits on 2018/6/16.
//

#ifndef CPLUS_QUEUE_H
#define CPLUS_QUEUE_H

#include "../tools/class.h"
#include "../memory/dark_magic.h"

typedef unsigned int cplus_queue_size_t;

namespace cplus {
	namespace utils {
		template<typename T>
		CPlusClass(Queue) {
		public:
			Queue() = default;
			
			explicit Queue(cplus_queue_size_t maxSize) : maxSize(maxSize) {}
			
			bool offer(const T &value) {
				if (queueSize >= maxSize) {
					return false;
				}
				end = new QueuePoint(end, value);
				if (begin == nullptr)begin = end;
				queueSize++;
				return true;
			}
			
			T &pool() {
				if (begin == nullptr) return last;
				memory::swap(last, begin->get());
				begin->setToNull();
				auto next = begin->getNext();
				free(begin);
				begin = next;
				queueSize--;
				return last;
			}
		
		private:
			/**
			 *单向链表节点
			 */
			CPlusClass(QueuePoint) {
			public:
				QueuePoint() : next(nullptr), value(nullptr) {}
				
				QueuePoint(QueuePoint *prev, const T &value)
						: next(nullptr), value(value) {
					if (prev != nullptr)prev->next = this;
				}
				
				inline void del(QueuePoint *next) { next->next = next; }
				
				inline T get() { return value; }
				
				inline const T get() const { return value; }
				
				void set(const T &value) {
					this->value = value;
				}
				
				void setToNull() { this->value = nullptr; }
				
				inline QueuePoint *getNext() { return next; }
				
				inline void setNext(QueuePoint *prev) { this->next = prev; }
			
			private:
				T value;
				QueuePoint *next;
			};
			
			cplus_queue_size_t maxSize{};
			cplus_queue_size_t queueSize = 0;
			QueuePoint *end = nullptr;
			QueuePoint *begin = nullptr;
			T last;
		};
	}
}


#endif //CPLUS_QUEUE_H
