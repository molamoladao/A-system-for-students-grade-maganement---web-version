#pragma once
#include"main.h"
#include"teacher.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstring>
#include<algorithm>

using namespace std;

extern SOCKET sClient;
extern SOCKET slisten;
extern sockaddr_in remoteAddr;
//extern sockaddr_in sin;
extern WORD sockVersion;
extern WSADATA wsaData;
extern int nAddrlen;
extern char revData[255];

Teacher now_teacher;
class Course;

int NUM = 0;

void Teacher::teacher_information(Teacher zancun)
{
	vector<string>ssend;
	ssend.push_back("教师姓名：");
	ssend.push_back(zancun.tea_name);
	ssend.push_back("\n");

	ssend.push_back("教师学院：");
	ssend.push_back(zancun.tea_collage);
	ssend.push_back("\n");

	ssend.push_back("教师工号：");
	ssend.push_back(zancun.tea_num);
	ssend.push_back("\n");
	//cout << "教师姓名：" << zancun.tea_name << endl;
	//cout << "教师学院：" << zancun.tea_collage << endl;
	//cout << "教师工号：" << zancun.tea_num << endl;
	if ((zancun.tea_course).size() == 0) {
		ssend.push_back("教授课程：[该老师无教授的课程]");
		//ssend.push_back(zancun.tea_collage);
		ssend.push_back("\n");
		//cout << "教授课程：[该老师无教授的课程]" << endl;
	}
	else if ((zancun.tea_course).size() > 0) {
		ssend.push_back("教授课程：");
		//cout << "教授课程：";
		stringstream k;
		int kk;
		for (int i = 0; i < (zancun.tea_course).size(); i++) {
			kk = zancun.tea_course[i].NO;
			k << kk;
			ssend.push_back(k.str());
			k.str("");
			ssend.push_back("-");
			//k = zancun.tea_course[i].couname;
			ssend.push_back(zancun.tea_course[i].couname);
			ssend.push_back("  ");
			//cout << zancun.tea_course[i].NO << "-" << zancun.tea_course[i].couname << "  ";
		}
		ssend.push_back("\n");
	}
	ssend.push_back("===================\n");

	stringstream ss;
	for (int i = 0; i < ssend.size(); i++) {
		ss << ssend[i];
	}
	//ss >> sendData;
	
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const string& sendDataa=ss.str();
	const char * sendData= sendDataa.c_str();

    //sendData << (ss.str()).c_str();
	send(sClient, sendData, strlen(sendData), 0);
	ss.clear();
	ssend.clear();
}

//打印课程信息
void print_course_list2(Course  zancun)
{
	stringstream s;
	vector<string>ssend;

	ssend.push_back("课程编号：");
	s << zancun.NO;
	ssend.push_back(s.str());
	s.str("");
	ssend.push_back("\n");

	ssend.push_back("课程名称：");
	ssend.push_back(zancun.couname);
	ssend.push_back("\n");

	ssend.push_back("课程类型：");
	s << zancun.kind;
	ssend.push_back(s.str());
	s.str("");
	ssend.push_back("\n");

	ssend.push_back("课程学分：");
	s << zancun.point;
	ssend.push_back(s.str());
	s.str("");
	ssend.push_back("\n");

	ssend.push_back("===================\n");

	stringstream ss;
	for (int i = 0; i < ssend.size(); i++) {
		ss << ssend[i];
	}

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const string& sendDataa = ss.str();
	const char * sendData = sendDataa.c_str();

	//sendData << (ss.str()).c_str();
	send(sClient, sendData, strlen(sendData), 0);
	ss.clear();
	ssend.clear();
	/*cout << "课程编号：" << zancun.NO << endl;
	cout << "课程名称：" << zancun.couname << endl;
	cout << "课程类型：" << zancun.kind << endl;
	cout << "课程学分：" << zancun.point << endl;
	cout << "===================" << endl;*/
}
//录入指定选课的指定学生成绩
void Teacher::set_student_grade(Student zancun, Course zancun2)
{
	int ggrade;
	//cout << "请输入成绩[范围：0-100]：";

	int i, j, k;
	//int cc = 0;
	while (1) {
		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const char * sendData = "--请输入成绩[范围：0-100]：";
		send(sClient, sendData, strlen(sendData), 0);
		//cout << "请输入成绩[范围：0-100]：";
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			//printf(revData);
		}
		string gggrade = revData;
		stringstream _ggrade;
		_ggrade << gggrade;
		_ggrade >> ggrade;

		//cin >> ggrade;
		if (ggrade >= 0 && ggrade <= 100) {//成绩范围符合要求
			//学生类更新
			for (int mm = 0; mm < student.size(); mm++) {
				for (int nn = 0; nn < student[mm].stu_course.size(); nn++) {
					if (student[mm].stu_num == zancun.stu_num && student[mm].stu_course[nn].NO == zancun2.NO) {
						student[mm].stu_course[nn].grade = ggrade;
					}
				}				
			}
			//教师类更新
			for (int ii = 0; ii < now_teacher.tea_course.size(); ii++) {
				for (int jj = 0; jj < now_teacher.tea_course[ii].stu_list.size(); jj++) {
					if (now_teacher.tea_course[ii].NO == zancun2.NO && now_teacher.tea_course[ii].stu_list[jj].stu_num == zancun.stu_num) {
						for (int kk = 0; kk < now_teacher.tea_course[ii].stu_list[jj].stu_course.size(); kk++) {
                             if (now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].NO == zancun2.NO) {
	                             now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].grade = ggrade;
                             }
						}
					}
				}
			}

			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "成绩记录成功！\n";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "成绩记录成功！" << endl;
			break;

		}
		else if (ggrade < 0 || ggrade>100) {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "--输入不符合规范，请重新录入成绩[成绩范围：0-100]：";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "输入不符合规范，请重新录入成绩[成绩范围：0-100]：";
		}

	}

}

