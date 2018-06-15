//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_SOCKET_H
#define CPLUS_SOCKET_H

#include <cygwin/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../tools/class.h"
#include "../lang/ByteArray.h"

namespace cplus {
	namespace socket {
		CPlusClass(Socket) {
		public:
			Socket() = default;
			
			Socket(int socket, sockaddr_in addr) : socket(socket), addr(addr), address(""), buffer(0) {}
			
			~Socket() {
				close();
			}
			
			lang::ByteArray &recv(size_t bufferSize) {
				buffer.setSize(bufferSize);
				buffer.fillWithZero();
				auto readSize = ::recv(socket, buffer.getBuffer(), bufferSize, 0);
				buffer.setSize(static_cast<size_t>(readSize));
				return buffer;
			}
			
			ssize_t recv(char buffer[], size_t bufferSize) const {
				return ::recv(socket, buffer, bufferSize, 0);
			}
			
			ssize_t send(char buffer[], size_t bufferSize) const {
				return ::send(socket, buffer, bufferSize, 0);
			}
			
			ssize_t send(const lang::ByteArray &buffer) const {
				return ::send(socket, buffer.getBuffer(), buffer.getSize(), 0);
			}
			
			int getSocket() const {
				return socket;
			}
			
			const sockaddr_in &getAddr() const {
				return addr;
			}
			
			void close() {
				::close(socket);
			}
		
		private:
			int socket{};
			sockaddr_in addr{};
			lang::String address;
			lang::ByteArray buffer;
		};
	}
}


#endif //CPLUS_SOCKET_H
