#ifndef _COURSE_H_
#define _COURSE_H_
//#include<cstring>
//#include<string>
//#include<vector>
#include"main.h"
class Student;
using namespace std;

class Course{//�Ƕ�̬����
public:
	Course() {
		
	}
	~Course() {

	}
	
	int kind;//�γ���������---1for���ޣ�2forѡ��
	int NO;//�γ̱�� 
	int point;//ѧ�� 
	string couname ;//�γ�����
	string teacher_num = "-1";//���γ̽�ʦ����

	int putin_key = 0;//���γ̳ɼ��Ƿ��ύ���ж��ź�
	int grade = -1;//�ɼ�
	double grade_point = -1;//����

	vector<Student>stu_list;//���γ�ѧ���������ɼ���Ϣ


	virtual double find_garde(Course a,int sum) const {
		return -1;
	}//������� 

	

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);
};

class Bixiu :public Course{//��̬����
public:
	
	virtual double find_garde(Course a,int sum) const {//�������
		a.grade_point =((double)a.grade/ sum)*a.point;
		return a.grade_point;
	} 

	int kind;//�γ���������---1for���ޣ�2forѡ��
	int NO;//�γ̱�� 
	int point;//ѧ�� 
	string couname;//�γ�����

	int grade = -1;//�ɼ�
	double grade_point = -1;//����

	int putin_key = 0;//���γ̳ɼ��Ƿ��ύ���ж��ź�

	string teacher_num= "-1";//���γ̽�ʦ����
	vector<Student>stu_list;//���γ�ѧ���������ɼ���Ϣ

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);
};

class Xuanxiu :public Course{//��̬����
public:

	int kind;//�γ���������---1for���ޣ�2forѡ��
	int NO;//�γ̱�� 
	int point;//ѧ�� 
	string couname;//�γ�����

	int grade = -1;//�ɼ�
	double grade_point = -1;//����

	int putin_key = 0;//���γ̳ɼ��Ƿ��ύ���ж��ź�

	string teacher_num="-1";//���γ̽�ʦ����
	vector<Student>stu_list;//���γ�ѧ���������ɼ���Ϣ

	virtual double find_garde(Course a,int sum) const {//������� 
		a.grade_point = (double)((sqrt(a.grade) / 10)*(a.point));
		return a.grade_point;
	}

	friend ostream & operator << (ostream &out, const Course &c);
	friend istream & operator >> (istream &in, Course &c);

};

int coursemain();
void course_save();

#endif