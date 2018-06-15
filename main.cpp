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

using namespace cplus::lang;
using namespace cplus::utils;
using namespace cplus::system;
using namespace cplus::thread;
using namespace cplus::socket;

#define HELLO_WORLD_SERVER_PORT    6666
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

void client() {
	char host[] = "localhost";
	char port[] = "0";
	//设置一个socket地址结构client_addr,代表客户机internet地址, 端口
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr)); //把一段内存区的内容全部设置为0
	client_addr.sin_family = AF_INET;    //internet协议族
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
	client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
	//创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		printf("Create Socket Failed!\n");
		exit(1);
	}
	//把客户机的socket和客户机的socket地址结构联系起来
	if (bind(client_socket, (struct sockaddr *) &client_addr, sizeof(client_addr))) {
		printf("Client Bind Port Failed!\n");
		exit(1);
	}
	
	//设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
	sockaddr_in server_addr{};
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (inet_aton(host, &server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
	{
		printf("Server IP Address Error!\n");
		exit(1);
	}
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);
	//向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
	if (connect(client_socket, (struct sockaddr *) &server_addr, server_addr_length) < 0) {
		printf("Can Not Connect To %s!\n", host);
		exit(1);
	}
	
	char file_name[FILE_NAME_MAX_SIZE + 1];
	bzero(file_name, FILE_NAME_MAX_SIZE + 1);
	printf("Please Input File Name On Server:\t");
	scanf("%s", file_name);
	
	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	strncpy(buffer, file_name, strlen(file_name) > BUFFER_SIZE ? BUFFER_SIZE : strlen(file_name));
	//向服务器发送buffer中的数据
	send(client_socket, buffer, BUFFER_SIZE, 0);

//    int fp = open(file_name, O_WRONLY|O_CREAT);
//    if( fp < 0
	
	//从服务器接收数据到buffer中
	bzero(buffer, BUFFER_SIZE);
	int length = 0;
	length = static_cast<int>(recv(client_socket, buffer, BUFFER_SIZE, 0));
	while (length) {
		if (length < 0) {
			printf("Recieve Data From Server %s Failed!\n", host);
			break;
		}
		bzero(buffer, BUFFER_SIZE);
		length = static_cast<int>(recv(client_socket, buffer, BUFFER_SIZE, 0));
	}
	printf("Recieve File:\t %s From Server[%s] Finished\n", file_name, host);
	
	//关闭socket
	close(client_socket);
}

int main() {
	char str[] = "12345\0\0\0\0\0\0\0\0\0\0\0";
	ByteArray byteArray(str, sizeof(str));
	std::cout << std::string(byteArray.getBuffer(), byteArray.indexOf(0)) << std::endl;
	std::set<std::string> stringSet;
	std::string ss1 = std::string("hello");
	std::string ss2 = std::string("hello");
	std::cout << stringSet.size() << std::endl;
	auto value = stringSet.emplace(ss1);
	std::cout << stringSet.size() << std::endl;
	String s1(ss1);
	String s2(ss2);
	std::cout << s1.stdString() << std::endl
	          << s2.stdString() << std::endl;
	std::cout << ((&s1.stdString() == &s2.stdString()) ? "true" : "false") << std::endl
	          << ((&s1.stdString() == &ss1) ? "true" : "false") << std::endl
	          << ((&s1.stdString() == &ss2) ? "true" : "false") << std::endl;
//	Thread::exitThread();
	return 0;
}