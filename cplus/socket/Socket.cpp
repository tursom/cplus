//
// Created by Tursom Ulefits on 2018/6/14.
//

#include "Socket.h"
#include "../lang/Long.h"
#include "../lang/Int.h"

namespace cplus {
	namespace socket {
		void Socket::connect() {
			//创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
			socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (socket < 0) {
				throw SocketException("Create Socket Failed!: " + lang::Int(errno).toString());
			}
			//把客户机的socket和客户机的socket地址结构联系起来
			if (::bind(socket, (struct sockaddr *) &local_addr, sizeof(local_addr))) {
				throw SocketException(
						"Client Bind Port Failed!: " + lang::Long(errno).toString());
			}
			
			if (inet_aton(address.c_str(), &addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
			{
				throw SocketException(
						"Server IP Address Error!: " + lang::Long(errno).toString());
			}
			//向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
			if (::connect(socket, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
				throw SocketException("Can Not Connect To " + address + ", error code: " +
				                      lang::Int(errno));
			}
		}
		
		Socket::Socket(const lang::String &host, uint16_t port) : address(host), buffer(0) {
			bzero(&local_addr, sizeof(local_addr)); //把一段内存区的内容全部设置为0
			local_addr.sin_family = AF_INET;    //internet协议族
			local_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
			local_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
			
			// 设置一个socket地址结构addr,代表服务器的internet地址, 端口
			bzero(&addr, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
		}
		
		Socket::Socket(int socket, sockaddr_in addr, sockaddr_in local_addr)
				: socket(socket), addr(addr), local_addr(local_addr), address(getIp(addr)),
				  buffer(0) {
		}
		
		Socket::Socket(const char *host, uint16_t port) : Socket(lang::String(host), port) {}
		
		Socket::~Socket() {
			close();
		}
		
		lang::ByteArray &Socket::recv(size_t bufferSize, int flags) {
			buffer.setSize(bufferSize);
			buffer.fillWithZero();
			auto readSize = ::recv(socket, buffer.getBuffer(), bufferSize, flags);
			if (readSize == -1)
				return buffer;
			buffer.setSize(static_cast<size_t>(readSize));
			return buffer;
		}
		
		const lang::String &Socket::getAddress() const {
			return address;
		}
		
		ssize_t Socket::recv(lang::ByteArray &buffer, int flags) const {
			ssize_t readSize = ::recv(socket, buffer.getBuffer(), buffer.getSize(), flags);
			buffer.setSize(static_cast<size_t>(readSize));
			return readSize;
		}
		
		ssize_t Socket::recv(char *buffer, size_t bufferSize, int flags) const {
			return ::recv(socket, buffer, bufferSize, flags);
		}
		
		ssize_t Socket::send(char *buffer, size_t bufferSize, int flags) const {
			return ::send(socket, buffer, bufferSize, flags);
		}
		
		ssize_t Socket::send(const lang::ByteArray &buffer, int flags) const {
			return ::send(socket, buffer.getBuffer(), buffer.getSize(), flags);
		}
		
		ssize_t Socket::write(const lang::ByteArray &buffer) const {
			return ::write(socket, buffer.getBuffer(), buffer.getSize());
		}
		
		ssize_t Socket::write(char *buffer, size_t bufferSize) const {
			return ::write(socket, buffer, bufferSize);
		}
		
		int Socket::getSocket() const {
			return socket;
		}
		
		const sockaddr_in &Socket::getAddr() const {
			return addr;
		}
		
		void Socket::close() const {
			::close(socket);
		}
		
		lang::String Socket::getIp(sockaddr_in addr) {
			return lang::String(inet_ntoa(addr.sin_addr));
		}
		
		uint16_t Socket::getPort() const {
			return htons(addr.sin_port);
		}
		
		lang::ByteArray &Socket::read(size_t bufferSize) {
			buffer.setSize(bufferSize);
			buffer.fillWithZero();
			auto readSize = ::read(socket, buffer.getBuffer(), bufferSize);
			if (readSize == -1)
				return buffer;
			buffer.setSize(static_cast<size_t>(readSize));
			return buffer;
		}
		
		ssize_t Socket::read(lang::ByteArray &buffer) const {
			ssize_t readSize = ::read(socket, buffer.getBuffer(), buffer.getSize());
			buffer.setSize(static_cast<size_t>(readSize));
			return readSize;
		}
		
		ssize_t Socket::read(char *buffer, size_t bufferSize) const {
			return ::read(socket, buffer, bufferSize);
		}
		
		ssize_t Socket::read(utils::ByteBuffer &buffer) const {
			ssize_t readSize = ::read(socket, buffer.getWriteBuffer(), buffer.getWriteableSize());
			buffer.readSize(readSize);
			return readSize;
		}
		
		ssize_t Socket::write(const utils::ByteBuffer &buffer) const {
			ssize_t writeSize = ::write(socket, buffer.getReadBuffer(), buffer.getReadableSize());
			buffer.writeSize(writeSize);
			return writeSize;
		}
	}
}