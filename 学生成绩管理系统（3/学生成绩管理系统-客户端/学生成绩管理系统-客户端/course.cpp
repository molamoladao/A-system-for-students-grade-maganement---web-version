#pragma once
#include"course.h"
#include"main.h"
#include<fstream>
#include<sstream>

//extern vector<Course*>course;

/*void initial_course()//�γ̳�ʼ��ver1
{
	Course save;

	//cout << "++++++++++++������γ���Ϣ++++++++++++++" << endl;
	
	save.kind = 1;
	save.NO = 1;
	save.point = 4;
	save.couname = "Math";
	save.teacher_num = "1111";
    course.push_back(save);

	save.kind = 1;
	save.NO = 2;
	save.point = 5;
	save.couname = "English";
	save.teacher_num = "1111";
	course.push_back(save);

	save.kind = 1;
	save.NO = 3;
	save.point = 5;
	save.couname = "EE";
	save.teacher_num = "1111";
	course.push_back(save);

	save.kind = 1;
	save.NO = 4;
	save.point = 5;
	save.couname = "CS";
	save.teacher_num = "2222";
	course.push_back(save);


	save.kind = 2;
	save.NO = 5;
	save.point = 2;
	save.couname = "Music";
	save.teacher_num = "2222";
	course.push_back(save);
	
	save.kind = 2;
	save.NO = 6;
	save.point = 1;
	save.couname = "PE";
	save.teacher_num = "2222";
	course.push_back(save);

	save.kind = 2;
	save.NO = 7;
	save.point = 2;
	save.couname = "Chinese";
	save.teacher_num = "3333";
	course.push_back(save);

	save.kind = 2;
	save.NO = 8;
	save.point = 1;
	save.couname = "Dance";
	save.teacher_num = "3333";
	course.push_back(save);


	/*int done_signal = 1;
	int i = 0;

	while (done_signal == 1) {

		cout << "������γ�����[1 for ���޿� 2 for ѡ�޿�]:";
		cin >> save.kind;
		cout << "������γ̱��:";
		cin >> save.NO ;
		cout << "������γ�ѧ��:";
        cin >> save.point;
		cout << "������γ�����:";
		cin >> save.couname;

		course.push_back(save);

		cout << "�Ƿ��������[1 for ����,else forֹͣ]:" ;
		cin >> done_signal;
		if (done_signal != 1) break;
		
		i++;
	}
	*/	

void initial_courselist() 
{
	Course zancun;
	cout << "**���ÿγ���Ϣ���£�" << endl;
	cout << "===================" << endl;
	for (int i = 0; i < course.size(); i++) {
		zancun = course[i];
		cout << "�γ̱�ţ�" << zancun.NO << endl;
        cout << "�γ����ƣ�" << zancun.couname << endl;
		cout << "�γ̽�ʦ��ţ�" << zancun.teacher_num << endl;

		if (zancun.kind == 1) {
			cout << "�γ����ͣ����޿�" <<  endl;
		}
		else if (zancun.kind == 2) {
			cout << "�γ����ͣ�ѡ�޿�" << endl;
		}
		cout << "�γ�ѧ�֣�" << zancun.point << endl;
		cout << "===================" << endl;
	}

}

istream & operator >> (istream &in, Course &c)
{
	try {
		string  s;
		int jishu = 1;
		while (in >> s) {
			stringstream ss(s);
			if (jishu % 6 == 1) {
				//c.kind = 's';
				ss >> c.kind;
				jishu++;
			}
			else if (jishu % 6 == 2) {
				ss >> c.NO;
				jishu++;
			}
			else if (jishu % 6 == 3) {
				ss >> c.point;
				jishu++;
			}
			else if (jishu % 6 == 4) {
				c.couname = s;
				jishu++;
			}
			else if (jishu % 6 == 5) {
				c.teacher_num = s;
				jishu++;

			}
			else if (jishu % 6 == 0) {
				ss >> c.putin_key;
				jishu++;
				course.push_back(c);
			}

		}
		if (jishu % 6 != 1) {
			throw"�γ���Ϣ�ļ���������";
		}
	}
	catch (char *msg) {
		cout << "����" << msg << endl;
		system("pause");
		exit(0);
	}
	return in;
}

ostream & operator << (ostream &out, const Course &c)
{
	for (int i = 0; i < course.size(); i++) {
		out << course[i].kind << " ";
		out << course[i].NO << " ";
		out << course[i].point << " ";
		out << course[i].couname << " ";
		out << course[i].teacher_num << " ";
		out << course[i].putin_key << endl;
	}
	return out;
	//out<<
}

void course_save()
{
    ofstream out("C://Users//11794//Desktop//�����coding test//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//course_information.txt");//���ļ�
	Course c2;
	out << c2;
	out.close();
}

int coursemain()
{
	ifstream in("C://Users//11794//Desktop//�����coding test//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//course_information.txt");//���ļ�
	Course c1;
	in >> c1;
    initial_courselist();
    in.close();

	return 0;
}