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
	}
}