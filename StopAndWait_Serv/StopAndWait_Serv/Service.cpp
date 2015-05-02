#include "StdAfx.h"
#include "Service.h"

Service::Service(void)
{
}

Service::~Service(void)
{
}

/************************************************************************/
/*
	Method      : init
	DATA		: 2015/05/02
	Author      : SkyLan
	Returns     : int �Ƿ��ʼ����ȷ
	Description : udp��ʼ������
 */
/************************************************************************/
int Service::init()
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
	sService.sin_family = AF_INET;
	sService.sin_port = htons(RECEIVE_PORT);
	sService.sin_addr.s_addr = 0;

	// �󶨱���UDP�˿��׽���
	err = bind(udpSocket, (SOCKADDR*)&sService, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err) {
		err = WSAGetLastError();
		printf("udp \"bind\" error! error code is %d/n", err);
		return -1;
	}

	return 1;
}

/************************************************************************/
/*
	Method      : receiveByUdp
	DATA		: 2015/05/02
	Author      : SkyLan
	Parameter   : char * _c
	Returns     : void
	Description : 
 */
/************************************************************************/
void Service::receiveByUdp(char* _c)
{
	int nAddrLen = sizeof(SOCKADDR);
	// ���ܻ���
	char receiveBuff[MAX_BUF_LEN] = "";
	// ��������
	int nReceiveSize = recvfrom(udpSocket, receiveBuff, MAX_BUF_LEN, 0, (SOCKADDR*)&sClient, &nAddrLen);

	if (SOCKET_ERROR == nReceiveSize) {
		int err = WSAGetLastError();
		printf("\"recvfrom\" error! error code is %d\n", err);
		return;
	}
	memcpy(_c, receiveBuff, MAX_BUF_LEN);
}


/************************************************************************/
/*
	Method      : sendByUdp
	DATA		: 2015/05/02
	Author      : SkyLan
	Parameter   : RETURN_TYPE _rt
	Returns     : int
	Description : 
 */
/************************************************************************/
int Service::sendByUdp(RETURN_TYPE _rt)
{
	char sendBuff[sizeof(RETURN_TYPE)] = "";
	memcpy(sendBuff, &_rt, sizeof(RETURN_TYPE));
	// ��������
	int nSendSize = sendto(udpSocket, sendBuff, sizeof(RETURN_TYPE), 0, (SOCKADDR*)&sClient, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nSendSize) {
		int err = WSAGetLastError();
		printf("\"sendto\" error!, error code is %d\n", err);
		return -1;
	}
	return 1;
}

void Service::destory()
{
	closesocket(udpSocket);
	WSACleanup();
}