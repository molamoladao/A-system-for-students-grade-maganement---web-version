#pragma once
#include"main.h"
#include"student.h"
#include<cstring>
#include<fstream>
#include<sstream>
#include<algorithm>
//#include<string.h>
using namespace std;

//vector<Course>can_course_list;//存储可选课程
Student now_student;

//显示学生信息
void Student::student_information(Student zancun)
{
	cout << "姓名：" << zancun.stu_name << endl;
	cout << "学院：" << zancun.stu_college << endl;
	cout << "班级：" << zancun.stu_class << endl;
	cout << "学号：" << zancun.stu_num << endl;
	cout << "===================" << endl;

}

//打印课程信息
void print_course_list(Course zancun)
{
	cout << "课程编号：" << zancun.NO<<endl;
	cout << "课程名称：" << zancun.couname<<endl;

	if (zancun.kind == 1) {
		cout << "课程类型：必修课" << endl;
	}
	else if (zancun.kind == 2) {
		cout << "课程类型：选修课" << endl;
	}

	cout << "课程学分：" << zancun.point << endl;
	cout << "===================" << endl;

}

//选课
void Student::course_choose()
{
	int SIGNAL = 0;

	while (!SIGNAL) {
		cout << "请输入你想选择的课程编号" << endl;
		int NO;
		cin >> NO;
		int signal = 0;
		while (!signal) {
			int found = 0;
			for (int i = 0; i < now_student.can_course_list.size(); i++) {
				if (NO == now_student.can_course_list[i].NO) {
					found = 1;
					cout << "请确认你将选择此课程:" << "1 for 确定; else for 取消" << endl;
					int n;
					cin >> n;
					if (n == 1) {
						//课程信息添加至学生信息中
						now_student.stu_course.push_back(now_student.can_course_list[i]);
  				        
						//将本学生信息添加到课程学生列表中
						for (int v = 0; v < course.size(); v++) {
							if (course[v].NO == NO) {
								course[v].stu_list.push_back(now_student);
							}
						}

						//将本学生信息添加到老师->课程->学生列表中
						int k;
						for (int l = 0; l < teacher.size(); l++) {
							for (int s = 0; s < teacher[l].tea_course.size(); s++) {
								if (teacher[l].tea_course[s].NO == NO) {
									teacher[l].tea_course[s].stu_list.push_back(now_student);
								}
							}

						}

						/*for (k = 0; k < course.size(); k++) {

							for (int l = 0; l < teacher.size(); l++) {
								for (int s = 0; s < teacher[l].tea_course.size(); s++) {
									if (teacher[l].tea_course[s].NO == NO) {
										teacher[l].tea_course[s].stu_list.push_back(now_student);
									}
								}

							}

							if (course[k].NO == now_student.can_course_list[i].NO) break;
						}*/

						//course[k].stu_list.push_back(now_student);

						//can_course_list里删去这个课程
						now_student.can_course_list.erase(now_student.can_course_list.begin() + i);

						signal = 1;
						SIGNAL = 1;//退出双层while循环
						break;//退出for循环
					}
					else {//取消，退出课程选择
						signal = 1;
						SIGNAL = 1;
						break;
					}					
				}
			}
			if(found==0) {
				cout << "对不起，此课程不在可选择范围内[要重新输入请先输入1；退出此操作请输入0]：";
				int a;
				cin >> a;
				if (a == 1) {
					found = 0;
					break;
				}
				else if (a == 0) {
					signal = 1;
					SIGNAL = 1;
				}
			}
		}
	}
}

//查看所有可选课程(选修)
void Student::show_allcan_course()
{
	int i, j;
	int jishu = 0;

	Course zancun;
	int m;
    
	if (now_student.can_course_list.size() > 0) {
		for (m = 0; m < now_student.can_course_list.size(); m++) {
			zancun = now_student.can_course_list[m];
			//cout << "===================" << endl;
			print_course_list(zancun);//打印课程列表
		}
		course_choose();//选课
	}

	else if (now_student.can_course_list.size() == 0) {
		cout << "对不起，没有可以选择的课程" << endl;
	}
	
}

