#pragma once
#include"main.h"
#include"teacher.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<cstring>
#include<algorithm>

using namespace std;
Teacher now_teacher;
class Course;

int NUM = 0;

void Teacher::teacher_information(Teacher zancun)
{
	cout << "��ʦ������" << zancun.tea_name << endl;
	cout << "��ʦѧԺ��" << zancun.tea_collage << endl;
	cout << "��ʦ���ţ�" << zancun.tea_num << endl;
	if ((zancun.tea_course).size() == 0) {
		cout << "���ڿγ̣�[����ʦ�޽��ڵĿγ�]" << endl;
	}
	else if ((zancun.tea_course).size() > 0) {
		cout << "���ڿγ̣�";
		for (int i = 0; i < (zancun.tea_course).size(); i++) {
			cout << zancun.tea_course[i].NO << "-" << zancun.tea_course[i].couname << "  ";
		}
		cout << endl;
	}
	cout << "===================" << endl;

}

//��ӡ�γ���Ϣ
void print_course_list2(Course  zancun)
{
	cout << "�γ̱�ţ�" << zancun.NO << endl;
	cout << "�γ����ƣ�" << zancun.couname << endl;
	cout << "�γ����ͣ�" << zancun.kind << endl;
	cout << "�γ�ѧ�֣�" << zancun.point << endl;
	cout << "===================" << endl;
}
//¼��ָ��ѡ�ε�ָ��ѧ���ɼ�
void Teacher::set_student_grade(Student zancun, Course zancun2)
{
	int ggrade;
	//cout << "������ɼ�[��Χ��0-100]��";

	int i, j, k;
	//int cc = 0;
	while (1) {

		cout << "������ɼ�[��Χ��0-100]��";
		cin >> ggrade;
		if (ggrade >= 0 && ggrade <= 100) {//�ɼ���Χ����Ҫ��
			//ѧ�������
			for (int mm = 0; mm < student.size(); mm++) {
				for (int nn = 0; nn < student[mm].stu_course.size(); nn++) {
					if (student[mm].stu_num == zancun.stu_num && student[mm].stu_course[nn].NO == zancun2.NO) {
						student[mm].stu_course[nn].grade = ggrade;
					}
				}				
			}
			//��ʦ�����
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


			cout << "�ɼ���¼�ɹ���" << endl;
			break;

		}
		else if (ggrade < 0 || ggrade>100) {
			cout << "���벻���Ϲ淶��������¼��ɼ�[�ɼ���Χ��0-100]��";
		}

	}

}

//�޸�ָ��ѡ�ε�ָ��ѧ���ɼ�
void Teacher::reset_student_grade(Student zancun, Course zancun2)
{

	int ggrade;
	//cout << "������ɼ�[��Χ��0-100]��";

	int i, j, k;
	//int cc = 0;
	while (1) {

		cout << "������ɼ�[��Χ��0-100]��";
		cin >> ggrade;
		if (ggrade >= 0 && ggrade <= 100) {//�ɼ���Χ����Ҫ��
			//ѧ�������
			for (int mm = 0; mm < student.size(); mm++) {
				if (student[mm].stu_num == zancun.stu_num) {//�ҵ�ĳѧ��
					for (int nn = 0; nn < student[mm].stu_course.size(); nn++) {
						if (student[mm].stu_course[nn].NO == zancun2.NO) {//�ҵ�ĳѧ����ĳ�γ�
							student[mm].stu_course[nn].grade = ggrade;
						}
					}
				}
			}

			//��ʦѧ��������Ϣ����
			for (int ii = 0; ii < now_teacher.tea_course.size(); ii++) {
				if (now_teacher.tea_course[ii].NO == zancun2.NO) {//�ҵ�ĳ��ʦ��ĳ�γ�
					for (int jj = 0; jj < now_teacher.tea_course[ii].stu_list.size(); jj++) {
						if (now_teacher.tea_course[ii].stu_list[jj].stu_num == zancun.stu_num) {//�ҵ��˿γ��е�ĳѧ��
							for (int kk = 0; kk < now_teacher.tea_course[ii].stu_list[jj].stu_course.size(); kk++) {
								if (now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].NO == zancun2.NO) {//�ҵ����ѧ����ָ���γ�
									now_teacher.tea_course[ii].stu_list[jj].stu_course[kk].grade = ggrade;
								}
							}
						}
					}
				}
				
			}
			//========================================================================

			//��ʦ��Ϣ�޸�
			for (int i = 0; i < now_teacher.tea_course.size(); i++) {
				if (now_teacher.tea_course[i].NO == zancun2.NO) {
					now_teacher.tea_course[i].grade = ggrade;
				}
			}
			
			//===========================================================================

			cout << "�ɼ��޸ĳɹ���" << endl;
			break;

		}
		else if (ggrade < 0 || ggrade>100) {
			cout << "���벻���Ϲ淶�������������³ɼ�[�ɼ���Χ��0-100]��";
		}

	}

}

