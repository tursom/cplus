#include <cmath>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <map>
#include <set>
#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
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
#include "cplus/thread/Runnable.h"
#include "cplus/socket/ServerSocket.h"
#include "cplus/utils/Set.hpp"
#include "cplus/system/io.h"

using namespace cplus::lang;
using namespace cplus::utils;
using namespace cplus::system;
using namespace cplus::thread;
using namespace cplus::socket;

/**
 *
 */
class ServerHandler : public Runnable {
public:
	void run() const override {
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
	bool isLeft{};
	bool red{};
	uint32_t size = 1;
	T1 *parent = nullptr;
	T1 *left = nullptr;
	T1 *right = nullptr;
};

class T2 {
	bool isLeft{};
	bool red{};
	uint32_t size = 1;
	T2 *parent = nullptr;
	T2 *left = nullptr;
	T2 *right = nullptr;
};

uint16_t port = 12345;

struct A {
public:
	A(int) {}

private:
	A(const A &) {
	
	}
};

int main() {
	cplus::utils::List<int> list{1, 2, 3};
	//启动服务器
	Thread([]() -> void {
		SocketServer server(port);
		server.listen();
		println({&String::getString("server started at port: "), &Short::get(port)});
		auto buffer = ByteBuffer(1024);
		while (true) {
			auto socket = server.accept();
			try {
				println({&String::getString("server got connection from:"), &socket.getAddress()});
				while (true) {
					socket.read(buffer);
					println({&String::getString("server recv from:"), &socket.getAddress()});
					println({String::getString(">>>"), buffer.getString()});
					socket.write(buffer);
				}
			} catch (const Exception &e) {
				std::cerr << e.getMessage().c_str() << std::endl
				          << e.getStackTrace().c_str() << std::endl;
				socket.close();
			} catch (const std::exception &e) {
				std::cerr << "server exception: " << e.what() << std::endl;
				socket.close();
			} catch (int e) {
				std::cerr << e << std::endl;
				socket.close();
			}
		}
	}).start();


//	Thread::msleep(100);
//	try {
//		auto message = ByteArray("hello?", sizeof("hello?"));
//		auto socket = Socket("127.0.0.1", port);
//
//		socket.connect();
//		println(2, &String::getString("connecting to server: localhost: )"),
//		        &String::getString(String(port)));
//
//		Thread::msleep(100);
//		ssize_t sendSize = socket.send(message);
//		if (sendSize == -1) {
//		throw Exception("send error: " + Long(errno).toString());
//		} else {
//			println(2, &String::getString("sending size: "),
//			        &String::getString(String(sendSize)));
//		}
//
//		auto recv = socket.recv(1024);
//		println(2, &String::getString("recving from server:\n>>>"),
//		        &String::getString(String(recv)));
	
	//} catch (Exception e) {
	//	std::cerr << e.getMessage().c_str() << std::endl
	//	          << e.getStackTrace().c_str() << std::endl;
	//} catch (std::exception e) {
	//	std::cerr << "client exception: " << e.what() << std::endl;
	//}

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