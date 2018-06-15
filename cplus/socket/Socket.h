//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_SOCKET_H
#define CPLUS_SOCKET_H

#include <cygwin/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include "../tools/class.h"
#include "../lang/ByteArray.h"
#include "../system/Exception.h"

namespace cplus {
	namespace socket {
		CPlusClass(Socket) {
		public:
			Socket() = default;
			
			Socket(int socket, sockaddr_in addr, sockaddr_in local_addr)
					: socket(socket), addr(addr), local_addr(local_addr), address(getIp(addr)), buffer(0) {
			}
			
			Socket(const lang::String &host, u_int16_t port) : address(host), buffer(0) {
				bzero(&local_addr, sizeof(local_addr)); //把一段内存区的内容全部设置为0
				local_addr.sin_family = AF_INET;    //internet协议族
				local_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
				local_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
				
				// 设置一个socket地址结构addr,代表服务器的internet地址, 端口
				bzero(&addr, sizeof(addr));
				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);
			}
			
			~Socket() {
				close();
			}
			
			void connect() {
				//创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
				int socket = ::socket(AF_INET, SOCK_STREAM, 0);
				if (socket < 0) {
					throw SocketException("Create Socket Failed!\n");
				}
				//把客户机的socket和客户机的socket地址结构联系起来
				if (bind(socket, (struct sockaddr *) &socket, sizeof(socket))) {
					throw SocketException("Client Bind Port Failed!");
				}
				
				if (inet_aton(address.c_str(), &addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
				{
					throw SocketException("Server IP Address Error!");
				}
				socklen_t server_addr_length = sizeof(addr);
				//向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
				if (::connect(socket, (struct sockaddr *) &addr, server_addr_length) < 0) {
					throw SocketException("Can Not Connect To " + address);
				}
			}
			
			const lang::String &getAddress() const {
				return address;
			}
			
			lang::ByteArray &recv(size_t bufferSize) {
				buffer.setSize(bufferSize);
				buffer.fillWithZero();
				auto readSize = ::recv(socket, buffer.getBuffer(), bufferSize, 0);
				buffer.setSize(static_cast<size_t>(readSize));
				return buffer;
			}
			
			ssize_t recv(lang::ByteArray &buffer) {
				auto readSize = ::recv(socket, buffer.getBuffer(), buffer.getSize(), 0);
				buffer.setSize(readSize);
				return readSize;
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
			
			u_int16_t getPort() { return htons(addr.sin_port); }
			
			int getSocket() const {
				return socket;
			}
			
			const sockaddr_in &getAddr() const {
				return addr;
			}
			
			void close() {
				::close(socket);
			}
			
			static lang::String getIp(sockaddr_in addr) {
				lang::String(inet_ntoa(addr.sin_addr));
			}
			
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
