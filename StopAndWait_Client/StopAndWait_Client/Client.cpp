#include "StdAfx.h"
#include "Client.h"


Client::Client(void)
{
}


Client::~Client(void)
{
}

int Client::init()
{
	// 加载套接字库（必须）
	WORD wVersionRequested;
	WSADATA wsaData;
	// 套接字加载时错误提示
	int err;

	// 启动socket api,版本2.2 
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//找不到winsock.dll
		printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	// 低字节，高字节
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		// 版本错误
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return -1;
	}

	// 创建UDP套接字
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == udpSocket) {
		err = WSAGetLastError();
		printf("\"socket\" error! error code is %d\n", err);
		return -1;
	}

	// Service套接字
	sSercice.sin_family = AF_INET;
	sSercice.sin_port = htons(RECEIVE_PORT);
	sSercice.sin_addr.s_addr = inet_addr(SERVICE_IP);

	return 1;
}

/************************************************************************/
/*
	Method      : sendByUdp
	DATA		: 2015/05/02
	Author      : SkyLan
	Parameter   : char * _c
	Returns     : int
	Description : Udp发送
 */
/************************************************************************/
int Client::sendByUdp(char* _c)
{
	char sendBuff[MAX_BUF_LEN] = "";
	memcpy(sendBuff, _c, MAX_BUF_LEN);
	// 发送数据
	int nSendSize = sendto(udpSocket, sendBuff, MAX_BUF_LEN, 0, (SOCKADDR*)&sSercice, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nSendSize) {
		int err = WSAGetLastError();
		printf("\"sendto\" error!, error code is %d\n", err);
		return -1;
	}
	return 1;
}

void Client::destory()
{
	closesocket(udpSocket);
	WSACleanup();
}