//修改指定选课的指定学生成绩
void Teacher::reset_student_grade(Student zancun, Course zancun2)
{

	int ggrade;
	//cout << "请输入成绩[范围：0-100]：";

	int i, j, k;
	//int cc = 0;
	while (1) {

		cout << "请输入成绩[范围：0-100]：";
		cin >> ggrade;
		if (ggrade >= 0 && ggrade <= 100) {//成绩范围符合要求
			//学生类更新
			for (int mm = 0; mm < student.size(); mm++) {
				if (student[mm].stu_num == zancun.stu_num) {//找到某学生
					for (int nn = 0; nn < student[mm].stu_course.size(); nn++) {
						if (student[mm].stu_course[nn].NO == zancun2.NO) {//找到某学生的某课程
							student[mm].stu_course[nn].grade = ggrade;
						}
					}
				}
			}

			//教师学生交互信息更新
			for (int ii = 0; ii < now_teacher.tea_course.size(); ii++) {
				if (now_teacher.tea_course[ii].NO == zancun2.NO) {//找到某老师的某课程
					for (int jj = 0; jj < now_teacher.tea_course[ii].stu_list.size(); jj++) {
						if (now_teacher.tea_course[ii].stu_list[jj].stu_num == zancun.stu_num) {//找到此课程中的某学生
							for (int kk = 0; kk < now_teacher.tea_course[ii].stu_list[jj].stu_course.size(); kk++) {
								if (now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].NO == zancun2.NO) {//找到这个学生的指定课程
									now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].grade = ggrade;
								}
							}
						}
					}
				}
				
			}
			//========================================================================

			//教师信息修改
			for (int i = 0; i < now_teacher.tea_course.size(); i++) {
				if (now_teacher.tea_course[i].NO == zancun2.NO) {
					now_teacher.tea_course[i].grade = ggrade;
				}
			}
			
			//===========================================================================

			cout << "成绩修改成功！" << endl;
			break;

		}
		else if (ggrade < 0 || ggrade>100) {
			cout << "输入不符合规范，请重新输入新成绩[成绩范围：0-100]：";
		}

	}

}


