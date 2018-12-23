#include "server.h"
#pragma comment(lib,"ws2_32.lib")  

int server(int argc, char* argv[])
{
	//����Winsock�� 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	//��ʼ��socket��Դ 
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�������SOCKET����ʽ�������׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);   //���ؼ����˿ڣ�8888
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) //���԰� 
	{
		printf("bind error !");
	}

	//�󶨳ɹ���ʼ������ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//ѭ����������  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		printf("�ȴ�����...\n");

		//�ȴ��ͻ����� 
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		//�ȴ��û����� 
		//��������  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}
		//��������  
		const char * sendData = "��ã�TCP�ͻ��ˣ�\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}
	//����˹ر�SOCKET  
	closesocket(slisten);

	//����Winsock��
	WSACleanup();
	return 0;
}