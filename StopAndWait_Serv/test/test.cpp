// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

typedef enum A{
	ACK = 65131354351345,
	BCD = 1,
	CHC,
	JJBH,
	JHGI,
	HHJ,
	HHO
}A;
int _tmain(int argc, _TCHAR* argv[])
{
	printf("%d", sizeof(A));
	system("pause");
	return 0;
}