//提交本课程学生成绩
void Teacher::logon_student_grade(Course  zancun2)
{
	Course *a = new Bixiu();
	Course *b = new Xuanxiu();

	//打印课程信息
	//print_course_list2(zancun2);
	
	int x,y;
	double u;
	Course ssave;
	for (x = 0; x < zancun2.stu_list.size(); x++) {//老师->课程->学生列表
		for (int y = 0; y < zancun2.stu_list[x].stu_course.size(); y++) {//老师->课程->学生列表->单个学生的课程列表
			if (zancun2.stu_list[x].stu_course[y].NO == zancun2.NO) {//老师->课程->学生列表->单个学生的课程列表->某课程序号等于传入的课程序号
				ssave = zancun2.stu_list[x].stu_course[y];
				ssave.stu_list = zancun2.stu_list;

				int sum = 0;//本课程学生成绩分数和
				for (int i=0; i < zancun2.stu_list.size(); i++) {
					for (int j=0; j < zancun2.stu_list[i].stu_course.size(); j++) {
						if (zancun2.stu_list[i].stu_course[j].NO == zancun2.NO) {
							sum = sum + zancun2.stu_list[i].stu_course[j].grade;
						}
					}
				}

				//print_course_list2(ssave);
				//int g = ssave.stu_list.size();
				//cout << "学生个数：" << g << endl;
				//double u;

				if (zancun2.kind == 1) {
					u = a->find_garde(ssave,sum);
				}
				else if (zancun2.kind == 2) {
					u = b->find_garde(ssave,sum);
				}

				ssave.putin_key = 1;
				ssave.grade_point = u;

				//cout << "绩点："<<u << endl;
				//cout << "绩点：" << ssave.grade_point << endl;

				//课程信息修改
				for (int i = 0; i < course.size(); i++) {
					if (course[i].NO == zancun2.NO) {
						course[i].putin_key = 1;
					}
				}

				//教师信息修改
				/*for (int i = 0; i < now_teacher.tea_course.size(); i++) {

					if (now_teacher.tea_course[i].NO == ssave.NO) {
						//now_teacher.tea_course[i] = ssave;
						now_teacher.tea_course[i].grade_point = ssave.grade_point;
						now_teacher.tea_course[i].putin_key = ssave.putin_key;
					}
				}*/

				//教师学生交互信息修改
				for (int i = 0; i < now_teacher.tea_course.size(); i++) {
					if (now_teacher.tea_course[i].NO == zancun2.NO) {//对教师的指定课程操作
						for (int j = 0; j < now_teacher.tea_course[i].stu_list.size(); j++) {
							if (now_teacher.tea_course[i].stu_list[j].stu_num == zancun2.stu_list[x].stu_num) {//指定课程的指定学生
								for (int k = 0; k < now_teacher.tea_course[i].stu_list[j].stu_course.size(); k++) {
									if (now_teacher.tea_course[i].stu_list[j].stu_course[k].NO == zancun2.NO) {
										now_teacher.tea_course[i].stu_list[j].stu_course[k] = ssave;
										//now_teacher.tea_course[i].stu_list[j].stu_course[k].grade_point = ssave.grade_point;
										//now_teacher.tea_course[i].stu_list[j].stu_course[k].putin_key = ssave.putin_key;
									}
								}
							}
						}
					}					
				}

				//学生信息修改
				for (int i = 0; i < student.size(); i++) {
					if (student[i].stu_num == zancun2.stu_list[x].stu_num) {
						for (int j = 0; j < student[i].stu_course.size(); j++) {
							if (student[i].stu_course[j].NO == ssave.NO) {
								student[i].stu_course[j] = ssave;
								//student[i].stu_course[j].grade_point = zancun2.grade_point;
								//student[i].stu_course[j].putin_key = zancun2.putin_key;
							}
						}
					}	
				}
			}
		}
	}
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "成绩提交成功\n";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "成绩提交成功" << endl;
}