//删除选课
void Student::course_delete()
{
	int class_NO;
	int havefound_signal=0;//已找到信号
	cout << "请输入想要删除的选修课编号:";
	cin >> class_NO;
	//Course *zancun;
	for (int k = 0; k < (now_student.stu_course).size(); k++) {
		if (class_NO == now_student.stu_course[k].NO && now_student.stu_course[k].kind == 2 && now_student.stu_course[k].grade<0) {
			havefound_signal = 1;
			cout << "你将要删去的课程是："<<endl;
			cout << "===================" << endl;
			print_course_list(now_student.stu_course[k]);
			cout << "请确认是否删去本课程：1for确认，；else for 取消" << endl;
			int a = 0;
			cin >> a;
			if (a == 1) {
				now_student.can_course_list.push_back(now_student.stu_course[k]);
				now_student.stu_course.erase(now_student.stu_course.begin() + k);//学生课程表中删去

				for (int i = 0; i < teacher.size(); i++) {//教师->教授的课->学生列表中删去
					for (int j = 0; j < teacher[i].tea_course.size(); j++) {
						if (teacher[i].tea_course[j].NO == class_NO) {//找到此课程
							for (int c = 0; c < teacher[i].tea_course[j].stu_list.size(); c++) {
								if (teacher[i].tea_course[j].stu_list[c].stu_num == now_student.stu_num) {
									teacher[i].tea_course[j].stu_list.erase(teacher[i].tea_course[j].stu_list.begin() + c);
								}

							}
							
						}
					}

				}
				break;
			}
			else break;
		}
	}
	if (havefound_signal == 0) {
		cout << "删除失败" << endl;
	}
}

//查看已选课程(选修)
void Student::show_student_course()
{
	Course zancun;
	int jishu = 0;

	for (int i= 0; i < (now_student.stu_course).size(); i++) {
		if (now_student.stu_course[i].kind == 2) {
			jishu++;
		}
	}

	if (jishu  == 0) {
		cout << "你还没有选择选修课" << endl;
	}

	else if (jishu > 0) {
		for (int k = 0; k < (now_student.stu_course).size(); k++) {
			if (now_student.stu_course[k].kind == 2) {
				zancun = now_student.stu_course[k];
				cout << "===================" << endl;
				print_course_list(zancun);
			}
		}
		int delet_signal = 0;
		cout << "是否要删除已选课程 1 for选择删除;else for不删除 " << endl;
		cin >> delet_signal;
		while (delet_signal == 1) {
			course_delete();//删除选课
			cout << "是否继续删除 1for继续 ；else for 退出" << endl;
			cin >> delet_signal;
		}
	}

	
}


//学生选课部分
void Student::for_course_choose()
{
	int signal = 0;
	int i;
	cout << "请选择要进行的操作：1.查看所有可选课程 2.查看所有已选课程" << endl;
	//cin >> i;
	while (!signal) {
		cin >> i;
		if (i == 1) {
			show_allcan_course();//查看所有可选课程
			signal = 1;
		}
		else if (i == 2) {
			show_student_course();//查看已选课程
			signal = 1;
		}
		else cout << "请输入正确序号" << endl;
	}
	
}

bool sgrade_increase(const Course &v1, const Course &v2) {
	return (v1.grade < v2.grade);
}
bool sgrade_decrease(const Course &v1, const Course &v2) {
	return (v1.grade > v2.grade);
}
bool sgradepoint_increase(const Course &v1, const Course &v2) {
	return(v1.grade_point < v2.grade_point);
}
bool sgradepoint_decrease(const Course &v1, const Course &v2) {
	return(v1.grade_point > v2.grade_point);
}

void Student::show_own_course()//查看自己的课程(选修+必修)
{

	Course zancun1;
	cout << "   必修课程：" << endl;
	for (int k = 0; k < (now_student.stu_course).size(); k++) {
		if (now_student.stu_course[k].kind == 1) {
			zancun1 = now_student.stu_course[k];
			print_course_list(zancun1);
		}
	}

	Course zancun2;
	cout << "   选修课程：" << endl;
	int nn = 0;
	int k;
	for (k = 0; k < (now_student.stu_course).size(); k++) {
		if (now_student.stu_course[k].kind == 2) {
			zancun2 = now_student.stu_course[k];
			nn ++;
			print_course_list(zancun2);
		}
	}
	if (nn == 0) {
		cout << "你还未选择选修课" << endl;
	}

}

void Student::show_all_course()//查看所有课程
{
	int k;

	Course zancun1;
	cout << "   必修课程：" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 1) {
			zancun1 = course[k];
			//cout << "===================" << endl;
			print_course_list(zancun1);
		}
	}

	Course zancun2;
	cout << "   选修课程：" << endl;
	for ( k = 0; k < course.size(); k++) {
		if (course[k].kind == 2) {
			zancun2 = course[k];
			//cout << "===================" << endl;
			print_course_list(zancun2);
		}
	}
}

