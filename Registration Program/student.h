//Authors: Cindy Chao & Daniel Chen

#ifndef STUDENT_H
#define STUDENT_H

typedef struct 
{
  char *first;
  char *surname;
  char sid[12];
  int crn[5];
  int count_class;
} Student;

#include "course.h"

void read_student(FILE *fp2, Student ***students, int *size_student, 
  int *count_student);

#endif
