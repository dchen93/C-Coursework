// Authors: Cindy Chao & Daniel Chen
// vector.c

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "vector.h"

void initialize(Course ***courses, int *size)
{
  int i;
  *size = 100; // size starts off at 100
 
  (*courses) = (Course**) malloc((*size) * sizeof(Course*));
 
 for (i=0; i<*size; i++) // malloc for each course
    (*courses)[i] = (Course*) malloc(sizeof(Course));
 
} // initialize()

void initialize_student(Student ***students, int *size_student)
{
  int i;
  *size_student = 10;

  (*students) = (Student**) malloc((*size_student) * sizeof(Student*));

  for (i=0; i<*size_student; i++) // malloc for each student
    (*students)[i] = (Student*) malloc(sizeof(Student));
} // initialize_student()

void resize_student(Student ***students, int *size_student)
{
  int i;
  Student **temp_students;
  
  temp_students = (Student**) malloc(*size_student *2 * sizeof(Student*));
  
  for (i = 0; i < *size_student; i++)
  {
    temp_students[i] = (Student*) malloc(sizeof(Course));
    temp_students[i] = (*students)[i];
  } // for()

  free(*students); // free memory in students
  *students = temp_students; // set equal to temp
  
  for (i = *size_student; i < *size_student * 2; i++)
    (*students)[i] = (Student*) malloc(sizeof(Student));

  (*size_student) *= 2; // double size

} // resize_student()

void resize(Course ***courses, int *size)
{
  int i;
  Course **temp_courses;

  temp_courses = (Course**) malloc(*size * 2 * sizeof(Course*));
  
  for (i = 0; i < *size; i++)
  {
    temp_courses[i] = (Course*) malloc(sizeof(Course));
    temp_courses[i] = (*courses)[i]; 
  } // for()
 
  free(*courses); // free and reassign pointer
  *courses = temp_courses;
  
  for (i = *size; i < *size * 2; i++)
    (*courses)[i] = (Course*) malloc(sizeof(Course));

  (*size) *= 2; // double size

} // resize()

void deallocate(Student **students, Course **courses, int size, 
  int count_student)
{
  int i;
  // freeing memory after memory allocation is no longer needed

  for (i = 0; i < size; i++)
    free(courses[i]);

  for (i = 0; i < count_student; i++)
  {
    free(students[i]->surname);
    free(students[i]->first);
  } // for()
 
  for (i = 0; i < count_student; i++)
    free(students[i]);

  free(students);
  free(courses);

} // deallocate()
