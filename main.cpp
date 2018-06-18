#include <cmath>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <map>
#include <set>
#include <algorithm>
#include <w32api/profileapi.h>
#include <arpa/inet.h>
#include "cplus/lang/String.h"
#include "cplus/lang/Int.h"
#include "cplus/system/time.h"
#include "cplus/system/OutputStream.h"
#include "cplus/lang/Float.h"
#include "cplus/lang/Short.h"
#include "cplus/utils/List.hpp"
#include "cplus/utils/ArrayList.hpp"
#include "cplus/utils/ArrayStack.hpp"
#include "cplus/lang/ByteArray.h"
#include "cplus/test/utils.h"
#include "cplus/thread/Thread.h"
#include "cplus/socket/ServerSocket.h"
#include "cplus/utils/Set.hpp"

using namespace cplus::lang;
using namespace cplus::utils;
using namespace cplus::system;
using namespace cplus::thread;
using namespace cplus::socket;

class ServerHandler : public Runnable {
public:
	void run(void *value) const override {
		SocketServer server(12345);
		ByteArray recv(1024);
		std::cout << "server started at port " << 12345 << std::endl;
		while (true) {
			auto socket = server.accept();
			socket.recv(recv);
			socket.send(recv);
			if (String(recv.getBuffer()) == String("exit"))
				break;
		}
		std::cout << "server closed at port " << 12345 << std::endl;
	}
};

void throwAnException() {
	throw Exception("test hello");
}

class T1 {
	bool isLeft;
	bool red;
	u_int32_t size = 1;
	T1 *parent = nullptr;
	T1 *left = nullptr;
	T1 *right = nullptr;
};

class T2 {
	bool isLeft;
	bool red;
	u_int32_t size = 1;
	T2 *parent = nullptr;
	T2 *left = nullptr;
	T2 *right = nullptr;
};

int main() {
	std::cout << sizeof(T1) << std::endl
	          << sizeof(T2) << std::endl;
	Set<int> s;
	for (int i = 0; i < 100; ++i) {
		s.insert(i);
	}
	std::cout << s.toString().c_str() << std::endl;
	for (int i = 0; i < 100; ++i) {
		auto find = s.find(i);
		std::cout << ((find == nullptr) ? 0 : *find) << std::endl;
	}
	
	try {
		std::cout << std::string("12345").size() << std::endl;
		String s1("123"), s2("123");
		std::cout << (s1.c_str() == s2.c_str() ? "true" : "false") << std::endl;
		String s3("1234"), s4("1234");
		std::cout << (s3.c_str() == s4.c_str() ? "true" : "false") << std::endl;
		String s5("12345"), s6("12345");
		std::cout << (s5.c_str() == s6.c_str() ? "true" : "false") << std::endl;
		throw Exception("hello");
	} catch (Exception e) {
		std::cout << e.getMessage().c_str() << std::endl;
	}
	
	try {
		throwAnException();
	} catch (Exception e) {
		std::cout << e.getMessage().c_str() << std::endl;
	}
	
	
	std::cout << String::allString().c_str() << std::endl;

//	ServerHandler serverHandler;
//	Thread([]() {
//		try {
//			u_int16_t port = 12346;
//			SocketServer server(port);
//			ByteArray recv(1024);
//			std::cout << "server started at port " << port << std::endl;
//			while (true) {
//				auto socket = server.accept();
//				std::cout << "get connection on: " << socket.getAddress().stdString()
//				          << ":" << socket.getPort() << std::endl;
//				socket.recv(recv);
//				socket.send(recv);
//				std::cout << String(recv).stdString() << std::endl;
//				std::cout << recv.toHexString().stdString() << std::endl;
//				if (String(recv.getBuffer()) == String("exit"))
//					break;
//			}
//		} catch (SocketServer::ServerException e) {
//			std::cerr << e.getMessage().stdString() << std::endl;
//		}
//	}).start();
//	Thread::detachAll();
	Thread::exitThread();
}