//成绩操作部分
void Teacher::for_course_set()
{
	//Course  zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--请输入想要进行操作的课程编码：";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "请输入想要进行操作的课程编码：";
	int a,b,k;
	b = 0;

	int ret = recv(sClient, revData, 255, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
	}
	a = int(revData[0] - '0');

	int pp = 0;
	int ssg = 0;
	while (pp == 0) {
		for (k = 0; k < (now_teacher.tea_course).size(); k++) {
			if (now_teacher.tea_course[k].NO == a) {//找到课程
				ssg = 1;
				
				if (now_teacher.tea_course[k].putin_key == 0 && now_teacher.tea_course[k].stu_list.size()>0) {//成绩未提交
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "--请选择成绩操作类型：1 for 成绩录入、修改;2 for 成绩提交 \n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "请选择成绩操作类型：1 for 成绩录入、修改;2 for 成绩提交 " << endl;
					int ret = recv(sClient, revData, 255, 0);
					if (ret > 0)
					{
						revData[ret] = 0x00;
					}
					b = int(revData[0] - '0');
					//cin >> b;
					if (b == 1) {
						closesocket(sClient);
						sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
						const char * sendData = "--请选择想要进行成绩操作的学生(学号):";
						send(sClient, sendData, strlen(sendData), 0);
						//cout << "请选择想要进行成绩操作的学生(学号):";
						string stunnum;
						int ret = recv(sClient, revData, 255, 0);
						if (ret > 0)
						{
							revData[ret] = 0x00;
						}
						stunnum = revData;
						//cin >> stunnum;
						int q;
						int found = 0;//是否在本课程中找到此学生
						for (q = 0; q < (now_teacher.tea_course[k].stu_list).size(); q++) {
							if (now_teacher.tea_course[k].stu_list[q].stu_num == stunnum) {
								found = 1;
								pp = 1;
								closesocket(sClient);
								sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
								const char * sendData = "--请选择操作：1 for 成绩录入；2 for 成绩修改\n";
								send(sClient, sendData, strlen(sendData), 0);
								//cout << "--请选择操作：1 for 成绩录入；2 for 成绩修改" << endl;
								int qq = 0;
								while (qq == 0) {
									//Student zancun;
									//zancun = now_teacher.tea_course[k].stu_list[q];
									int c = 0;
									int ret = recv(sClient, revData, 255, 0);
									if (ret > 0)
									{
										revData[ret] = 0x00;
									}
									c = int(revData[0] - '0');
									//cin >> c;
									if (c == 1) {
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//录入学生成绩
										qq = 1;
									}
									else if (c == 2) {
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//修改学生成绩
										qq = 1;
									}
									else {
										closesocket(sClient);
										sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
										const char * sendData = "--操作选择有误，请重新输入：";
										send(sClient, sendData, strlen(sendData), 0);
										//cout << "操作选择有误，请重新输入：";
									}
										
								}

							}
						}
						if (found == 0) {
							closesocket(sClient);
							sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
							const char * sendData = "该学生未选择此课程\n";
							send(sClient, sendData, strlen(sendData), 0);
							//cout << "该学生未选择此课程" << endl;
						}
					}
					else if (b == 2) {
						int putin_done=0;
						for (int v = 0; v < now_teacher.tea_course[k].stu_list.size(); v++) {
							for (int u = 0; u < now_teacher.tea_course[k].stu_list[v].stu_course.size(); u++) {
								if (now_teacher.tea_course[k].stu_list[v].stu_course[u].NO== now_teacher.tea_course[k].NO 
									&& now_teacher.tea_course[k].stu_list[v].stu_course[u].grade == -1) {
									putin_done++;
								}
							}
						}
						if (putin_done == 0) {//本全部学生成绩均已录入
							logon_student_grade(now_teacher.tea_course[k]);//提交本课程学生成绩
							pp = 1;
						}
						else {
							closesocket(sClient);
							sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
							const char * sendData = "本课程还有学生成绩未录入，请检查后再提交\n";
							send(sClient, sendData, strlen(sendData), 0);
							//cout << "本课程还有学生成绩未录入，请检查后再提交" << endl;
							pp = 1;
						}
						//logon_student_grade(now_teacher.tea_course[k]);//提交本课程学生成绩
						//pp = 1;
					}
					else {
						closesocket(sClient);
						sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
						const char * sendData = "--成绩操作类型序号选择有误，请重新输入：";
						send(sClient, sendData, strlen(sendData), 0);
						//cout << "成绩操作类型序号选择有误，请重新输入：";
					}
						
				}
				else if (now_teacher.tea_course[k].putin_key == 1) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "成绩已经提交，无法再进行操作\n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "成绩已经提交，无法再进行操作" << endl;
					pp = 1;
				}
				else if (now_teacher.tea_course[k].stu_list.size() == 0) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "课程中没有学生信息，无法操作成绩\n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "课程中没有学生信息，无法操作成绩" << endl;
					pp = 1;
				}
			}
		}

		if (ssg == 0) {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "你不能操作此课程成绩！\n";
			send(sClient, sendData, strlen(sendData), 0);

			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData2 = "--1 for 重新输入课程编码，else for退出此操作:";
			send(sClient, sendData2, strlen(sendData2), 0);
			//cout << "你不能操作此课程成绩！" << endl;
			//cout << "1 for 重新输入课程编码，else for退出此操作:";
			int ooper;
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				//printf(revData);
			}
			ooper = int(revData[0] - '0');
			//cin >> ooper;
			if (ooper == 1) {
				cout << "--请输入想要进行操作的课程编码：";
				//int kk;
				int ret = recv(sClient, revData, 255, 0);
				if (ret > 0)
				{
					revData[ret] = 0x00;
					//printf(revData);
				}
				a = int(revData - '0');
				//cin >> a;

				pp = 0;
			}
			else if (ooper != 1) {
				pp = 1;
			}
		}
	}
}

