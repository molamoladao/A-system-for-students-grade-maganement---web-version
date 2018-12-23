#include "server.h"
#pragma comment(lib,"ws2_32.lib")  

int server(int argc, char* argv[])
{
	//加载Winsock库 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	//初始化socket资源 
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//构造监听SOCKET，流式，创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);   //本地监听端口：8888
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) //尝试绑定 
	{
		printf("bind error !");
	}

	//绑定成功后开始监听开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		printf("等待连接...\n");

		//等待客户接入 
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		//等待用户接入 
		//接收数据  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}
		//发送数据  
		const char * sendData = "你好，TCP客户端！\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}
	//服务端关闭SOCKET  
	closesocket(slisten);

	//加载Winsock库
	WSACleanup();
	return 0;
}