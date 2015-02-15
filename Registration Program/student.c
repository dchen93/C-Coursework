//Authors: Cindy Chao & Daniel Chen
//student.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "vector.h"

void read_student(FILE *fp2, Student ***students, int *size_student, int *i)
{
  int j;
  char line[80], *temp;
  
  *i = 0;

  initialize_student(students, size_student); // call initialize

  while (fgets(line, 80, fp2) != NULL) // strtok at each , 
  {
    temp = strtok(line, ",");
    (*students)[*i]->surname = (char*) malloc(strlen(temp) + 1);
    strcpy((*students)[*i]->surname, temp);
    temp = strtok(NULL, ",");
    (*students)[*i]->first = (char*) malloc(strlen(temp) + 1);
    strcpy((*students)[*i]->first, temp);
    temp = strtok(NULL, ",");
    strcpy((*students)[*i]->sid, temp);
    
    j = 0; // reset j to 0

    while ((temp = strtok(NULL, ",")) != NULL)
    {
      (*students)[*i]->crn[j] =  atoi(temp); // assign number of ints
      j++; // increment j
    } // while()

    (*students)[*i]->count_class = j;
    (*i)++; // readjust size

    if (*i >= *size_student) // if count is greater, resize
      resize_student(students, size_student);

  } // while()
 
} // read_student()