//查看所有课程
void Teacher::show_all_course()
{
	int k;

	Course zancun1;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "   必修课程：\n";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "   必修课程：" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 1) {
			zancun1 = course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData2 = "   选修课程：\n";
	send(sClient, sendData2, strlen(sendData2), 0);
	//cout << "   选修课程：" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 2) {
			zancun2 = course[k];
			print_course_list2(zancun2);
		}
	}
}
//显示自己的所有课程
void Teacher::show_teacher_course()
{
	Course zancun1;

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "   必修课程：\n";
	send(sClient, sendData, strlen(sendData), 0);
    //cout << "   必修课程：" << endl;

	for (int k = 0; k < (now_teacher.tea_course).size(); k++) {
		if (now_teacher.tea_course[k].kind == 1) {
			zancun1 = now_teacher.tea_course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData3 = "   选修课程：\n";
	send(sClient, sendData3, strlen(sendData3), 0);
	//cout << "   选修课程：" << endl;
	for (int k = 0; k < (now_teacher.tea_course).size(); k++) {
		if (now_teacher.tea_course[k].kind == 2) {
			zancun2 = now_teacher.tea_course[k];
			print_course_list2(zancun2);
		}
	}

}

//某课程学生名单排序输出
bool num_increase(const Student &v1, const Student &v2) {
	return (v1.stu_num < v2.stu_num);
}
bool num_decrease(const Student &v1, const Student &v2) {
	return (v1.stu_num > v2.stu_num);
}
bool grade_increase(const Student &v1, const Student &v2) {
	int x1, x2;
	for (x1 = 0; x1 < v1.stu_course.size(); x1++) {
		if (v1.stu_course[x1].NO == NUM) break;
	}
	for (x2 = 0; x2 < v2.stu_course.size(); x2++) {
		if (v2.stu_course[x2].NO == NUM) break;
	}

	return (v1.stu_course[x1].grade < v2.stu_course[x2].grade);
}
bool grade_decrease(const Student &v1, const Student &v2) {
	int x1, x2;
	for (x1 = 0; x1 < v1.stu_course.size(); x1++) {
		if (v1.stu_course[x1].NO == NUM) break;
	}
	for (x2 = 0; x2 < v2.stu_course.size(); x2++) {
		if (v2.stu_course[x2].NO == NUM) break;
	}

	return (v1.stu_course[x1].grade > v2.stu_course[x2].grade);
}

//查看指定选课学生信息,nnum为课程编号
void Teacher::show_specify_student_information(int nnum)
{
	NUM = nnum;
	Student zancun;
	int i,j;
	for (i = 0; i < now_teacher.tea_course.size(); i++) {
		if (now_teacher.tea_course[i].NO == nnum) {//找到指定课程
			if (now_teacher.tea_course[i].stu_list.size() == 0) {

				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData2 = "本课程暂时没有学生信息";
				send(sClient, sendData2, strlen(sendData2), 0);

				//cout << "本课程暂时没有学生信息" << endl;
			}
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData2 = "--请选择学生信息呈现方式： 1for按学号升序；2for按学号降序；3for按成绩升序；4for按成绩降序\n";
			send(sClient, sendData2, strlen(sendData2), 0);
			//cout << "请选择学生信息呈现方式：";
			//cout << "1for按学号升序；2for按学号降序；3for按成绩升序；4for按成绩降序" << endl;
			
			string a;
			//接收数据  
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				//printf(revData);
			}
			a=revData[0];
			
			if (a == "1") {//1for按学号升序
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), num_increase);
			}
			else if (a == "2") {//2for按学号降序
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), num_decrease);
			}
			else if (a == "3") {//3for按成绩升序
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), grade_increase);			
			}
			else if (a == "4") {//4for按成绩降序
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), grade_decrease);	
			}
			else {
				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData2 = "输入不正确，按默认方式呈现\n";
				send(sClient, sendData2, strlen(sendData2), 0);
				//cout << "输入不正确，按默认方式呈现" << endl;
				break;
			}
			vector<string>ssend;
			for (j = 0; j < now_teacher.tea_course[i].stu_list.size(); j++) {//输出所有本课程学生信息
				zancun = now_teacher.tea_course[i].stu_list[j];

				ssend.push_back("姓名：");
				ssend.push_back(zancun.stu_name);
				ssend.push_back("\n");

				ssend.push_back("学院：");
				ssend.push_back(zancun.stu_college);
				ssend.push_back("\n");

				ssend.push_back("班级：");
				ssend.push_back(zancun.stu_class);
				ssend.push_back("\n");

				ssend.push_back("学号：");
				ssend.push_back(zancun.stu_num);
				ssend.push_back("\n");

				ssend.push_back("成绩：");

				//cout << "姓名：" << zancun.stu_name << endl;
				//cout << "学院：" << zancun.stu_college << endl;
				//cout << "班级：" << zancun.stu_class << endl;
				//cout << "学号：" << zancun.stu_num << endl;
				//cout << "成绩：";

				double jidian=0;
				int tijiao=0;
				
				int k;
				for (k = 0; k < zancun.stu_course.size(); k++) {
					if (zancun.stu_course[k].NO == nnum) {
						tijiao = zancun.stu_course[k].putin_key;
						if (zancun.stu_course[k].grade>0) {
							stringstream aa;
							aa << zancun.stu_course[k].grade;
							ssend.push_back(aa.str());
							ssend.push_back("\n");
							aa.str("");
							//cout << zancun.stu_course[k].grade << endl;
						}
						else {
							ssend.push_back("成绩未录入\n");
							//ssend.push_back("");
							//cout << "成绩未录入" << endl;
						}
							

						if (tijiao == 1) {
							jidian = zancun.stu_course[k].grade_point;
						}
					}
				}
				ssend.push_back("成绩是否提交：");
				//cout << "成绩是否提交：";
				if (tijiao == 1) {
					ssend.push_back("已提交\n");
					//ssend.push_back("");
					//cout << "已提交" << endl;
				}
				else if (tijiao == 0) {
					ssend.push_back("未提交\n");
					//ssend.push_back("");
					//cout << "未提交" << endl;
				}
				ssend.push_back("===================\n");
				//ssend.push_back("\n");
				//cout << "===================" << endl;
			}
			stringstream ss;
			for (int i = 0; i < ssend.size(); i++) {
				ss << ssend[i];
			}
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const string& sendDataa = ss.str();
			const char * sendData = sendDataa.c_str();

			//sendData << (ss.str()).c_str();
			send(sClient, sendData, strlen(sendData), 0);
			ss.clear();
			ssend.clear();
		}
	}
}

