# Authors: Cindy Chao & Daniel Chen

rsvp.out: rsvp.o course.o vector.o student.o
	gcc -g -Wall -o rsvp.out rsvp.o course.o student.o vector.o

rsvp.o: rsvp.c course.h student.h vector.h
	gcc -g -Wall -c rsvp.c

course.o: course.c course.h vector.h student.h
	gcc -g -Wall -c course.c

vector.o: vector.c vector.h student.h
	gcc -g -Wall -c vector.c

student.o: student.c student.h vector.h
	gcc -g -Wall -c student.c

clean: 
	rm -f rsvp.out rsvp.o course.o student.o vector.o
	
