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

	void teacher_register(string a);//��ʦע��
	void teacher_login();//��ʦ��¼
	void teacher_information(Teacher zancun);//��ʾ��ʦ��Ϣ

	void show_teacher_choice();//��ʾ��ʦ���Խ��еĹ���ѡ��
	//void choice(int choice1);//�Խ�ʦ��ѡ�������Ӧ���� 

	void for_course_show();//�γ̲鿴����
	void show_all_course();//�鿴���пγ� �����ֱ��ޣ�ѡ��
	void show_teacher_course();//��ʾ�Լ������пγ̣����ֱ��ޣ�ѡ��
	void show_course_studentlist();//��ʾ�γ̵�����ѡ��ѧ������ 
	void show_specify_student_information(int nnum);//��ʾָ��ѡ��ѧ����Ϣ�������ɼ� 

	void for_course_set();//�ɼ���������
	void set_student_grade(Student zancun, Course zancun2);//¼��ѧ���ɼ�
	void reset_student_grade(Student zancun, Course zancun2);//�޸�ѧ���ɼ�
	void logon_student_grade(Course zancun2);//�ύѧ���ɼ�

//private:
	
	//vector<get_grade>gather;//ѧ���ɼ��洢����
	//int student_count;//��¼ѧ������ 
	//int teacher_count;//��¼��ʦ���� 
	string tea_num;//��¼��ʦ���� 
	string tea_name;//��¼��ʦ����
	string tea_collage;//��¼��ʦѧԺ 
	vector<Course>tea_course;//��¼��ʦ�Լ��Ŀγ�

	friend ostream & operator << (ostream &out, const Teacher &c);
	friend istream & operator >> (istream &in, Teacher &c);
};
void initial_teacher();
void teacher_save();
#endif