//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_SOCKET_H
#define CPLUS_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include "../tools/class.h"
#include "../lang/ByteArray.h"
#include "../system/Exception.h"
#include "../lang/String.h"
#include "../utils/ByteBuffer.h"

namespace cplus {
	namespace socket {
		CPlusClass(Socket) {
		public:
			Socket() = default;
			
			Socket(int socket, sockaddr_in addr, sockaddr_in local_addr);
			
			Socket(const lang::String &host, uint16_t port);
			
			Socket(const char *host, uint16_t port);
			
			~Socket();
			
			void connect();
			
			const lang::String &getAddress() const;
			
			lang::ByteArray &recv(size_t bufferSize, int flags = 0);
			
			ssize_t recv(lang::ByteArray &buffer, int flags = 0) const;
			
			ssize_t recv(char buffer[], size_t bufferSize, int flags = 0) const;
			
			ssize_t send(char buffer[], size_t bufferSize, int flags = 0) const;
			
			ssize_t send(const lang::ByteArray &buffer, int flags = 0) const;
			
			lang::ByteArray &read(size_t bufferSize);
			
			ssize_t read(lang::ByteArray &buffer) const;
			
			ssize_t read(char buffer[], size_t bufferSize) const;
			
			ssize_t write(const lang::ByteArray &buffer) const;
			
			ssize_t write(char buffer[], size_t bufferSize) const;
			
			ssize_t read(utils::ByteBuffer &buffer) const;
			
			ssize_t write(const utils::ByteBuffer &buffer) const;
			
			uint16_t getPort() const;
			
			int getSocket() const;
			
			const sockaddr_in &getAddr() const;
			
			void close() const;
			
			static lang::String getIp(sockaddr_in addr);
			
			class SocketException : public system::Exception {
			public:
				SocketException() = default;
				
				explicit SocketException(const char *message) : Exception(lang::String(message)) {}
				
				explicit SocketException(const lang::String &message) : Exception(message) {}
			};
		
		private:
			int socket{};
			sockaddr_in addr{};
			sockaddr_in local_addr{};
			lang::String address;
			lang::ByteArray buffer;
		};
	}
}


#endif //CPLUS_SOCKET_H
