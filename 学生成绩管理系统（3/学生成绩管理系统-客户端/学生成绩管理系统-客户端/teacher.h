#ifndef _TEACHER_H_
#define _TEACHER_H_

#include"main.h"
//#include"student.h"
//#include"course.h"
class Teacher
{
public:
	Teacher() {
		
	}
	~Teacher() {

	}

	void teacher_register(string a);//教师注册
	void teacher_login();//教师登录
	void teacher_information(Teacher zancun);//显示教师信息

	void show_teacher_choice();//显示教师可以进行的功能选择
	//void choice(int choice1);//对教师的选择进行相应操作 

	void for_course_show();//课程查看部分
	void show_all_course();//查看所有课程 （区分必修，选修
	void show_teacher_course();//显示自己的所有课程（区分必修，选修
	void show_course_studentlist();//显示课程的所有选课学生名单 
	void show_specify_student_information(int nnum);//显示指定选课学生信息（包括成绩 

	void for_course_set();//成绩操作部分
	void set_student_grade(Student zancun, Course zancun2);//录入学生成绩
	void reset_student_grade(Student zancun, Course zancun2);//修改学生成绩
	void logon_student_grade(Course zancun2);//提交学生成绩

//private:
	
	//vector<get_grade>gather;//学生成绩存储数组
	//int student_count;//记录学生人数 
	//int teacher_count;//记录教师人数 
	string tea_num;//记录教师工号 
	string tea_name;//记录教师姓名
	string tea_collage;//记录教师学院 
	vector<Course>tea_course;//记录老师自己的课程

	friend ostream & operator << (ostream &out, const Teacher &c);
	friend istream & operator >> (istream &in, Teacher &c);
};
void initial_teacher();
void teacher_save();
#endif