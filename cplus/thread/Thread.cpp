//
// Created by Tursom Ulefits on 2018/5/16.
//

#include "Thread.h"

namespace cplus {
	namespace thread {
		pid_t Thread::pidCount = 0;
		ThreadMutex Thread::pidCountMutex = ThreadMutex();
		ThreadMutex Thread::outputMutex = ThreadMutex();
		
		void *threadStart(void *t) {
			auto thread = (Thread *) t;
			thread
			->func
			->run();
			return nullptr;
		}
		
		void *staticThreadStart(void *thread) {
			((std::function<void()> *) thread)->operator()();
			return nullptr;
		}
		
		pthread_t Thread::run(std::function<void()> func) {
			pthread_t pthread1;
			pthread_create(&pthread1, nullptr, staticThreadStart, (void *) &func);
			return pthread1;
		}
		
		bool Thread::start() {
			pthread_create(&pthread, nullptr, threadStart, this);
			return true;
		}
		
		Thread::~Thread() {
		
		}
		
		const pthread_t &Thread::getPthread() const {
			return pthread;
		}
		
		const pid_t &Thread::getPID() const {
			return pid;
		}
		
		void Thread::lockOutput() {
			outputMutex.lock();
		}
		
		void Thread::unlockOutput() {
			outputMutex.unlock();
		}
		
		void Thread::msleep(unsigned int secs) {
			timeval tval{};
			tval.tv_sec = secs / 1000;
			tval.tv_usec = (secs * 1000) % 1000000;
			select(0, nullptr, nullptr, nullptr, &tval);
		}
		
		void Thread::usleep(unsigned int secs) {
			::usleep(secs);
		}
		
		void Thread::sleep(unsigned int secs) {
			::sleep(secs);
		}
		
		void Thread::exitThread() {
			pthread_exit(nullptr);
		}
		
		void Thread::detach(const Thread &thread1) {
			pthread_join(thread1.getPthread(), nullptr);
		}
		
		Thread::ThreadException::ThreadException(const char *message) : Exception(message) {}
		
		Thread::ThreadException::ThreadException(const lang::String &message) : Exception(message) {}
	}
}
