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

class Client
{
public:
	Client(void);
	~Client(void);

	int receiveByUdp(RETURN_TYPE _rt, long _out_time_sec);
	int sendByUdp(char* _c);

	int init();
	void destory();

	SOCKET udpSocket;			// UDP套接字
	SOCKADDR_IN sSercice;			// Service套接字
	SOCKADDR_IN sClient;			// UDP接受本机套接字
};

