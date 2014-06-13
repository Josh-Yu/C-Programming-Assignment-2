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
#ifndef PMS_COURSE_H
#define PMS_COURSE_H
#include "pms.h"
typedef struct teachPeriod
{
    unsigned semester;
    unsigned year;
} TeachPeriodType;

struct course_data
{
    char courseID[ID_LEN + 1];  /* Unique ID for a course */
    char progID[ID_LEN + 1];
    char courseTitle[MAX_TITLE_LEN + 1];
    char courseCode[COURSE_CODE_LEN + 1];
    unsigned creditPoints;
    TeachPeriodType teachPeriods[NUM_TEACHPERIODS];
    char courseCoordinator[MAX_TITLE_LEN+1];
    char courseDescription[MAX_DESC_LEN+1];
};

typedef struct course
{
    struct course_data *data;
    CourseTypePtr nextCourse;
} CourseType;

/* provide prototypes for managing the pms_course list data structure
 * here
 */

CourseTypePtr createCourseNode();

ProgramTypePtr findProgram(PMSType *pms, char *programID);

void addToCourseList(PMSType *pms, ProgramTypePtr currentProgram,\
CourseTypePtr newCourse);

CourseTypePtr findCourse(ProgramTypePtr program, char *courseID);

BOOLEAN deleteCourseNode(ProgramTypePtr program, char *courseID);

void removeTempCourse(CourseTypePtr newCourse);
#endif
