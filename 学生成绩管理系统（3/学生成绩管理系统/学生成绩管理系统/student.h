#ifndef _STUDENT_H_
#define _STUDENT_H_

#include"main.h"
class Course;
using namespace std;
class Student
{
public:
	Student() {
		vector<Course>stu_grade;//学生成绩信息数组
		string stu_num;//记录学生学号
		string stu_name;//记录学生姓名
		string stu_college;//记录学生学院
		string stu_class;//记录学生班级 
		vector<Course>stu_course;//记录学生自己的课程
		vector<Course>can_course_list;//存储可选课程
	}
	~Student() {

	}
	void student_register(string a);//学生注册
	void student_login();//学生登录
	void student_information(Student zancun);//显示学生信息

	void show_student_choice();//显示学生可以进行的功能选择
	//void choice(int choice2);//对学生的选择进行相应操作

	void for_course_choose();//选课部分
	void show_allcan_course();//查看所有可选课程
	void course_choose();//选课
	void show_student_course();//查看已选课程
	void course_delete();//删除课程

	void for_course_show();//查看课程部分
	void show_all_course();//查看所有课程
	void show_own_course();//查看自己的课程

	void show_student_grade();//查询学生成绩

//private:
	vector<Course>stu_grade;//学生成绩信息数组
	string stu_num;//记录学生学号
	string stu_name ;//记录学生姓名
	string stu_college ;//记录学生学院
	string stu_class ;//记录学生班级 

	vector<Course>stu_course;//记录学生自己的课程
	vector<Course>can_course_list;//存储可选课程
	friend ostream & operator << (ostream &out, const Student &c);
	friend istream & operator >> (istream &in, Student &c);
};

void initial_student();
void student_save();
#endif
