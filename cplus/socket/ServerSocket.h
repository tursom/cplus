//
// Created by Tursom Ulefits on 2018/6/14.
//

#ifndef CPLUS_SOCKETSERVER_H
#define CPLUS_SOCKETSERVER_H

#include <strings.h>
#include "../tools/class.h"
#include "Socket.h"
#include "../lang/Long.h"

namespace cplus {
	namespace socket {
		CPlusClass(SocketServer) {
		public:
			SocketServer() = default;
			
			explicit SocketServer(uint16_t port);
			
			~SocketServer() {
				close();
			}
			
			int listen() const;
			
			int bind();
			
			int bind(uint16_t port);
			
			int close() const;
			
			Socket accept();
			
			class ServerException : public system::Exception {
			public:
				ServerException() = default;
				
				explicit ServerException(const char *message);
				
				explicit ServerException(const lang::String &message);
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