//显示自己课程的所有选课学生名单
void Teacher::show_course_studentlist()
{
	Student zancun;
	int i,j;
	
	int nnnum=0;

	vector<string>ssend;
	stringstream k;

	for (i = 0; i < (now_teacher.tea_course).size(); i++) {
		ssend.push_back("课程：");
		k << now_teacher.tea_course[i].NO;
		ssend.push_back(k.str());
		k.str("");
		ssend.push_back(now_teacher.tea_course[i].couname);
		ssend.push_back("\n");

		//cout << "课程：" << now_teacher.tea_course[i].NO<<"-" << now_teacher.tea_course[i].couname << endl;
		for (j = 0; j < (now_teacher.tea_course[i].stu_list).size(); j++) {
			nnnum++;
			zancun = now_teacher.tea_course[i].stu_list[j];

			//cout << "课程：" << now_teacher.tea_course[i].couname <<"    ";
			ssend.push_back("      学号：");
			ssend.push_back(zancun.stu_num);
			ssend.push_back("          ");
			//ssend.push_back("setw(8)");
			ssend.push_back("姓名：");
			ssend.push_back(zancun.stu_name);
			ssend.push_back("\n");

			//cout << "      学号：" << zancun.stu_num << std::right << setw(8) << "姓名：" << zancun.stu_name << endl;
			//cout << "学院：" << zancun.stu_college << endl;
			//cout << "班级：" << zancun.stu_class << endl;
		}
	}


	if (nnnum == 0) {
		ssend.push_back("您的课程中还没有学生\n");

		stringstream ss;
		for (int i = 0; i < ssend.size(); i++) {
			ss << ssend[i];
		}
		//ss >> sendData;

		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const string& sendDataa = ss.str();
		const char * sendData = sendDataa.c_str();

		//sendData << (ss.str()).c_str();
		send(sClient, sendData, strlen(sendData), 0);
		ss.clear();
		ssend.clear();
		//cout << "您的课程中还没有学生" << endl;
	}
	else if (nnnum != 0) {
		ssend.push_back("是否想查询指定选课详细学生信息\n");
		stringstream ss;
		for (int i = 0; i < ssend.size(); i++) {
			ss << ssend[i];
		}
		//ss >> sendData;

		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const string& sendDataa = ss.str();
		const char * sendData = sendDataa.c_str();

		//sendData << (ss.str()).c_str();
		send(sClient, sendData, strlen(sendData), 0);

		int a = 0;
		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const char * sendData2 = "--1 for 是 ；else for 退出：";
		send(sClient, sendData2, strlen(sendData2), 0);
		//cout << "1 for 是 ；else for 退出：";
		//接收数据  
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			//printf(revData);
		}
		//cin >> a;
		if (revData[0] == '1') {
			//int m;
			int nn = 0;

			while (nn == 0) {
				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData3 = "--请输想要查询的课程编号：";
				send(sClient, sendData3, strlen(sendData3), 0);

				int ret = recv(sClient, revData, 255, 0);
				if (ret > 0)
				{
					revData[ret] = 0x00;
					//printf(revData);
				}
				int nnum = int(revData[0]-'0');
				//cin >> nnum;

				for (int m = 0; m <(now_teacher.tea_course).size(); m++) {
					if (now_teacher.tea_course[m].NO == nnum) {
						show_specify_student_information(nnum); //显示指定选课学生信息
						nn = 1;
						break;
					}
				}
				if (nn == 0) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData4 = "课程编号错误，请重新输入\n";
					send(sClient, sendData4, strlen(sendData4), 0);
					//cout << "课程编号错误，请重新输入," << endl;
				}
			}
		}
		ss.clear();
		ssend.clear();
	}
	
}

