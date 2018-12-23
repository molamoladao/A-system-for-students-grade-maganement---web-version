#ifndef _STUDENT_H_
#define _STUDENT_H_

#include"main.h"
class Course;
using namespace std;
class Student
{
public:
	Student() {
		vector<Course>stu_grade;//ѧ���ɼ���Ϣ����
		string stu_num;//��¼ѧ��ѧ��
		string stu_name;//��¼ѧ������
		string stu_college;//��¼ѧ��ѧԺ
		string stu_class;//��¼ѧ���༶ 
		vector<Course>stu_course;//��¼ѧ���Լ��Ŀγ�
		vector<Course>can_course_list;//�洢��ѡ�γ�
	}
	~Student() {

	}
	void student_register(string a);//ѧ��ע��
	void student_login();//ѧ����¼
	void student_information(Student zancun);//��ʾѧ����Ϣ

	void show_student_choice();//��ʾѧ�����Խ��еĹ���ѡ��
	//void choice(int choice2);//��ѧ����ѡ�������Ӧ����

	void for_course_choose();//ѡ�β���
	void show_allcan_course();//�鿴���п�ѡ�γ�
	void course_choose();//ѡ��
	void show_student_course();//�鿴��ѡ�γ�
	void course_delete();//ɾ���γ�

	void for_course_show();//�鿴�γ̲���
	void show_all_course();//�鿴���пγ�
	void show_own_course();//�鿴�Լ��Ŀγ�

	void show_student_grade();//��ѯѧ���ɼ�

//private:
	vector<Course>stu_grade;//ѧ���ɼ���Ϣ����
	string stu_num;//��¼ѧ��ѧ��
	string stu_name ;//��¼ѧ������
	string stu_college ;//��¼ѧ��ѧԺ
	string stu_class ;//��¼ѧ���༶ 

	vector<Course>stu_course;//��¼ѧ���Լ��Ŀγ�
	vector<Course>can_course_list;//�洢��ѡ�γ�
	friend ostream & operator << (ostream &out, const Student &c);
	friend istream & operator >> (istream &in, Student &c);
};

void initial_student();
void student_save();
#endif
