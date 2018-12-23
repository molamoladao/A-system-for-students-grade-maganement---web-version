#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<istream>
#include<cstring>
#include<fstream>
#include<sstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//加载Winsock库 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	//初始化socket资源 
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	while (true) {
		//构造通讯SOCKET，流式，创建套接字  
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return 0;
		}

		//配置要连接的地址和端口
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		//请求与服务器连接 
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //连接失败 
			printf("连接服务器失败!\n");
			closesocket(sclient);
			system("pause");
			return 0;
		}

		//请求与服务器端连接
		//接收数据 
		char recData[2046];
		int ret= recv(sclient, recData, 2046, 0);	
		if (ret>0) {
			recData[ret] = 0x00;
			if (strcmp(recData, "读取文件内容有误！\n") == 0) {
				printf(recData);
				closesocket(sclient);
				break;
			}
			printf(recData);
		}

		char a = recData[0];
		char b = recData[1];
		char c = '-';
		//发送数据 
		if ((a== c) && (b == c )) {

			string data;
			cin >> data;
			const char * sendData;
			sendData = data.c_str();   //string转const char* 
			send(sclient, sendData, strlen(sendData), 0);
			if (strcmp(data.c_str(), "shut_down") == 0) {
				closesocket(sclient);
				break;
			}
		}
		
		//客户端关闭SOCKET 
		closesocket(sclient);
	}

	//释放Winsock库
	WSACleanup();
	cout << "客户端关闭" << endl;
	system("pause");
	return 0;

}


