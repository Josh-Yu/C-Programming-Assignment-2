/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 1 2013 Assignment #2 - SCSIT Program Management System
* Full Name        : Joshua Yu
* Student Number   : s3235184
* Yallara Username : s3235184
* Course Code      : COSC1284
* Program Code     : BP162
* Start up code provided by Paul Miller and Xiaodong Li
***************************************************************************/

#include "pms.h"
#ifndef PMS_UTILITY_H
#define PMS_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
BOOLEAN systemInit(PMSType* pms);
BOOLEAN loadData(PMSType* pms, char* programFile, char* courseFile);
void systemFree(PMSType* pms);


BOOLEAN addToProgList(PMSType *pms, ProgramTypePtr newProgram);

void menu(PMSType* pms,char* programFile, char* courseFile);

BOOLEAN getUserInput(int charLimit, char *);

BOOLEAN validateCourseData(int, char *token, CourseTypePtr,\
ProgramTypePtr ,PMSType *pms);
BOOLEAN validateProgramData(int, char *token, ProgramTypePtr, PMSType *pms);

BOOLEAN writeCourseFile(PMSType *pms, char *courseFile);
BOOLEAN writeProgramFile(PMSType *pms, char *programFile);

BOOLEAN writeProgramReport(char *inputProgID,ProgramTypePtr programFound);

BOOLEAN checkStringLength(char* string,int charMin, int charMax);

BOOLEAN checkProgFieldNum(char *string);
BOOLEAN checkCourseFieldNum(char *string);


void generateProgID(PMSType *pms, char *);
void generateCourseID(ProgramTypePtr program, char * generateCourseID);
void removeTempProgram(ProgramTypePtr program);
#endif
