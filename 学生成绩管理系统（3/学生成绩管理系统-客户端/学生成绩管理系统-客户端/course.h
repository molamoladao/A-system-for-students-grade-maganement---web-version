#ifndef _COURSE_H_
#define _COURSE_H_
//#include<cstring>
//#include<string>
//#include<vector>
#include"main.h"
class Student;
using namespace std;

class Course{//非多态类型
public:
	Course() {
		
	}
	~Course() {

	}
	
	int kind;//课程属性类型---1for必修；2for选修
	int NO;//课程编号 
	int point;//学分 
	string couname ;//课程名字
	string teacher_num = "-1";//本课程教师工号

	int putin_key = 0;//本课程成绩是否提交的判断信号
	int grade = -1;//成绩
	double grade_point = -1;//绩点

	vector<Student>stu_list;//本课程学生名单及成绩信息


	virtual double find_garde(Course a,int sum) const {
		return -1;
	}//绩点计算 

	

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);
};

class Bixiu :public Course{//多态类型
public:
	
	virtual double find_garde(Course a,int sum) const {//绩点计算
		a.grade_point =((double)a.grade/ sum)*a.point;
		return a.grade_point;
	} 

	int kind;//课程属性类型---1for必修；2for选修
	int NO;//课程编号 
	int point;//学分 
	string couname;//课程名字

	int grade = -1;//成绩
	double grade_point = -1;//绩点

	int putin_key = 0;//本课程成绩是否提交的判断信号

	string teacher_num= "-1";//本课程教师工号
	vector<Student>stu_list;//本课程学生名单及成绩信息

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);
};

class Xuanxiu :public Course{//多态类型
public:

	int kind;//课程属性类型---1for必修；2for选修
	int NO;//课程编号 
	int point;//学分 
	string couname;//课程名字

	int grade = -1;//成绩
	double grade_point = -1;//绩点

	int putin_key = 0;//本课程成绩是否提交的判断信号

	string teacher_num="-1";//本课程教师工号
	vector<Student>stu_list;//本课程学生名单及成绩信息

	virtual double find_garde(Course a,int sum) const {//绩点计算 
		a.grade_point = (double)((sqrt(a.grade) / 10)*(a.point));
		return a.grade_point;
	}

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);

};

int coursemain();
void course_save();

#endif