//学生的课程查看操作
void Student::for_course_show()
{
	int signal = 0;
	int i;
	cout << "请选择要进行的操作：1.查看自己的课程 2.查看所有课程" << endl;
	cin >> i;
	while (!signal) {
		if (i == 1) {
			show_own_course();//查看自己的课程
			signal = 1;
		}
		else if (i == 2) {
			show_all_course();//查看所有课程
			signal = 1;
		}
		else cout << "请输入正确序号" << endl;
	}
}

//学生成绩查看
void Student::show_student_grade()
{
	//vector<Course*>stu_grade;学生成绩信息数组
	int k;

	cout << "请选择课程信息呈现方式：";
	cout << "1for按成绩升序；2for按成绩降序；3for按绩点升序；4for按绩点降序" << endl;

	string a;
	cin >> a;

	if (a == "1") {//1for按成绩升序
		sort(now_student.stu_course.begin(), now_student.stu_course.end(), sgrade_increase);
	}
	else if (a == "2") {//2for按成绩降序
		sort(now_student.stu_course.begin(), now_student.stu_course.end(), sgrade_decrease);
	}
	else if (a == "3") {//3for按绩点升序
		sort(now_student.stu_course.begin(), now_student.stu_course.end(), sgradepoint_increase);
	}
	else if (a == "4") {//4for按绩点降序
		sort(now_student.stu_course.begin(), now_student.stu_course.end(), sgradepoint_decrease);
	}
	else {
		cout << "输入不正确,按默认方式呈现" << endl;
	}

	for (k = 0; k < (now_student.stu_course).size(); k++) {
		cout << "课程：" << std::left << setw(10) << now_student.stu_course[k].couname ;

		if (now_student.stu_course[k].putin_key == 1) {
			cout << "成绩：" << std::left << setw(10) << now_student.stu_course[k].grade ;
			cout << "绩点：" << std::left << setw(10) << now_student.stu_course[k].grade_point << endl;

		}
		else if (now_student.stu_course[k].putin_key == 0) {
			cout << std::left << setw(10) <<"成绩:未录入" << endl;
		}
		
	}
}

//学生操作选择
void Student::show_student_choice()
{
	int signal = 0;//标识符
	while (!signal) {

		cout << "请选择将要进行的操作：1.课程选择 2.课程查询 3.成绩查询 4.注销登录" << endl;
		int i;
		cin >> i;

		if (i == 1) {
			for_course_choose();//选课部分
			//signal = 1;
		}
		else if (i == 2) {
			for_course_show();//课程查看部分
			//signal = 1;
		}
		else if (i == 3) {
			show_student_grade();//成绩查询部分
			//signal = 1;
		}
		else if (i == 4) {
			for (int i = 0; i < student.size(); i++) {
				if (student[i].stu_num == now_student.stu_num) {
					student[i] = now_student;
				}
			}
			cout << "||您已注销登录||" << endl;
			signal = 1;
			
		}
		else cout << "请输入正确序号" << endl;
	}
}

//学生注册
void Student::student_register(string a)
{
	Student zancun;
	int stusize = student.size();
	int signal = 0;//注册成功标识符

	cout << "|对不起，该用户信息不存在|" << endl;
	cout << "  |是否要注册用户信息？|" << endl;
	cout << "     1.注册 2.退出" << endl;
	int choose;
	cin >> choose;
	while (!signal ) {
		if (choose == 1) {
			zancun.stu_num = a;
			//strcpy_s(((string)zancun.stu_num).c_str(),a.size(), a.c_str());
			cout << "请输入学生姓名：";
			cin >> zancun.stu_name;
			cout << "请输入学生学院：";
			cin >> zancun.stu_college;
			cout << "请输入学生班级：";
			cin >> zancun.stu_class;

			for (int i = 0; i < course.size(); i++) {
				if (course[i].kind == 1) {
					zancun.stu_course.push_back(course[i]);
					course[i].stu_list.push_back(zancun);//初始时，必修课必须已被选
				}
				else if (course[i].kind == 2) {
					zancun.can_course_list.push_back(course[i]);
				}

				if (course[i].teacher_num != "-1") {//老师->课程信息的更新
					for (int l = 0; l < teacher.size(); l++) {
						for (int s = 0; s < teacher[l].tea_course.size(); s++) {
							if (teacher[l].tea_course[s].NO == course[i].NO) {
								teacher[l].tea_course[s].stu_list.push_back(zancun);
							}
						}
					}
				}
			}

			student.push_back(zancun);
			now_student = zancun;

			signal = 1;

			student_information(now_student);//显示学生信息
			show_student_choice();//显示学生可以进行的功能选择
		}
		else if (choose == 2) {
			//cout << "                ||您已退出学生成绩管理系统||" << endl;
			//system("pause");
			//exit(0);
			break;
			break;
		}
		else cout << "请输入正确序号" << endl;
	}
	//student_information(zancun);
}

