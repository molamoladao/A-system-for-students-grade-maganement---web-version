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
	ssend.push_back("��ʦ������");
	ssend.push_back(zancun.tea_name);
	ssend.push_back("\n");

	ssend.push_back("��ʦѧԺ��");
	ssend.push_back(zancun.tea_collage);
	ssend.push_back("\n");

	ssend.push_back("��ʦ���ţ�");
	ssend.push_back(zancun.tea_num);
	ssend.push_back("\n");
	//cout << "��ʦ������" << zancun.tea_name << endl;
	//cout << "��ʦѧԺ��" << zancun.tea_collage << endl;
	//cout << "��ʦ���ţ�" << zancun.tea_num << endl;
	if ((zancun.tea_course).size() == 0) {
		ssend.push_back("���ڿγ̣�[����ʦ�޽��ڵĿγ�]");
		//ssend.push_back(zancun.tea_collage);
		ssend.push_back("\n");
		//cout << "���ڿγ̣�[����ʦ�޽��ڵĿγ�]" << endl;
	}
	else if ((zancun.tea_course).size() > 0) {
		ssend.push_back("���ڿγ̣�");
		//cout << "���ڿγ̣�";
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

//��ӡ�γ���Ϣ
void print_course_list2(Course  zancun)
{
	stringstream s;
	vector<string>ssend;

	ssend.push_back("�γ̱�ţ�");
	s << zancun.NO;
	ssend.push_back(s.str());
	s.str("");
	ssend.push_back("\n");

	ssend.push_back("�γ����ƣ�");
	ssend.push_back(zancun.couname);
	ssend.push_back("\n");

	ssend.push_back("�γ����ͣ�");
	s << zancun.kind;
	ssend.push_back(s.str());
	s.str("");
	ssend.push_back("\n");

	ssend.push_back("�γ�ѧ�֣�");
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
	/*cout << "�γ̱�ţ�" << zancun.NO << endl;
	cout << "�γ����ƣ�" << zancun.couname << endl;
	cout << "�γ����ͣ�" << zancun.kind << endl;
	cout << "�γ�ѧ�֣�" << zancun.point << endl;
	cout << "===================" << endl;*/
}
//¼��ָ��ѡ�ε�ָ��ѧ���ɼ�
void Teacher::set_student_grade(Student zancun, Course zancun2)
{
	int ggrade;
	//cout << "������ɼ�[��Χ��0-100]��";

	int i, j, k;
	//int cc = 0;
	while (1) {
		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const char * sendData = "--������ɼ�[��Χ��0-100]��";
		send(sClient, sendData, strlen(sendData), 0);
		//cout << "������ɼ�[��Χ��0-100]��";
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

			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "�ɼ���¼�ɹ���\n";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "�ɼ���¼�ɹ���" << endl;
			break;

		}
		else if (ggrade < 0 || ggrade>100) {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "--���벻���Ϲ淶��������¼��ɼ�[�ɼ���Χ��0-100]��";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "���벻���Ϲ淶��������¼��ɼ�[�ɼ���Χ��0-100]��";
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
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "�ɼ��ύ�ɹ�\n";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "�ɼ��ύ�ɹ�" << endl;
}

//�ɼ���������
void Teacher::for_course_set()
{
	//Course  zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--��������Ҫ���в����Ŀγ̱��룺";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "��������Ҫ���в����Ŀγ̱��룺";
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
			if (now_teacher.tea_course[k].NO == a) {//�ҵ��γ�
				ssg = 1;
				
				if (now_teacher.tea_course[k].putin_key == 0 && now_teacher.tea_course[k].stu_list.size()>0) {//�ɼ�δ�ύ
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "--��ѡ��ɼ��������ͣ�1 for �ɼ�¼�롢�޸�;2 for �ɼ��ύ \n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "��ѡ��ɼ��������ͣ�1 for �ɼ�¼�롢�޸�;2 for �ɼ��ύ " << endl;
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
						const char * sendData = "--��ѡ����Ҫ���гɼ�������ѧ��(ѧ��):";
						send(sClient, sendData, strlen(sendData), 0);
						//cout << "��ѡ����Ҫ���гɼ�������ѧ��(ѧ��):";
						string stunnum;
						int ret = recv(sClient, revData, 255, 0);
						if (ret > 0)
						{
							revData[ret] = 0x00;
						}
						stunnum = revData;
						//cin >> stunnum;
						int q;
						int found = 0;//�Ƿ��ڱ��γ����ҵ���ѧ��
						for (q = 0; q < (now_teacher.tea_course[k].stu_list).size(); q++) {
							if (now_teacher.tea_course[k].stu_list[q].stu_num == stunnum) {
								found = 1;
								pp = 1;
								closesocket(sClient);
								sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
								const char * sendData = "--��ѡ�������1 for �ɼ�¼�룻2 for �ɼ��޸�\n";
								send(sClient, sendData, strlen(sendData), 0);
								//cout << "--��ѡ�������1 for �ɼ�¼�룻2 for �ɼ��޸�" << endl;
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
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//¼��ѧ���ɼ�
										qq = 1;
									}
									else if (c == 2) {
										set_student_grade(now_teacher.tea_course[k].stu_list[q], now_teacher.tea_course[k]);//�޸�ѧ���ɼ�
										qq = 1;
									}
									else {
										closesocket(sClient);
										sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
										const char * sendData = "--����ѡ���������������룺";
										send(sClient, sendData, strlen(sendData), 0);
										//cout << "����ѡ���������������룺";
									}
										
								}

							}
						}
						if (found == 0) {
							closesocket(sClient);
							sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
							const char * sendData = "��ѧ��δѡ��˿γ�\n";
							send(sClient, sendData, strlen(sendData), 0);
							//cout << "��ѧ��δѡ��˿γ�" << endl;
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
							closesocket(sClient);
							sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
							const char * sendData = "���γ̻���ѧ���ɼ�δ¼�룬��������ύ\n";
							send(sClient, sendData, strlen(sendData), 0);
							//cout << "���γ̻���ѧ���ɼ�δ¼�룬��������ύ" << endl;
							pp = 1;
						}
						//logon_student_grade(now_teacher.tea_course[k]);//�ύ���γ�ѧ���ɼ�
						//pp = 1;
					}
					else {
						closesocket(sClient);
						sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
						const char * sendData = "--�ɼ������������ѡ���������������룺";
						send(sClient, sendData, strlen(sendData), 0);
						//cout << "�ɼ������������ѡ���������������룺";
					}
						
				}
				else if (now_teacher.tea_course[k].putin_key == 1) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "�ɼ��Ѿ��ύ���޷��ٽ��в���\n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "�ɼ��Ѿ��ύ���޷��ٽ��в���" << endl;
					pp = 1;
				}
				else if (now_teacher.tea_course[k].stu_list.size() == 0) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData = "�γ���û��ѧ����Ϣ���޷������ɼ�\n";
					send(sClient, sendData, strlen(sendData), 0);
					//cout << "�γ���û��ѧ����Ϣ���޷������ɼ�" << endl;
					pp = 1;
				}
			}
		}

		if (ssg == 0) {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "�㲻�ܲ����˿γ̳ɼ���\n";
			send(sClient, sendData, strlen(sendData), 0);

			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData2 = "--1 for ��������γ̱��룬else for�˳��˲���:";
			send(sClient, sendData2, strlen(sendData2), 0);
			//cout << "�㲻�ܲ����˿γ̳ɼ���" << endl;
			//cout << "1 for ��������γ̱��룬else for�˳��˲���:";
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
				cout << "--��������Ҫ���в����Ŀγ̱��룺";
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

//�鿴���пγ�
void Teacher::show_all_course()
{
	int k;

	Course zancun1;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "   ���޿γ̣�\n";
	send(sClient, sendData, strlen(sendData), 0);
	//cout << "   ���޿γ̣�" << endl;
	for (k = 0; k < course.size(); k++) {
		if (course[k].kind == 1) {
			zancun1 = course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData2 = "   ѡ�޿γ̣�\n";
	send(sClient, sendData2, strlen(sendData2), 0);
	//cout << "   ѡ�޿γ̣�" << endl;
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

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "   ���޿γ̣�\n";
	send(sClient, sendData, strlen(sendData), 0);
    //cout << "   ���޿γ̣�" << endl;

	for (int k = 0; k < (now_teacher.tea_course).size(); k++) {
		if (now_teacher.tea_course[k].kind == 1) {
			zancun1 = now_teacher.tea_course[k];
			print_course_list2(zancun1);
		}
	}

	Course zancun2;
	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData3 = "   ѡ�޿γ̣�\n";
	send(sClient, sendData3, strlen(sendData3), 0);
	//cout << "   ѡ�޿γ̣�" << endl;
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

				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData2 = "���γ���ʱû��ѧ����Ϣ";
				send(sClient, sendData2, strlen(sendData2), 0);

				//cout << "���γ���ʱû��ѧ����Ϣ" << endl;
			}
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData2 = "--��ѡ��ѧ����Ϣ���ַ�ʽ�� 1for��ѧ������2for��ѧ�Ž���3for���ɼ�����4for���ɼ�����\n";
			send(sClient, sendData2, strlen(sendData2), 0);
			//cout << "��ѡ��ѧ����Ϣ���ַ�ʽ��";
			//cout << "1for��ѧ������2for��ѧ�Ž���3for���ɼ�����4for���ɼ�����" << endl;
			
			string a;
			//��������  
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				//printf(revData);
			}
			a=revData[0];
			
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
				closesocket(sClient);
				sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
				const char * sendData2 = "���벻��ȷ����Ĭ�Ϸ�ʽ����\n";
				send(sClient, sendData2, strlen(sendData2), 0);
				//cout << "���벻��ȷ����Ĭ�Ϸ�ʽ����" << endl;
				break;
			}
			vector<string>ssend;
			for (j = 0; j < now_teacher.tea_course[i].stu_list.size(); j++) {//������б��γ�ѧ����Ϣ
				zancun = now_teacher.tea_course[i].stu_list[j];

				ssend.push_back("������");
				ssend.push_back(zancun.stu_name);
				ssend.push_back("\n");

				ssend.push_back("ѧԺ��");
				ssend.push_back(zancun.stu_college);
				ssend.push_back("\n");

				ssend.push_back("�༶��");
				ssend.push_back(zancun.stu_class);
				ssend.push_back("\n");

				ssend.push_back("ѧ�ţ�");
				ssend.push_back(zancun.stu_num);
				ssend.push_back("\n");

				ssend.push_back("�ɼ���");

				//cout << "������" << zancun.stu_name << endl;
				//cout << "ѧԺ��" << zancun.stu_college << endl;
				//cout << "�༶��" << zancun.stu_class << endl;
				//cout << "ѧ�ţ�" << zancun.stu_num << endl;
				//cout << "�ɼ���";

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
							ssend.push_back("�ɼ�δ¼��\n");
							//ssend.push_back("");
							//cout << "�ɼ�δ¼��" << endl;
						}
							

						if (tijiao == 1) {
							jidian = zancun.stu_course[k].grade_point;
						}
					}
				}
				ssend.push_back("�ɼ��Ƿ��ύ��");
				//cout << "�ɼ��Ƿ��ύ��";
				if (tijiao == 1) {
					ssend.push_back("���ύ\n");
					//ssend.push_back("");
					//cout << "���ύ" << endl;
				}
				else if (tijiao == 0) {
					ssend.push_back("δ�ύ\n");
					//ssend.push_back("");
					//cout << "δ�ύ" << endl;
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

//��ʾ�Լ��γ̵�����ѡ��ѧ������
void Teacher::show_course_studentlist()
{
	Student zancun;
	int i,j;
	
	int nnnum=0;

	vector<string>ssend;
	stringstream k;

	for (i = 0; i < (now_teacher.tea_course).size(); i++) {
		ssend.push_back("�γ̣�");
		k << now_teacher.tea_course[i].NO;
		ssend.push_back(k.str());
		k.str("");
		ssend.push_back(now_teacher.tea_course[i].couname);
		ssend.push_back("\n");

		//cout << "�γ̣�" << now_teacher.tea_course[i].NO<<"-" << now_teacher.tea_course[i].couname << endl;
		for (j = 0; j < (now_teacher.tea_course[i].stu_list).size(); j++) {
			nnnum++;
			zancun = now_teacher.tea_course[i].stu_list[j];

			//cout << "�γ̣�" << now_teacher.tea_course[i].couname <<"    ";
			ssend.push_back("      ѧ�ţ�");
			ssend.push_back(zancun.stu_num);
			ssend.push_back("          ");
			//ssend.push_back("setw(8)");
			ssend.push_back("������");
			ssend.push_back(zancun.stu_name);
			ssend.push_back("\n");

			//cout << "      ѧ�ţ�" << zancun.stu_num << std::right << setw(8) << "������" << zancun.stu_name << endl;
			//cout << "ѧԺ��" << zancun.stu_college << endl;
			//cout << "�༶��" << zancun.stu_class << endl;
		}
	}


	if (nnnum == 0) {
		ssend.push_back("���Ŀγ��л�û��ѧ��\n");

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
		//cout << "���Ŀγ��л�û��ѧ��" << endl;
	}
	else if (nnnum != 0) {
		ssend.push_back("�Ƿ����ѯָ��ѡ����ϸѧ����Ϣ\n");
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
		const char * sendData2 = "--1 for �� ��else for �˳���";
		send(sClient, sendData2, strlen(sendData2), 0);
		//cout << "1 for �� ��else for �˳���";
		//��������  
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
				const char * sendData3 = "--������Ҫ��ѯ�Ŀγ̱�ţ�";
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
						show_specify_student_information(nnum); //��ʾָ��ѡ��ѧ����Ϣ
						nn = 1;
						break;
					}
				}
				if (nn == 0) {
					closesocket(sClient);
					sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
					const char * sendData4 = "�γ̱�Ŵ�������������\n";
					send(sClient, sendData4, strlen(sendData4), 0);
					//cout << "�γ̱�Ŵ�������������," << endl;
				}
			}
		}
		ss.clear();
		ssend.clear();
	}
	
}

