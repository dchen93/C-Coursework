// Authors: Cindy Chao & Daniel Chen

#ifndef COURSE_H
#define COURSE_H

typedef struct
{
  int crn;
  char subject[4];
  char course[6];
} Course;

#include "student.h"

void read_courses(FILE *fp, Course ***courses, int *size, int *count);
void find_crn(Student **students, Course **courses, int count,
  int count_student);
void find_subject(Course **courses, int count);
void add_course(Student **students, Course **courses, int count, 
  int count_student);
void remove_course(Student **students, int count_student);

#endif
