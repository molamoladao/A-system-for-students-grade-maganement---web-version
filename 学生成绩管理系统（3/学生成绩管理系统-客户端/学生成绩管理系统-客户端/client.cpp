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
	//����Winsock�� 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	//��ʼ��socket��Դ 
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	while (true) {
		//����ͨѶSOCKET����ʽ�������׽���  
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return 0;
		}

		//����Ҫ���ӵĵ�ַ�Ͷ˿�
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		//��������������� 
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //����ʧ�� 
			printf("���ӷ�����ʧ��!\n");
			closesocket(sclient);
			system("pause");
			return 0;
		}

		//�����������������
		//�������� 
		char recData[2046];
		int ret= recv(sclient, recData, 2046, 0);	
		if (ret>0) {
			recData[ret] = 0x00;
			if (strcmp(recData, "��ȡ�ļ���������\n") == 0) {
				printf(recData);
				closesocket(sclient);
				break;
			}
			printf(recData);
		}

		char a = recData[0];
		char b = recData[1];
		char c = '-';
		//�������� 
		if ((a== c) && (b == c )) {

			string data;
			cin >> data;
			const char * sendData;
			sendData = data.c_str();   //stringתconst char* 
			send(sclient, sendData, strlen(sendData), 0);
			if (strcmp(data.c_str(), "shut_down") == 0) {
				closesocket(sclient);
				break;
			}
		}
		
		//�ͻ��˹ر�SOCKET 
		closesocket(sclient);
	}

	//�ͷ�Winsock��
	WSACleanup();
	cout << "�ͻ��˹ر�" << endl;
	system("pause");
	return 0;

}


