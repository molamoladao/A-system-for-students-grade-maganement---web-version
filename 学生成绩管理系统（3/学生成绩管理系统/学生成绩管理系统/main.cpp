#pragma once
#include"main.h"
#include<fstream>
#include<sstream>
//#include"student.h"
//#include"teacher.h"
//#include"course.h"
//using namespace System1;

int reinitsiganl = 0;//ע���ź�

vector<Student>student;
vector<Teacher>teacher;
vector<Course>course;

SOCKET sClient;
SOCKET slisten;
sockaddr_in remoteAddr;
WORD sockVersion;
WSADATA wsaData;
int nAddrlen;
char revData[255];

int main(int argc, char* argv[])
{
	//��ʼ��WSA  
	sockVersion = MAKEWORD(2, 2);
	wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�������ڼ������׽���  
	slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	//���׽��֣�ʹ�����Ա���������ʹ�ã�
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//�����׽��ֶ��У���ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//ѭ����������  
	sClient;
	remoteAddr;
	nAddrlen = sizeof(remoteAddr);
	//char revData[255];

	//SSystem ssystem;
	//int choice = 0;
	//cout << " =================================================" << endl;
	//cout << "          ||��ӭ����ѧ���ɼ�����ϵͳ||" << endl;
	//cout << " =================================================" << endl;
	int first = 0;
	coursemain();
	initial_teacher();
	initial_student();


	try {
		while (1) {
			
			printf("�ȴ�����...\n");
			//�ȴ��ͻ����� 
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			if (sClient == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

			/*sClient2 = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			if (sClient2 == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));*/


			//��������  
			if (first == 0) {
				const char * sendData = "-----------------------------------------------\n          ||��ӭ����ѧ���ɼ�����ϵͳ||\n-----------------------------------------------\n \n--��ѡ���û����ͣ�1.ѧ��   2.��ʦ   shut_down.�˳�\n";
				send(sClient, sendData, strlen(sendData), 0);
				first = 1;
				
			}
			else if (first == 1) {
				const char * sendData = "--��ѡ���û����ͣ�1.ѧ��   2.��ʦ   shut_down.�˳�\n";
				send(sClient, sendData, strlen(sendData), 0);
			}
			//closesocket(sClient);

            //cout << "��ѡ���û����ͣ�1.ѧ��   2.��ʦ   3.�˳�" << endl;
		
			//��������  
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				//printf(revData);
			}
			
			//cin >> choice;

			if (revData[0] == '1') {
				Student bridge;
				bridge.student_login();//ѧ����¼
			}
			else if (revData[0] == '2') {
				Teacher bridge;
				bridge.teacher_login();//��ʦ��¼
			}
			else if (strcmp(revData,"shut_down")==0) {


				//closesocket(sClient);
				//sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

				//��������  
				//const char * sendData = "||-�����˳�ѧ���ɼ�����ϵͳ-||\n";
				//send(sClient, sendData, strlen(sendData), 0);
				//int k= send(sClient, sendData, strlen(sendData), 0);
				//cout << k;
				cout << endl << "||�����˳�ѧ���ɼ�����ϵͳ||" << endl;


				//��γ���Ϣ
				course_save();
				//���ʦ��Ϣ
				teacher_save();
				//��ѧ����Ϣ
				student_save();

                closesocket(sClient);
				system("pause");
				exit(0);
			}
			else{
				//cout << "��������ȷ�����" << endl;
				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData = "���벻��ȷ�����˳�����������\n";
				send(sClient, sendData, strlen(sendData), 0);

				throw revData;
            }
			closesocket(sClient);
		}
		
	}
	catch (...)
	{
		cout << "error" << endl;
	}
	system("pause");

	//����˹ر�SOCKET  
	closesocket(slisten);

	//����Winsock��
	WSACleanup();
	return 0;

}