//学生登录
void Student::student_login()
{
	string a;
	int stusize = student.size();
	cout << "您已选择了学生身份，请输入学号：";
	cin >> a  ;
    Student zancun;

	//初始情况，内部无信息
	if (stusize == 0) {
		student_register(a);//学生注册	
	}

	//内部有学生信息
	else if(stusize > 0) {
		int i ;

		int sig = 0;

		for (i = 0; i < student.size(); i++) {
			if (student[i].stu_num == a) {
				now_student = student[i];//拷贝
				sig = 1;
				
				student_information(now_student);//显示学生信息
				show_student_choice();//显示学生可以进行的功能选择
			}
		}

		
		if (sig==0) {//未查找到该序号
			student_register(a);//学生注册
		}
	}

	//show_student_choice();//显示学生可以进行的功能选择

}


void initial_studentlist()
{
	//学号 姓名 班级 学院 课程
	Student zancun;
	cout <<endl<< "**内置学生信息如下：" << endl;
	cout << "======================================" << endl;
	for (int i = 0; i < student.size(); i++) {
		zancun = student[i];
		cout << "学生学号：" << zancun.stu_num << endl;
		cout << "学生姓名：" << zancun.stu_name << endl;
		cout << "学生学院：" << zancun.stu_college << endl;
		cout << "学生课程：";

		for (int i = 0; i < zancun.stu_course.size(); i++) {
			cout << zancun.stu_course[i].NO << "-" << zancun.stu_course[i].couname << "  ";
		}
		cout << endl << "======================================" << endl;

	}

}

istream & operator >> (istream &in, Student &c)
{
	Course save;
	string  s;
	int jishu = 1;
	int coumun = 0;
	int done_key = 0;//一行是否读完的标志
	int line_num = 0;//一行元素的个数
	int sum = 0;//总元素个数
	int sum_jishu=1;//总元素个数计数
	try {
		while (in >> s) {
			stringstream ss(s);
			if (done_key == 0) {//算一行的元素个数
				ss >> coumun;
				line_num = 1 + 4 + coumun * 3;
				sum = sum + line_num;
				done_key = 1;
			}
			if (jishu % line_num == 1) {
				jishu++;
				sum_jishu++;
			}
			else if (jishu % line_num == 2) {
				c.stu_num = s;
				jishu++;
				sum_jishu++;
			}
			else if (jishu % line_num == 3) {
				c.stu_name = s;
				jishu++;
				sum_jishu++;
			}
			else if (jishu % line_num == 4) {
				c.stu_class = s;
				jishu++;
				sum_jishu++;
			}
			else if (jishu % line_num == 5) {
				c.stu_college = s;
				jishu++;
				sum_jishu++;
			}
			else if (jishu % line_num >= 6 || jishu % line_num == 0) {
				//Course save;
				if ((jishu - 5) % 3 == 1) {
					ss >> save.NO;
					jishu++;
					sum_jishu++;
				}
				else if ((jishu - 5) % 3 == 2) {
					ss >> save.grade;
					jishu++;
					sum_jishu++;
				}
				else if ((jishu - 5) % 3 == 0) {//某课程输入完毕
					ss >> save.grade_point;
					jishu++;
					sum_jishu++;

					for (int i = 0; i < course.size(); i++) {//课程信息更新
						if (course[i].NO == save.NO) {
							course[i].stu_list.push_back(c);//课程信息更新
							course[i].grade = save.grade;
							course[i].grade_point = save.grade_point;
							c.stu_course.push_back(course[i]);
						}
					}

					for (int i = 0; i < teacher.size(); i++) {//教师信息更新
						for (int j = 0; j < teacher[i].tea_course.size(); j++) {
							if (teacher[i].tea_course[j].NO == save.NO) {
								teacher[i].tea_course[j].stu_list.push_back(c);
								break;
								//break;
							}
						}
					}

					if (jishu > line_num) {//一行读完

						int had = 0;
						for (int i = 0; i < course.size(); i++) {//存入can_course_list存储可选课程
							for (int j = 0; j <c.stu_course.size(); j++) {
								if (course[i].NO == c.stu_course[j].NO) {
									had = 1;//此课程学生已选
								}
							}
							if (had == 1) {
								had = 0;
							}
							else if (had == 0) {//没找到
								c.can_course_list.push_back(course[i]);
							}
						}

						student.push_back(c);
						c.can_course_list.clear();
						c.stu_course.clear();
						done_key = 0;
						jishu = 1;
					}
				}
			}
		}
		if (sum_jishu <= sum) {
			throw"学生信息文件内容有误！";
		}
	}
	catch (char *msg) {
		cout << "错误！" << msg << endl;
		system("pause");
		exit(0);
	}
	
	return in;
}

