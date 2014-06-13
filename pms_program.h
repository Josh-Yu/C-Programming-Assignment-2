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


#ifndef PMS_PROGRAM_H
#define PMS_PROGRAM_H

#include "pms.h"
struct program_data
{
    char progID[ID_LEN + 1];   /* Unique ID for a program */
    char progTitle[MAX_TITLE_LEN + 1];
    char progMajor[MAX_TITLE_LEN + 1];
    char progCode[PROG_CODE_LEN + 1];
    float progDuration;
    char progType[PROG_TYPE_LEN+1];    /* Undergrade(UG) or Postgrad (PG) */
    char progMode[MODE_LEN+1];  /* Full-time (FT) or Part-time (PT) */
    char progDescription[MAX_DESC_LEN+1];
    char majorDescription[MAX_DESC_LEN+1];
};


/* The node of the linked list*/
typedef struct program  
{
/* declare pointer 'data' to point to type program_data, 
not pointing at the moment*/
    struct program_data *data; 
    ProgramTypePtr nextProgram; /* Holds the address for the next node*/
    CourseTypePtr headCourse;
    unsigned numCourses;
} ProgramType;

/* create any function prototypes required for managing the pms_program list
 * here.
 */

int cmp(char* string1, char* string2);
ProgramTypePtr createPNode();

BOOLEAN deleteProgramNode(PMSType *pms, char *progID);

BOOLEAN bulkDeleteCourses(ProgramTypePtr);
void removeTempProgram(ProgramTypePtr program);
 
#endif


