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
	// �����׽��ֿ⣨���룩
	WORD wVersionRequested;
	WSADATA wsaData;
	// �׽��ּ���ʱ������ʾ
	int err;

	// ����socket api,�汾2.2 
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//�Ҳ���winsock.dll
		printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	// ���ֽڣ����ֽ�
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		// �汾����
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return -1;
	}

	// ����UDP�׽���
	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == udpSocket) {
		err = WSAGetLastError();
		printf("\"socket\" error! error code is %d\n", err);
		return -1;
	}

	// Service�׽���
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
	Description : Udp����
 */
/************************************************************************/
int Client::sendByUdp(char* _c)
{
	char sendBuff[MAX_BUF_LEN] = "";
	memcpy(sendBuff, _c, MAX_BUF_LEN);
	// ��������
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