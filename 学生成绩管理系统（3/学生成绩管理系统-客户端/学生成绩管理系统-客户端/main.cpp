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

int main(int argc, char* argv[])
{
	//����Winsock�� 
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	//��ʼ��socket��Դ 
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	int choice = 0;

	try {
		while (1) {

			cout << "��ѡ���û����ͣ�1.ѧ��   2.��ʦ   3.�˳�" << endl;
			cin >> choice;

			if (choice == 1) {
				Student bridge;
				bridge.student_login();//ѧ����¼
			}
			else if (choice == 2) {
				Teacher bridge;
				bridge.teacher_login();//��ʦ��¼
			}
			else if (choice == 3) {
				cout << "||�����˳�ѧ���ɼ�����ϵͳ||" << endl;

				//��γ���Ϣ
				course_save();
				//���ʦ��Ϣ
				teacher_save();
				//��ѧ����Ϣ
				student_save();

				system("pause");
				exit(0);
			}
			else
				//cout << "��������ȷ�����" << endl;
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