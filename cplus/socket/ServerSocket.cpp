//
// Created by Tursom Ulefits on 2018/6/14.
//

#include "ServerSocket.h"

namespace cplus {
	namespace socket {
		SocketServer::ServerException::ServerException(const char *message) : Exception(message) {
		
		}
		
		SocketServer::ServerException::ServerException(const lang::String &message) : Exception(message) {
		
		}
		
		int SocketServer::listen() const {
			//server_socket用于监听
			return ::listen(server_socket, lengthOfListenQueue);
		}
		
		int SocketServer::close() const {
			return ::close(server_socket);
		}
		
		int SocketServer::bind() {
			//把socket和socket地址结构联系起来
			return ::bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
		}
		
		int SocketServer::bind(uint16_t port) {
			bzero(&server_addr, sizeof(server_addr)); //把一段内存区的内容全部设置为0
			server_addr.sin_family = AF_INET;
			server_addr.sin_addr.s_addr = htons(INADDR_ANY);
			server_addr.sin_port = htons(port);
			//创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
			server_socket = ::socket(PF_INET, SOCK_STREAM, 0);
			if (server_socket < 0) {
				throw ServerException("Create Socket Failed!");
			}
			int opt = 1;
			setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
			//把socket和socket地址结构联系起来
			return bind();
		}
		
		Socket SocketServer::accept() {
			//定义客户端的socket地址结构client_addr
			sockaddr_in client_addr{};
			socklen_t length = sizeof(client_addr);
			
			//接受一个到server_socket代表的socket的一个连接
			//如果没有连接请求,就等待到有连接请求--这是accept函数的特性
			//accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
			//new_server_socket代表了服务器和客户端之间的一个通信通道
			//accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
			int new_server_socket = ::accept(server_socket, (struct sockaddr *) &client_addr, &length);
			if (new_server_socket < 0) {
				throw AcceptFailedException();
			}
			
			return {new_server_socket, client_addr, server_addr};
		}
		
		SocketServer::SocketServer(uint16_t port) {
			//把socket和socket地址结构联系起来
			if (bind(port)) {
				throw ServerException("Server Bind Port : " + lang::Long(port).toString() + " Failed!");
			}
			//server_socket用于监听
			if (listen()) {
				throw ServerException("Server Listen Failed!");
			}
		}
	}
}