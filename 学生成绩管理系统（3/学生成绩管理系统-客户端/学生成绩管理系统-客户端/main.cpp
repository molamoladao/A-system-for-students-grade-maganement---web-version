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

int main(int argc, char* argv[])
{
	//加载Winsock库 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	//初始化socket资源 
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	int choice = 0;

	try {
		while (1) {

			cout << "请选择用户类型：1.学生   2.教师   3.退出" << endl;
			cin >> choice;

			if (choice == 1) {
				Student bridge;
				bridge.student_login();//学生登录
			}
			else if (choice == 2) {
				Teacher bridge;
				bridge.teacher_login();//教师登录
			}
			else if (choice == 3) {
				cout << "||您已退出学生成绩管理系统||" << endl;

				//存课程信息
				course_save();
				//存教师信息
				teacher_save();
				//存学生信息
				student_save();

				system("pause");
				exit(0);
			}
			else
				//cout << "请输入正确的序号" << endl;
				throw choice;
		}
	}
	catch (...)
	{
		cout << "error" << endl;
	}
	system("pause");
	return 0;

}