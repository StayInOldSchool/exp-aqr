#pragma once

#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_PORT 8000
#define MAX_BUF_LEN 512
#define SERVICE_IP "127.0.0.1"

using namespace std;

typedef enum {
	ACK = 0,
	NAK = 1
}RETURN_TYPE;

class Service
{
public:
	Service(void);
	~Service(void);

	void receiveByUdp(char* _c);
	int sendByUdp(RETURN_TYPE);

	int init();
	void destory();

private:
	SOCKET udpSocket;			// UDP套接字
	SOCKADDR_IN sService;			// Service套接字
	SOCKADDR_IN sClient;			// UDP接受本机套接字
};

