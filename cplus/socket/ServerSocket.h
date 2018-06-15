//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_SOCKETSERVER_H
#define CPLUS_SOCKETSERVER_H

#include <strings.h>
#include "../tools/class.h"
#include "Socket.h"

namespace cplus {
	namespace socket {
		CPlusClass(SocketServer) {
		public:
			SocketServer() = default;
			
			explicit SocketServer(uint16_t port) {
				//把socket和socket地址结构联系起来
				if (bind(port)) {
					printf("Server Bind Port : %d Failed!", port);
					exit(1);
				}
				//server_socket用于监听
				if (listen()) {
					printf("Server Listen Failed!");
					exit(1);
				}
			}
			
			int listen() {
				//server_socket用于监听
				return ::listen(server_socket, lengthOfListenQueue);
			}
			
			int bind() {
				//把socket和socket地址结构联系起来
				return ::bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
			}
			
			int bind(uint16_t port) {
				bzero(&server_addr, sizeof(server_addr)); //把一段内存区的内容全部设置为0
				server_addr.sin_family = AF_INET;
				server_addr.sin_addr.s_addr = htons(INADDR_ANY);
				server_addr.sin_port = htons(port);
				//创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
				server_socket = ::socket(PF_INET, SOCK_STREAM, 0);
				if (server_socket < 0) {
					printf("Create Socket Failed!");
					throw (CreateFailedException());
				}
				int opt = 1;
				setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
				//把socket和socket地址结构联系起来
				return bind();
			}
			
			int close() {
				return ::close(server_socket);
			}
			
			Socket accept() {
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
				
				return {new_server_socket, client_addr};
			}
			
			class ServerException : public std::exception {
			};
			
			class CreateFailedException : public ServerException {
			};
			
			class AcceptFailedException : public ServerException {
			};
		
		private:
			sockaddr_in server_addr{};
			int server_socket{};
			int lengthOfListenQueue = 20;
		};
	}
}


#endif //CPLUS_SOCKETSERVER_H