ostream & operator << (ostream &out, const Student &c)
{
	//int cla_num = 0;
	for (int i = 0; i < student.size(); i++) {
		//cla_num = student[i].stu_course.size();
		out << student[i].stu_course.size() << " ";
		out << student[i].stu_num << " ";
		out << student[i].stu_name << " ";
		out << student[i].stu_class << " ";
		out << student[i].stu_college << " ";
		for (int j = 0; j < student[i].stu_course.size(); j++) {
			out << student[i].stu_course[j].NO << " ";
			out << student[i].stu_course[j].grade << " ";
			out << student[i].stu_course[j].grade_point << " ";
		}
		out << endl;
	}
	return out;
}

void student_save()
{
	ofstream out("C://Users//11794//Desktop//大二下coding test//学生成绩管理系统//学生成绩管理系统//student_information.txt");//打开文件
	Student c1;
	out << c1;

	out.close();
}

void initial_student()
{
	ifstream in("C://Users//11794//Desktop//大二下coding test//学生成绩管理系统//学生成绩管理系统//student_information.txt");//打开文件
	Student c1;
	in >> c1;

	initial_studentlist();
	in.close();

	/*
	Student save1, save2, save3,save4;
	//Course save2;
	//学号 姓名 班级 学院 课程 

	//学生1
	save1.stu_num = "1234";
	save1.stu_name = "JHS";
	save1.stu_class = "10";
	save1.stu_college = "scs";
	//int i;
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//存入必修课
			course[i].stu_list.push_back(save1);//课程信息更新
			save1.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save1.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save1.stu_course.size(); i++) {//教师信息更新
		for (int j = 0; j < teacher.size(); j++) {
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save1.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save1);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save1);

	//学生2
	save2.stu_num = "4321";
	save2.stu_name = "PJM";
	save2.stu_class = "11";
	save2.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//存入必修课
			course[i].stu_list.push_back(save2);//课程信息更新
			save2.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save2.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save2.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//教师信息更新
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save2.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save2);
					break;
					break;
					break;

				}
			}
		}
	}
	student.push_back(save2);

	//学生3
	save3.stu_num = "5678";
	save3.stu_name = "KTH";
	save3.stu_class = "12";
	save3.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//存入必修课
			course[i].stu_list.push_back(save3);//课程信息更新
			save3.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save3.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save3.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//教师信息更新
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save3.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save3);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save3);

	//学生4
	save4.stu_num = "8765";
	save4.stu_name = "JJK";
	save4.stu_class = "13";
	save4.stu_college = "scs";
	for (int i = 0; i < course.size(); i++) {
		if (course[i].kind == 1) {//存入必修课
			course[i].stu_list.push_back(save4);//课程信息更新
			save4.stu_course.push_back(course[i]);
		}
		else if (course[i].kind == 2) {
			save4.can_course_list.push_back(course[i]);
		}
	}
	for (int i = 0; i < save4.stu_course.size(); i++) {
		for (int j = 0; j < teacher.size(); j++) {//教师信息更新
			for (int k = 0; k < teacher[j].tea_course.size(); k++) {
				if (teacher[j].tea_course[k].NO == save4.stu_course[i].NO) {
					teacher[j].tea_course[k].stu_list.push_back(save4);
					break;
					break;
					break;
				}
			}
		}
	}
	student.push_back(save4);*/

	//initial_studentlist();
}