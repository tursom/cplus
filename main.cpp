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
#include "cplus/utils/Set.h"

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

int main() {
	ServerHandler serverHandler;
	Thread([]() {
		try {
			u_int16_t port = 12346;
			SocketServer server(port);
			ByteArray recv(1024);
			std::cout << "server started at port " << port << std::endl;
			while (true) {
				auto socket = server.accept();
				std::cout << "get connection on: " << socket.getAddress().stdString()
				          << ":" << socket.getPort() << std::endl;
				socket.recv(recv);
				socket.send(recv);
				std::cout << String(recv).stdString() << std::endl;
				std::cout << recv.toHexString().stdString() << std::endl;
				if (String(recv.getBuffer()) == String("exit"))
					break;
			}
		} catch (SocketServer::ServerException e) {
			std::cerr << e.getMessage().stdString() << std::endl;
		}
	}).start();
	Thread::detachAll();
	Thread::exitThread();
}