//课程查看部分
void Teacher::for_course_show()
{
	int signal = 0;
	int i;

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--请选择要进行的操作：1.查看所有课程 2.查看自己教授的课程 3.查看所有选课学生名单\n";
	send(sClient, sendData, strlen(sendData), 0);
	//接收数据  
	int ret = recv(sClient, revData, 255, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
		//printf(revData);
	}
	//cin >> i;
	while (!signal) {
		if (revData[0] == '1') {
			show_all_course();//查看所有课程	
			signal = 1;
		}
		else if (revData[0] == '2') {
			show_teacher_course();//显示自己的所有课程
			signal = 1;
		}
		else if (revData[0] == '3') {
			show_course_studentlist();//显示自己课程的所有选课学生名单
			signal = 1;
		}
		else {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "请输入正确序号\n";
			send(sClient, sendData, strlen(sendData), 0);
		}
	}
}

//教师操作选择
void Teacher::show_teacher_choice()
{

	int signal = 0;//标识符
	while (!signal) {

		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const char * sendData = "--请选择将要进行的操作：1.课程查看 2.成绩操作 3.注销登录\n";
		send(sClient, sendData, strlen(sendData), 0);

		//cout << "请选择将要进行的操作：1.课程查看 2.成绩操作 3.注销登录" << endl;
		//int i;
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			//printf(revData);
		}
		//i = revData[0];

		if (revData[0] == '1') {
			for_course_show();//课程查看部分
		}
		else if (revData[0] == '2') {
			for_course_set();//成绩操作部分
		}
		else if (revData[0] == '3') {

			teacher_information(now_teacher);

			for (int i = 0; i < teacher.size(); i++) {
				if (teacher[i].tea_num == now_teacher.tea_num) {
					teacher[i] = now_teacher;
				}
			}

			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "||您已注销登录||\n";
			send(sClient, sendData, strlen(sendData), 0);

			//cout << "||您已注销登录||" << endl;
			signal = 1;
		}
		else {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "请输入正确序号\n";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "请输入正确序号" << endl;
		}

	}
}

//教师注册
void Teacher::teacher_register(string a)
{
	Teacher zancun;
	int stusize = (student).size();
	int signal = 0;//注册成功标识符

	cout << "|对不起，该用户信息不存在|" << endl;
	cout << "  |是否要注册用户信息？|" << endl;
	cout << "     1.注册 2.退出" << endl;
	int choose;
	int b,i;
	cin >> choose;
	while (!signal) {
		if (choose == 1) {
			zancun.tea_num = a;//教师工号
			//strcpy_s(((string)zancun.stu_num).c_str(),a.size(), a.c_str());
			cout << "请输入教师师姓名：";
			cin >> zancun.tea_name;
			cout << "请输入教师学院：";
			cin >> zancun.tea_collage;


			cout << "请输入教师所授课程编号：";
			int mm=0;
			while (mm == 0) {		
				cin >> b;
				for (i = 0; i < course.size(); i++) {
					if (b == course[i].NO ) {
						if (course[i].teacher_num == "-1") {//找到此课程且此课程还无人教授
							zancun.tea_course.push_back(course[i]);//加入课程
							course[i].teacher_num = zancun.tea_num;//将教师信息添加到课程信息中


																   //mm = 1;
							break;
						}
						else if (course[i].teacher_num != "-1") {//找到此课程但有人教授此课程
							cout << "你不能添加此课程" << endl;
							break;
						}					
					}
				}

				cout << "是否继续添加教授的课程，1 for 继续，else for 停止：";
				int sigg;
				cin >> sigg;
				if (sigg == 1) {
					cout << "请输入课程编号：" ;
				}
				else {
					mm = 1;
					break;
				}
			}
			teacher.push_back(zancun);
			now_teacher = zancun;
			signal = 1;

			teacher_information(zancun);
			show_teacher_choice();//显示教师可以进行的功能选择
		}
		else if (choose == 2) {
			//cout << "                ||您已退出学生成绩管理系统||" << endl;
			//exit(0);
			break;
			break;
		}
		else cout << "请输入正确序号" << endl;
	}
	//teacher_information(zancun);
}

