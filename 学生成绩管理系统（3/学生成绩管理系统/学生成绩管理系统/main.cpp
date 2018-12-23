#pragma once
#include"main.h"
#include<fstream>
#include<sstream>
//#include"student.h"
//#include"teacher.h"
//#include"course.h"
//using namespace System1;

int reinitsiganl = 0;//注销信号

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
	//初始化WSA  
	sockVersion = MAKEWORD(2, 2);
	wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建用于监听的套接字  
	slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	//绑定套接字（使他可以被其他进程使用）
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//创建套接字队列，开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//循环接收数据  
	sClient;
	remoteAddr;
	nAddrlen = sizeof(remoteAddr);
	//char revData[255];

	//SSystem ssystem;
	//int choice = 0;
	//cout << " =================================================" << endl;
	//cout << "          ||欢迎进入学生成绩管理系统||" << endl;
	//cout << " =================================================" << endl;
	int first = 0;
	coursemain();
	initial_teacher();
	initial_student();


	try {
		while (1) {
			
			printf("等待连接...\n");
			//等待客户接入 
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			if (sClient == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

			/*sClient2 = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			if (sClient2 == INVALID_SOCKET)
			{
				printf("accept error !");
				continue;
			}
			printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));*/


			//发送数据  
			if (first == 0) {
				const char * sendData = "-----------------------------------------------\n          ||欢迎进入学生成绩管理系统||\n-----------------------------------------------\n \n--请选择用户类型：1.学生   2.教师   shut_down.退出\n";
				send(sClient, sendData, strlen(sendData), 0);
				first = 1;
				
			}
			else if (first == 1) {
				const char * sendData = "--请选择用户类型：1.学生   2.教师   shut_down.退出\n";
				send(sClient, sendData, strlen(sendData), 0);
			}
			//closesocket(sClient);

            //cout << "请选择用户类型：1.学生   2.教师   3.退出" << endl;
		
			//接收数据  
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				//printf(revData);
			}
			
			//cin >> choice;

			if (revData[0] == '1') {
				Student bridge;
				bridge.student_login();//学生登录
			}
			else if (revData[0] == '2') {
				Teacher bridge;
				bridge.teacher_login();//教师登录
			}
			else if (strcmp(revData,"shut_down")==0) {


				//closesocket(sClient);
				//sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);

				//发送数据  
				//const char * sendData = "||-您已退出学生成绩管理系统-||\n";
				//send(sClient, sendData, strlen(sendData), 0);
				//int k= send(sClient, sendData, strlen(sendData), 0);
				//cout << k;
				cout << endl << "||您已退出学生成绩管理系统||" << endl;


				//存课程信息
				course_save();
				//存教师信息
				teacher_save();
				//存学生信息
				student_save();

                closesocket(sClient);
				system("pause");
				exit(0);
			}
			else{
				//cout << "请输入正确的序号" << endl;
				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData = "输入不正确，已退出程序，请重启\n";
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

	//服务端关闭SOCKET  
	closesocket(slisten);

	//加载Winsock库
	WSACleanup();
	return 0;

}