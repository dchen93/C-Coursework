// Authors: Cindy Chao & Daniel Chen
// Program will read and parse list of classes using structures and
// displaying student information.

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"
#include "vector.h"

int get_choice();
void display_info(Student **students, Course **courses, int count, 
  int count_students);
void read_courses(FILE *fp, Course ***courses, int *size, int *count); 

int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "r");
  FILE *fp2 = fopen(argv[2], "r");

  int size, count, size_student, count_student; 
  // size = size of array, count = num of elements
  Student **students = NULL;
  Course **courses = NULL;
  
  read_courses(fp, &courses, &size, &count); // parse
  read_student(fp2, &students, &size_student, &count_student);
  display_info(students, courses, count, count_student); 
  //calls get_choice, calls find_crn or find_subject

  deallocate(students, courses, size, count_student); // call deallocate

  fclose(fp);
  fclose(fp2);
 
  return 0;
} // main()

int get_choice()
{
  int choice, flag = 0; // flag acts as bool

  while(!flag) // display menu
  {
    printf("\nRSVP Menu\n");
    printf("0. Done.\n");
    printf("1. Find by CRN.\n");
    printf("2. Find by subject.\n");
    printf("3. Add course.\n");
    printf("4. Remove course.\n");
    printf("Your choice (0 - 4): ");
  
    if(scanf("%d", &choice) == 0)
    {
      printf("Incorrect Entry.\n");
      break; // exit loop 
    } // if()

    if(choice >= 0 && choice <= 4)
      return choice; 

    printf("Your choice is outside the acceptable range. Please try again.\n");

  } // while()

  return 0;

} // get_choice()

void display_info(Student **students, Course **courses, int count, 
  int count_student)
{
  int choice = 5;

  while(choice != 0)
  {
    choice = get_choice(); // call get_choice()

    if (choice == 1) // prompt for crn
      find_crn(students, courses, count, count_student);

    else // prompt for subject
      if (choice == 2) 
        find_subject(courses, count);

    else // prompt for adding course
      if (choice == 3)
        add_course(students, courses, count, count_student);

    else // prompt for removing course
      if (choice == 4)
        remove_course(students, count_student);

    else // prompt for exiting program
      if (choice == 0)
        break;

  } // while()

} // display_info()
