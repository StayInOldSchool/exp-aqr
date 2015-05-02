// StopAndWait_Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Client.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Client cl;
	if (cl.init()==-1)
	{
		cout << "Init Wrong!\n";
		cl.destory();
		return -1;
	}
	
	// 超时设置	
	struct timeval out_time;
	out_time.tv_sec = 5;		// 设置延迟时间参数
	out_time.tv_usec = 0;
	
	// 接受缓存
	char receiveBuff[sizeof(RETURN_TYPE)] = "";
	char* sendBuff = new char[MAX_BUF_LEN];
	int nAddrLen = sizeof(SOCKADDR);

	RETURN_TYPE x = ACK;
	int messageNum = 0;
	while(true) {

		sprintf_s(sendBuff, MAX_BUF_LEN, "Hey, I'm sending you No.%d Message!", messageNum);
		printf("Hey, I'm sending you No.%d Message!\n", messageNum);
		cl.sendByUdp(sendBuff);

		FD_SET fdr = {1, cl.udpSocket};
		// zero-超时 nonzero-未超时
		int n_select_ret = select(0, &fdr, NULL, NULL, &out_time);
		if(n_select_ret == SOCKET_ERROR)
		{
			printf("\"select\" error! error code is %d\n", WSAGetLastError());
			return -1;
		}
		if(n_select_ret == 0)
		{
			printf("It's time out, try to send him again...\n");
			continue;
		}
		else
		{
			if(recvfrom(cl.udpSocket, receiveBuff, sizeof(RETURN_TYPE), 0, (SOCKADDR*)&cl.sSercice, &nAddrLen) == SOCKET_ERROR)
			{
				printf("\"recvfrom\" error! error code is %d\n", WSAGetLastError());
				cout << "Please open your service first!!\n";
				system("pause");
				return -1;
			}
			memcpy(&x, receiveBuff, sizeof(RETURN_TYPE));
			if (x == ACK)
			{
				messageNum++;
			}
			else
			{
				printf("Service received wrong data, try to send him again...\n");
			}
		}
	}
	cl.destory();
	return 0;
}

