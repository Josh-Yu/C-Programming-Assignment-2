############################################################################
# COSC1283/1284 - Programming Techniques
# Semester 1 2013 Assignment #2 - SCSIT Program Management System
# Full Name        : Joshua Yu
# Student Number   : s3235184
# Yallara Username : s3235184
# Course Code      : COSC1284
# Program Code     : BP162
# Start up code provided by Christopher Hoobin, Paul Miller, and Xiaodong Li
############################################################################

CC = gcc
CFLAGS = -ansi -Wall -pedantic 

compile: pms.o pms_course.o pms_options.o pms_program.o pms_utility.o
	$(CC) -lm pms.o pms_course.o pms_options.o pms_program.o pms_utility.o -o pms

pms.o: pms.h pms_options.h pms_utility.h pms.c
	$(CC) $(CFLAGS) -c pms.c
	
pms_course.o: pms_course.h pms_course.c
	$(CC) $(CFLAGS) -c pms_course.c
	
pms_options.o: pms.h pms_options.h pms_utility.h pms_options.c
	$(CC) $(CFLAGS) -c pms_options.c
	
pms_program.o: pms_program.h pms_program.c
	$(CC) $(CFLAGS) -c pms_program.c
	
pms_utility.o: pms.h pms_options.h pms_utility.h pms_utility.c	
	$(CC) $(CFLAGS) -c pms_utility.c
	
clean:
	rm -f *.o core *.exe pms
	
archive:
	zip $(USER)-a2.zip course.dat program.dat pms.c pms.h \
	pms_course.c pms_course.h Makefile \pms_options.c \
	pms_options.h pms_program.c pms_program.h pms_readme.txt \
	pms_utility.c pms_utility.h
