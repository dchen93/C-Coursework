//Authors: Cindy Chao & Daniel Chen

#ifndef VECTOR_H
#define VECTOR_H

#include "student.h"
#include "course.h"

void initialize(Course ***courses, int *size);
void initialize_student(Student ***students, int *size_student);
void resize_student(Student ***students, int *size_student);
void resize(Course ***courses, int *size);
void deallocate(Student **students, Course **courses, int size, 
  int count_student);

#endif