//教师登录
void Teacher::teacher_login()
{
	string a;
	int teasize = teacher.size();

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--您已选择了教师身份，请输入工号：";
	send(sClient, sendData, strlen(sendData), 0);

	//cout << "您已选择了教师身份，请输入工号：";

	//cin >> a;
	int ret = recv(sClient, revData, 255, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
		//printf(revData);
	}
	a = revData;
	Teacher zancun;

	//初始情况，内部无信息
	if (teasize == 0) {
		teacher_register(a);//老师注册	
	}

	//内部有教师信息
	else if (teasize > 0) {
		int i;

		int sig = 0;

		for (i = 0; i < teacher.size(); i++) {
			if (teacher[i].tea_num == a) {
				now_teacher = teacher[i];//拷贝
				sig = 1;

				teacher_information(now_teacher);//显示教师信息
				show_teacher_choice();//显示教师可以进行的功能选择
			}
		}
		if (sig == 0) {//未查找到该序号
			teacher_register(a);//教师注册
		}
	}
}

void initial_teacherlist()
{
	Teacher zancun;
	cout << endl<<"**内置教师信息如下：" << endl;
	cout << "======================================" << endl;
	for (int i = 0; i < teacher.size(); i++) {
		zancun = teacher[i];
		cout << "教师工号：" << zancun.tea_num << endl;
		cout << "教师姓名：" << zancun.tea_name << endl;
		cout << "教师学院：" << zancun.tea_collage << endl;
		cout << "教师课程：" ;

		for (int i = 0; i < zancun.tea_course.size(); i++) {
			cout << zancun.tea_course[i].NO << "-" << zancun.tea_course[i].couname << "  ";
		}
		cout <<endl<< "======================================" << endl;

	}

}

istream & operator >> (istream &in, Teacher &c) 
{
	
	try {
        string  s;
	    int jishu = 1;
		while (in >> s) {
			//stringstream ss(s);
			if (jishu % 3 == 1) {
				c.tea_num = s;
				jishu++;
			}
			else if (jishu % 3 == 2) {
				c.tea_name = s;
				jishu++;
			}
			else if (jishu % 3 == 0) {
				c.tea_collage = s;
				jishu++;

				for (int i = 0; i < course.size(); i++) {
					if (course[i].teacher_num == c.tea_num) {
						c.tea_course.push_back(course[i]);
					}
				}
				teacher.push_back(c);
				c.tea_course.clear();
			}

		}
		
		int find = 0;
		for (int j = 0; j < teacher.size(); j++) {
			for (int i = 0; i < course.size(); i++) {
				if (teacher[j].tea_num == course[i].teacher_num) {
					find++;
				}
			}			
		}

		if ((jishu % 3 != 1)||( find != course.size())) {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "读取文件内容有误！\n";
			send(sClient, sendData, strlen(sendData), 0);

			throw"教师信息文件内容有误！";
		}
	}
	catch (char *msg) {
		cout << "错误！" << msg << endl;
		system("pause");
		exit(0);
	}
	return in;
}


ostream& operator << (ostream &out, const Teacher &c)
{
	for (int i = 0; i < teacher.size(); i++) {
		out << teacher[i].tea_num << " ";
		out << teacher[i].tea_name << " ";
		out << teacher[i].tea_collage <<  endl;
	}
	return out;
}

void teacher_save()
{
	ofstream out("C://Users//11794//Desktop//学生成绩管理系统//学生成绩管理系统（3//学生成绩管理系统//学生成绩管理系统//teacher_information.txt");//打开文件
	Teacher c1;
	out << c1;

	out.close();
}

void initial_teacher()
{
	ifstream in("C://Users//11794//Desktop//学生成绩管理系统//学生成绩管理系统（3//学生成绩管理系统//学生成绩管理系统//teacher_information.txt");//打开文件
	Teacher c1;
	in >> c1;

	initial_teacherlist();

	in.close();
}