/*void Xuanxiu ::find_garde(Course*a) const {//�������
	a->grade_point = (sqrt(a->grade) / 10)*(a->point);
}*/



//�ύ���γ�ѧ���ɼ�
void Teacher::logon_student_grade(Course  zancun2)
{
	Course *a = new Bixiu();
	Course *b = new Xuanxiu();

	//��ӡ�γ���Ϣ
	//print_course_list2(zancun2);
	
	int x,y;
	double u;
	Course ssave;
	for (x = 0; x < zancun2.stu_list.size(); x++) {//��ʦ->�γ�->ѧ���б�
		for (int y = 0; y < zancun2.stu_list[x].stu_course.size(); y++) {//��ʦ->�γ�->ѧ���б�->����ѧ���Ŀγ��б�
			if (zancun2.stu_list[x].stu_course[y].NO == zancun2.NO) {//��ʦ->�γ�->ѧ���б�->����ѧ���Ŀγ��б�->ĳ�γ���ŵ��ڴ���Ŀγ����
				ssave = zancun2.stu_list[x].stu_course[y];
				ssave.stu_list = zancun2.stu_list;

				int sum = 0;//���γ�ѧ���ɼ�������
				for (int i=0; i < zancun2.stu_list.size(); i++) {
					for (int j=0; j < zancun2.stu_list[i].stu_course.size(); j++) {
						if (zancun2.stu_list[i].stu_course[j].NO == zancun2.NO) {
							sum = sum + zancun2.stu_list[i].stu_course[j].grade;
						}
					}
				}

				//print_course_list2(ssave);
				//int g = ssave.stu_list.size();
				//cout << "ѧ��������" << g << endl;
				//double u;

				if (zancun2.kind == 1) {
					u = a->find_garde(ssave,sum);
				}
				else if (zancun2.kind == 2) {
					u = b->find_garde(ssave,sum);
				}

				ssave.putin_key = 1;
				ssave.grade_point = u;

				//cout << "���㣺"<<u << endl;
				//cout << "���㣺" << ssave.grade_point << endl;

				//�γ���Ϣ�޸�
				for (int i = 0; i < course.size(); i++) {
					if (course[i].NO == zancun2.NO) {
						course[i].putin_key = 1;
					}
				}

				//��ʦ��Ϣ�޸�
				/*for (int i = 0; i < now_teacher.tea_course.size(); i++) {

					if (now_teacher.tea_course[i].NO == ssave.NO) {
						//now_teacher.tea_course[i] = ssave;
						now_teacher.tea_course[i].grade_point = ssave.grade_point;
						now_teacher.tea_course[i].putin_key = ssave.putin_key;
					}
				}*/

				//��ʦѧ��������Ϣ�޸�
				for (int i = 0; i < now_teacher.tea_course.size(); i++) {
					if (now_teacher.tea_course[i].NO == zancun2.NO) {//�Խ�ʦ��ָ���γ̲���
						for (int j = 0; j < now_teacher.tea_course[i].stu_list.size(); j++) {
							if (now_teacher.tea_course[i].stu_list[j].stu_num == zancun2.stu_list[x].stu_num) {//ָ���γ̵�ָ��ѧ��
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

				//ѧ����Ϣ�޸�
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
	cout << "�ɼ��ύ�ɹ�" << endl;
}

//�ɼ���������
void Teacher::for_course_set()
{
	//Course  zancun2;
	cout << "��������Ҫ���в����Ŀγ̱��룺";
	int a,b,k;
	b = 0;
	cin >> a;
	int pp = 0;
	int ssg = 0;
	
	while (pp == 0) {
		//cout << "��������Ҫ���в����Ŀγ̱��룺";
		for (k = 0; k < (now_teacher.tea_course).size(); k++) {
			if (now_teacher.tea_course[k].NO == a) {//�ҵ��γ�
				ssg = 1;
				//Course  zancun2;
				//zancun2 = now_teacher.tea_course[k];

				if (now_teacher.tea_course[k].putin_key == 0 && now_teacher.tea_course[k].stu_list.size()>0) {//�ɼ�δ�ύ
					cout << "��ѡ��ɼ��������ͣ�1 for �ɼ�¼�롢�޸�;2 for �ɼ��ύ " << endl;
					cin >> b;
					if (b == 1) {
						cout << "��ѡ����Ҫ���гɼ�������ѧ��(ѧ��):";
						string stunnum;
						cin >> stunnum;
						int q;
						int found = 0;//�Ƿ��ڱ��γ����ҵ���ѧ��
						for (q = 0; q < (now_teacher.tea_course[k].stu_list).size(); q++) {
							if (now_teacher.tea_course[k].stu_list[q].stu_num == stunnum) {
								found = 1;
								pp = 1;
								cout << "��ѡ�������1 for �ɼ�¼�룻2 for �ɼ��޸�" << endl;
								int qq = 0;
								while (qq == 0) {
									//Student zancun;
									//zancun = now_teacher.tea_course[k].stu_list[q];
									int c = 0;
									cin >> c;
									if (c == 1) {
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//¼��ѧ���ɼ�
										qq = 1;
									}
									else if (c == 2) {
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//�޸�ѧ���ɼ�
										qq = 1;
									}
									else cout << "����ѡ���������������룺";
								}

							}
						}
						if (found == 0) {
							cout << "��ѧ��δѡ��˿γ�" << endl;
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
						if (putin_done == 0) {//��ȫ��ѧ���ɼ�����¼��
							logon_student_grade(now_teacher.tea_course[k]);//�ύ���γ�ѧ���ɼ�
							pp = 1;
						}
						else {
							cout << "���γ̻���ѧ���ɼ�δ¼�룬��������ύ" << endl;
							pp = 1;
						}
						//logon_student_grade(now_teacher.tea_course[k]);//�ύ���γ�ѧ���ɼ�
						//pp = 1;
					}
					else cout << "�ɼ������������ѡ���������������룺";
				}
				else if (now_teacher.tea_course[k].putin_key == 1) {
					cout << "�ɼ��Ѿ��ύ���޷��ٽ��в���" << endl;
					pp = 1;
				}
				else if (now_teacher.tea_course[k].stu_list.size() == 0) {
					cout << "�γ���û��ѧ����Ϣ���޷������ɼ�" << endl;
					pp = 1;
				}
			}
		}

		if (ssg == 0) {
			cout << "�㲻�ܲ����˿γ̳ɼ���" << endl;
			cout << "1 for ��������γ̱��룬else for�˳��˲���:";
			int ooper;
			cin >> ooper;
			if (ooper == 1) {
				cout << "��������Ҫ���в����Ŀγ̱��룺";
				//int kk;
				cin >> a;

				pp = 0;
			}
			else if (ooper != 1) {
				pp = 1;
			}
		}
	}
}

//�鿴���пγ�
void Teacher::show_all_course()
{
	int k;

	Course zancun1;
	cout << "   ���޿γ̣�" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 1) {
			zancun1 = course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	cout << "   ѡ�޿γ̣�" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 2) {
			zancun2 = course[k];
			print_course_list2(zancun2);
		}
	}
}
//��ʾ�Լ������пγ�
void Teacher::show_teacher_course()
{
	Course zancun1;
	cout << "   ���޿γ̣�" << endl;
	for (int k = 0; k < (now_teacher.tea_course).size(); k++) {
		if (now_teacher.tea_course[k].kind == 1) {
			zancun1 = now_teacher.tea_course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	cout << "   ѡ�޿γ̣�" << endl;
	for (int k = 0; k < (now_teacher.tea_course).size(); k++) {
		if (now_teacher.tea_course[k].kind == 2) {
			zancun2 = now_teacher.tea_course[k];
			print_course_list2(zancun2);
		}
	}

}

//ĳ�γ�ѧ�������������
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

//�鿴ָ��ѡ��ѧ����Ϣ,nnumΪ�γ̱��
void Teacher::show_specify_student_information(int nnum)
{
	NUM = nnum;
	Student zancun;
	int i,j;
	for (i = 0; i < now_teacher.tea_course.size(); i++) {
		if (now_teacher.tea_course[i].NO == nnum) {//�ҵ�ָ���γ�
			if (now_teacher.tea_course[i].stu_list.size() == 0) {
				cout << "���γ���ʱû��ѧ����Ϣ" << endl;
			}
			cout << "��ѡ��ѧ����Ϣ���ַ�ʽ��";
			cout << "1for��ѧ������2for��ѧ�Ž���3for���ɼ�����4for���ɼ�����" << endl;
			
			string a;
			cin >> a;
			
			if (a == "1") {//1for��ѧ������
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), num_increase);
			}
			else if (a == "2") {//2for��ѧ�Ž���
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), num_decrease);
			}
			else if (a == "3") {//3for���ɼ�����
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), grade_increase);			
			}
			else if (a == "4") {//4for���ɼ�����
				sort(now_teacher.tea_course[i].stu_list.begin(), now_teacher.tea_course[i].stu_list.end(), grade_decrease);	
			}
			else {
				cout << "���벻��ȷ����Ĭ�Ϸ�ʽ����" << endl;
				break;
			}

			for (j = 0; j < now_teacher.tea_course[i].stu_list.size(); j++) {//������б��γ�ѧ����Ϣ
				zancun = now_teacher.tea_course[i].stu_list[j];
				cout << "������" << zancun.stu_name << endl;
				cout << "ѧԺ��" << zancun.stu_college << endl;
				cout << "�༶��" << zancun.stu_class << endl;
				cout << "ѧ�ţ�" << zancun.stu_num << endl;
				cout << "�ɼ���";

				double jidian=0;
				int tijiao=0;
				
				int k;
				for (k = 0; k < zancun.stu_course.size(); k++) {
					if (zancun.stu_course[k].NO == nnum) {
						tijiao = zancun.stu_course[k].putin_key;
						if (zancun.stu_course[k].grade>0) {
							cout << zancun.stu_course[k].grade << endl;
						}
						else cout << "�ɼ�δ¼��" << endl;

						if (tijiao == 1) {
							jidian = zancun.stu_course[k].grade_point;
						}
					}
				}

				cout << "�ɼ��Ƿ��ύ��";
				if (tijiao == 1) {
					cout << "���ύ" << endl;
				}
				else if (tijiao == 0) {
					cout << "δ�ύ" << endl;
				}
				cout << "===================" << endl;
			}
		}
	}
}

//��ʾ�Լ��γ̵�����ѡ��ѧ������
void Teacher::show_course_studentlist()
{
	Student zancun;
	int i,j;

	
	int nnnum=0;

	for (i = 0; i < (now_teacher.tea_course).size(); i++) {
		cout << "�γ̣�" << now_teacher.tea_course[i].NO<<"-" << now_teacher.tea_course[i].couname << endl;
		for (j = 0; j < (now_teacher.tea_course[i].stu_list).size(); j++) {
			nnnum++;
			zancun = now_teacher.tea_course[i].stu_list[j];

			//cout << "�γ̣�" << now_teacher.tea_course[i].couname <<"    ";
			cout << "      ѧ�ţ�" << zancun.stu_num << std::right << setw(8) << "������" << zancun.stu_name << endl;
			//cout << "ѧԺ��" << zancun.stu_college << endl;
			//cout << "�༶��" << zancun.stu_class << endl;
		}
	}
	/*for (int i = 0; i < student.size(); i++) {//��ѧ���ӿڽ���
		for (int j = 0; j < student[i].stu_course.size(); j++) {//�����γ�
			if (student[i].stu_course[j].teacher_num == now_teacher.tea_num) {//�γ̵Ľ�ʦ���ŵ��ڱ��˺Ž�ʦ����
				nnnum++;
				//zancun = now_teacher.tea_course[i].stu_list[j];
				cout << "ѧ�ţ�" << student[i].stu_num << "    ";
				cout << "������" << student[i].stu_name << endl;
				//cout << "ѧԺ��" << zancun.stu_college << endl;
				//cout << "�༶��" << zancun.stu_class << endl;
			}

		}

	}*/




	if (nnnum == 0) {
		cout << "���Ŀγ��л�û��ѧ��" << endl;
	}
	else if (nnnum != 0) {
		cout << "�Ƿ����ѯָ��ѡ����ϸѧ����Ϣ ";
		int a = 0;
		cout << "1 for �� ��else for �˳���";
		cin >> a;
		if (a == 1) {
			//int m;
			int nn = 0;

			while (nn == 0) {
				cout << "������Ҫ��ѯ�Ŀγ̱�ţ�";
				int nnum;
				cin >> nnum;

				for (int m = 0; m <(now_teacher.tea_course).size(); m++) {
					if (now_teacher.tea_course[m].NO == nnum) {
						show_specify_student_information(nnum); //��ʾָ��ѡ��ѧ����Ϣ
						nn = 1;
						break;
					}
				}
				if (nn == 0) {
					cout << "�γ̱�Ŵ�������������," << endl;
				}
			}
		}
	}
	
}

//�γ̲鿴����
void Teacher::for_course_show()
{
	int signal = 0;
	int i;
	cout << "��ѡ��Ҫ���еĲ�����1.�鿴���пγ� 2.�鿴�Լ����ڵĿγ� 3.�鿴����ѡ��ѧ������ " << endl;
	cin >> i;
	while (!signal) {
		if (i == 1) {
			show_all_course();//�鿴���пγ�	
			signal = 1;
		}
		else if (i == 2) {
			show_teacher_course();//��ʾ�Լ������пγ�
			signal = 1;
		}
		else if (i == 3) {
			show_course_studentlist();//��ʾ�Լ��γ̵�����ѡ��ѧ������
			signal = 1;
		}
		else cout << "��������ȷ���" << endl;
	}

}

//��ʦ����ѡ��
void Teacher::show_teacher_choice()
{

	int signal = 0;//��ʶ��
	while (!signal) {

		cout << "��ѡ��Ҫ���еĲ�����1.�γ̲鿴 2.�ɼ����� 3.ע����¼" << endl;
		int i;
		cin >> i;

		if (i == 1) {
			for_course_show();//�γ̲鿴����
		}
		else if (i == 2) {
			for_course_set();//�ɼ���������
		}
		else if (i == 3) {

			teacher_information(now_teacher);

			for (int i = 0; i < teacher.size(); i++) {
				if (teacher[i].tea_num == now_teacher.tea_num) {
					teacher[i] = now_teacher;
				}
			}



			cout << "||����ע����¼||" << endl;
			signal = 1;
		}
		else cout << "��������ȷ���" << endl;
	}

}

//��ʦע��
void Teacher::teacher_register(string a)
{
	Teacher zancun;
	int stusize = (student).size();
	int signal = 0;//ע��ɹ���ʶ��

	cout << "|�Բ��𣬸��û���Ϣ������|" << endl;
	cout << "  |�Ƿ�Ҫע���û���Ϣ��|" << endl;
	cout << "     1.ע�� 2.�˳�" << endl;
	int choose;
	int b,i;
	cin >> choose;
	while (!signal) {
		if (choose == 1) {
			zancun.tea_num = a;//��ʦ����
			//strcpy_s(((string)zancun.stu_num).c_str(),a.size(), a.c_str());
			cout << "�������ʦʦ������";
			cin >> zancun.tea_name;
			cout << "�������ʦѧԺ��";
			cin >> zancun.tea_collage;


			cout << "�������ʦ���ڿγ̱�ţ�";
			int mm=0;
			while (mm == 0) {		
				cin >> b;
				for (i = 0; i < course.size(); i++) {
					if (b == course[i].NO ) {
						if (course[i].teacher_num == "-1") {//�ҵ��˿γ��Ҵ˿γ̻����˽���
							zancun.tea_course.push_back(course[i]);//����γ�
							course[i].teacher_num = zancun.tea_num;//����ʦ��Ϣ��ӵ��γ���Ϣ��


																   //mm = 1;
							break;
						}
						else if (course[i].teacher_num != "-1") {//�ҵ��˿γ̵����˽��ڴ˿γ�
							cout << "�㲻����Ӵ˿γ�" << endl;
							break;
						}					
					}
				}

				cout << "�Ƿ������ӽ��ڵĿγ̣�1 for ������else for ֹͣ��";
				int sigg;
				cin >> sigg;
				if (sigg == 1) {
					cout << "������γ̱�ţ�" ;
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
			show_teacher_choice();//��ʾ��ʦ���Խ��еĹ���ѡ��
		}
		else if (choose == 2) {
			//cout << "                ||�����˳�ѧ���ɼ�����ϵͳ||" << endl;
			//exit(0);
			break;
			break;
		}
		else cout << "��������ȷ���" << endl;
	}
	//teacher_information(zancun);
}

//��ʦ��¼
void Teacher::teacher_login()
{
	string a;
	int teasize = teacher.size();
	cout << "����ѡ���˽�ʦ��ݣ������빤�ţ�";
	cin >> a;
	Teacher zancun;

	//��ʼ������ڲ�����Ϣ
	if (teasize == 0) {
		teacher_register(a);//��ʦע��	
	}

	//�ڲ��н�ʦ��Ϣ
	else if (teasize > 0) {
		int i;

		int sig = 0;

		for (i = 0; i < teacher.size(); i++) {
			if (teacher[i].tea_num == a) {
				now_teacher = teacher[i];//����
				sig = 1;

				teacher_information(now_teacher);//��ʾ��ʦ��Ϣ
				show_teacher_choice();//��ʾ��ʦ���Խ��еĹ���ѡ��
			}
		}
		if (sig == 0) {//δ���ҵ������
			teacher_register(a);//��ʦע��
		}
	}
}

void initial_teacherlist()
{
	Teacher zancun;
	cout << endl<<"**���ý�ʦ��Ϣ���£�" << endl;
	cout << "======================================" << endl;
	for (int i = 0; i < teacher.size(); i++) {
		zancun = teacher[i];
		cout << "��ʦ���ţ�" << zancun.tea_num << endl;
		cout << "��ʦ������" << zancun.tea_name << endl;
		cout << "��ʦѧԺ��" << zancun.tea_collage << endl;
		cout << "��ʦ�γ̣�" ;

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
			throw"��ʦ��Ϣ�ļ���������";
		}
	}
	catch (char *msg) {
		cout << "����" << msg << endl;
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
	ofstream out("C://Users//11794//Desktop//�����coding test//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//teacher_information.txt");//���ļ�
	Teacher c1;
	out << c1;

	out.close();
}

void initial_teacher()
{
	ifstream in("C://Users//11794//Desktop//�����coding test//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//teacher_information.txt");//���ļ�
	Teacher c1;
	in >> c1;

	initial_teacherlist();

	in.close();
}