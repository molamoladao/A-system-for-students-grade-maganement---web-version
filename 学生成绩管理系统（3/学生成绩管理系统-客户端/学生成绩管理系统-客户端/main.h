#ifndef _MAIN_H_
#define _MAIN_H_

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include<vector>
#include <malloc.h>
#include <cstdint>
#include<cstring>
#include<iomanip>
#include"student.h"
#include"course.h"
#include"teacher.h"
#include"server.h"
#include"client.h"

using namespace std;

class Teacher;
class Course;
class Student;

extern int reinitsiganl;//×¢ÏúÐÅºÅ

extern vector<Student>student;
extern vector<Teacher>teacher;
extern vector<Course>course;

//void print_course_list(Course *zancun);

#endif


