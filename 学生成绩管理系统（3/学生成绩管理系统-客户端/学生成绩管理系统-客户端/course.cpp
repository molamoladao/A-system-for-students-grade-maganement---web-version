#pragma once
#include"course.h"
#include"main.h"
#include<fstream>
#include<sstream>

//extern vector<Course*>course;

/*void initial_course()//课程初始化ver1
{
	Course save;

	//cout << "++++++++++++请输入课程信息++++++++++++++" << endl;
	
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

		cout << "请输入课程类型[1 for 必修课 2 for 选修课]:";
		cin >> save.kind;
		cout << "请输入课程编号:";
		cin >> save.NO ;
		cout << "请输入课程学分:";
        cin >> save.point;
		cout << "请输入课程名称:";
		cin >> save.couname;

		course.push_back(save);

		cout << "是否继续输入[1 for 继续,else for停止]:" ;
		cin >> done_signal;
		if (done_signal != 1) break;
		
		i++;
	}
	*/	

void initial_courselist() 
{
	Course zancun;
	cout << "**内置课程信息如下：" << endl;
	cout << "===================" << endl;
	for (int i = 0; i < course.size(); i++) {
		zancun = course[i];
		cout << "课程编号：" << zancun.NO << endl;
        cout << "课程名称：" << zancun.couname << endl;
		cout << "课程教师编号：" << zancun.teacher_num << endl;

		if (zancun.kind == 1) {
			cout << "课程类型：必修课" <<  endl;
		}
		else if (zancun.kind == 2) {
			cout << "课程类型：选修课" << endl;
		}
		cout << "课程学分：" << zancun.point << endl;
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
			throw"课程信息文件内容有误！";
		}
	}
	catch (char *msg) {
		cout << "错误！" << msg << endl;
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
    ofstream out("C://Users//11794//Desktop//大二下coding test//学生成绩管理系统//学生成绩管理系统//course_information.txt");//打开文件
	Course c2;
	out << c2;
	out.close();
}

int coursemain()
{
	ifstream in("C://Users//11794//Desktop//大二下coding test//学生成绩管理系统//学生成绩管理系统//course_information.txt");//打开文件
	Course c1;
	in >> c1;
    initial_courselist();
    in.close();

	return 0;
}