//�γ̲鿴����
void Teacher::for_course_show()
{
	int signal = 0;
	int i;

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--��ѡ��Ҫ���еĲ�����1.�鿴���пγ� 2.�鿴�Լ����ڵĿγ� 3.�鿴����ѡ��ѧ������\n";
	send(sClient, sendData, strlen(sendData), 0);
	//��������  
	int ret = recv(sClient, revData, 255, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
		//printf(revData);
	}
	//cin >> i;
	while (!signal) {
		if (revData[0] == '1') {
			show_all_course();//�鿴���пγ�	
			signal = 1;
		}
		else if (revData[0] == '2') {
			show_teacher_course();//��ʾ�Լ������пγ�
			signal = 1;
		}
		else if (revData[0] == '3') {
			show_course_studentlist();//��ʾ�Լ��γ̵�����ѡ��ѧ������
			signal = 1;
		}
		else {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "��������ȷ���\n";
			send(sClient, sendData, strlen(sendData), 0);
		}
	}
}

//��ʦ����ѡ��
void Teacher::show_teacher_choice()
{

	int signal = 0;//��ʶ��
	while (!signal) {

		closesocket(sClient);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		const char * sendData = "--��ѡ��Ҫ���еĲ�����1.�γ̲鿴 2.�ɼ����� 3.ע����¼\n";
		send(sClient, sendData, strlen(sendData), 0);

		//cout << "��ѡ��Ҫ���еĲ�����1.�γ̲鿴 2.�ɼ����� 3.ע����¼" << endl;
		//int i;
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			//printf(revData);
		}
		//i = revData[0];

		if (revData[0] == '1') {
			for_course_show();//�γ̲鿴����
		}
		else if (revData[0] == '2') {
			for_course_set();//�ɼ���������
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
			const char * sendData = "||����ע����¼||\n";
			send(sClient, sendData, strlen(sendData), 0);

			//cout << "||����ע����¼||" << endl;
			signal = 1;
		}
		else {
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "��������ȷ���\n";
			send(sClient, sendData, strlen(sendData), 0);
			//cout << "��������ȷ���" << endl;
		}

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

	closesocket(sClient);
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	const char * sendData = "--����ѡ���˽�ʦ��ݣ������빤�ţ�";
	send(sClient, sendData, strlen(sendData), 0);

	//cout << "����ѡ���˽�ʦ��ݣ������빤�ţ�";

	//cin >> a;
	int ret = recv(sClient, revData, 255, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
		//printf(revData);
	}
	a = revData;
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
			closesocket(sClient);
			sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
			const char * sendData = "��ȡ�ļ���������\n";
			send(sClient, sendData, strlen(sendData), 0);

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
	ofstream out("C://Users//11794//Desktop//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ��3//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//teacher_information.txt");//���ļ�
	Teacher c1;
	out << c1;

	out.close();
}

void initial_teacher()
{
	ifstream in("C://Users//11794//Desktop//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ��3//ѧ���ɼ�����ϵͳ//ѧ���ɼ�����ϵͳ//teacher_information.txt");//���ļ�
	Teacher c1;
	in >> c1;

	initial_teacherlist();

	in.close();
}