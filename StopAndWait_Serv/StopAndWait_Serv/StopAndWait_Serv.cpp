// StopAndWait_Serv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Service.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Service serv;
	serv.init();

	int choose = 1;
	while(choose==1 || choose==2)
	{
		char* receiveBuff = new char[MAX_BUF_LEN];
		cout << "\nMessage from client:" << endl;
		serv.receiveByUdp(receiveBuff);
		cout << receiveBuff << endl;

		cout << "So, What's your plan?\n" 
			 << "1.You received right data.\n"
			 << "2.You received wrong data.\n"
			 << "3.This is too boring and exit!"
			 << endl;

		cin >> choose;
		switch(choose){
		case 1:
			serv.sendByUdp(ACK);
			break;
		case 2:
			serv.sendByUdp(NAK);
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
	return 0;
}

