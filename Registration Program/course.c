// Authors: Cindy Chao & Daniel Chen
// course.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "course.h"
#include "student.h"

void read_courses(FILE *fp, Course ***courses, int *size, int *count)
{
  int i; 
  char line[200], *ptr[3], *temp;

  *count = 0; //initialize count
  initialize(courses, size); //call initializei

  if (fgets(line, 200, fp) == NULL)
  {
    printf("File could not be opened.\n");
    exit(1);
  } // if()

  while (fgets(line, 200, fp) != NULL)
  {
    temp = strtok(line, "\t^"); // parse line
    for (i = 0; i < 3; i++)
    {
      ptr[i] = temp; // assign tokens 
      temp = strtok(NULL, "\t^"); 
    } // for()

    if (ptr[0] && (strlen(ptr[0]) == 5) && ptr[1] && (strlen(ptr[1]) == 3) 
      && ptr[2])
    {
      (*courses)[*count]->crn = atoi(ptr[0]); // assign ptr[0] to crn 
      strcpy((*courses)[*count]->subject, ptr[1]); // copy ptr[1] to subject
      strcpy((*courses)[*count]->course, ptr[2]); // copy ptr[2] to course
      (*count)++;
    } // if()

    if (*count >= *size)
      resize(courses, size); // call resize if too large
  } // while()
} // read_courses()

void find_crn(Student **students, Course **courses, int count, 
  int count_student)
{
  int temp, i, j;

  printf("Please enter a CRN: ");
  scanf("%d", &temp);
  
  for (i = 0; i < count; i++)
  {
    if (courses[i]->crn == temp) // if crn is the same as temp
    {
      printf("%s %s\n", courses[i]->subject, courses[i]->course);
      break; // continue to next if statement
    } // if ()
  } // for()

  if (i == count) // if for loop reaches end
    printf("CRN %d not found.\n", temp);
  else 
  {
    for (i = 0; i < count_student; i++)
    {
      for (j = 0; j < students[i]->count_class; j++)
      {
        if (students[i]->crn[j] == temp)
          printf("%s %s\n", students[i]->surname, students[i]->first);
      } // for()
    } // for()
  } // else() 
} // find_crn()

void find_subject(Course **courses, int count)
{
  int i, flag = 0;
  char temp[20];

  printf("Please enter a subject: ");
  scanf("%s", temp);
  temp[3] = '\0'; // completes the string

  for (i = 0; i < count; i++)
  {
    if (strcmp(courses[i]->subject, temp) == 0) // if they are the same
    {
      printf("%d %s %s\n", courses[i]->crn, temp, courses[i]->course);
      flag = 1;
    } // if() 
    
    else // if subject does not match
      if ((flag == 0) && (strcmp(courses[i]->subject, temp) != 0) 
        && (i == (count - 1)))
        printf("No courses were found for %s.\n", temp);
  } // for()
} // find_subject()

void add_course(Student **students, Course **courses, int count, 
  int count_student)
{
  int i, j, k, temp;
  char temp_sid[12]; // put student id in here temporarily
 
  printf("Add Course\n");
  printf("Please enter the SID of the student: ");
  scanf("%s", temp_sid);

  for (i = 0; i < count_student; i++)
  {
    if (strcmp(students[i]->sid, temp_sid) == 0)
      break; // continue on to next if statement
  } // for()

  if (i == count_student) // if for loop reaches end
    printf("A student with SID #%s was not found.\n", temp_sid);

  else 
    if (students[i]->count_class == 5) // if student has 5 classes
      printf("You are already taking 5 courses.\n");

  else 
  {
    printf("Please enter the CRN: ");
    scanf("%d", &temp);

    for (j = 0; j < count; j++)
    {    
      if (courses[j]->crn == temp) 
      {
        break;
      } // if()
    } // for()

    if (j == count) // if for loop reaches end
      printf("There is no course with CRN #%d\n", temp);

    else
    {
      for (k = 0; k < students[i]->count_class; k++)
      {
        if (temp == students[i]->crn[k]) // if entered crn matches
        {
          printf("You are already taking that course.\n");
          break; // continue onto next for loop
        } // if ()
      } // for()
  
      for (j = 0; j < count; j++)
      {    
        if (courses[j]->crn == temp) 
        {
          students[i]->crn[students[i]->count_class] = temp; //add class
          students[i]->count_class++; // update number of classes
          break;
        } // if()
      } // for()
    } // else to account for different summer sessions classes
  } // else()

} // add_course()

void remove_course(Student **students, int count_student)
{
  int i, k, l, temp_crn, prev_count_class;
  char temp[12]; //for entering student id

  printf("Remove Course\n");  
  printf("Please enter the SID of the student: ");
  scanf("%s", temp);
  
  for (i = 0; i < count_student; i++)
  {
    if (strcmp(students[i]->sid, temp) == 0)
      break;
  } // for()

  if (i == count_student)
    printf("A student with SID #%s was not found.\n", temp);

  else 
  {
    printf("Current courses:");

    for (k = 0; k < students[i]->count_class; k++)
      printf(" %d", students[i]->crn[k]);

    printf("\n"); // new line

    printf("Please enter the CRN: ");
    scanf("%d", &temp_crn);

    prev_count_class = students[i]->count_class;
    
    for (k = 0; k < students[i]->count_class; k++)
    {
      if (temp_crn == students[i]->crn[k]) // if temp matches student's crn's
      {
        for (l = k; l < students[i]->count_class; l++)
          students[i]->crn[k] = students[i]->crn[k+1]; // shift array element
        
        students[i]->count_class--; // readjust number of classes
        break;
      } // if()
    } // for()

    if (k == prev_count_class)
      printf("You are not taking that course.\n");
  } // else()
} // remove_course()
