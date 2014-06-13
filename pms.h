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

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* program header files */
#include "pms_program.h"
#include "pms_course.h"
#ifndef PMS_H
#define PMS_H


/* System-wide constants. */
#define ID_LEN 5
#define PROG_ID_LEN 5
#define PROG_TYPE_LEN 2
#define MODE_LEN 2
#define MIN_TITLE_LEN 1     /*this value also applies to major titles */
#define MAX_TITLE_LEN 35    /* modified - This value also applies to major*/
#define PROG_CODE_LEN 5
#define COURSE_ID_LEN 5  /* modified */
#define COURSE_CODE_LEN 8 /* eg COSC1073*/
#define MIN_DESC_LEN 1
#define MAX_DESC_LEN 300   /* modified*/
#define NUM_TEACHPERIODS 1
#define SUCCESS 1
#define FAILURE 0

/* My defined variables*/

#define MAX_OPTION_INPUT 1 /* Used in the menu*/
#define EXTRA_SPACES 2
#define MAX_CREDIT_POINT_TXT 7


#define MAX_CREDIT_LEN 2 /*eg 12 */
#define MIN_COORDINATOR_LEN 1
#define MAX_COORDINATOR_LEN 25 /* eg Charles Thevathayan*/

/*"Semester 1,"(courses) used together with max_year_len*/
#define MAX_SEMESTER_LEN 12
#define MAX_YEAR_LEN 4 /*eg 1998 */

#define MAX_PROG_DURATION 2 /*For adding to programs #4*/

#define MIN_CREDIT_POINT_RANGE 1 /*minmal credit point a course can have */
#define MAX_CREDIT_POINT_MAX_RANGE 48/*maximum credit point a course can have*/

#define MIN_COURSE_YEAR_YEAR 1990 /*Minimal year for course teaching*/
#define MAX_COURSE_TEACH_YEAR 2025 /* max course year for teaching*/


/* used to identify what type of validation check to perform for program */
#define PROGID_FIELD            0
#define PROG_TYPE_FIELD         1
#define PROG_TITLE_FIELD        2
#define PROG_MAJOR_FIELD        3
#define PROG_CODE_FIELD         4
#define PROG_DURATION_FIELD     5
#define PROG_MODE_FIELD         6
#define PROG_DESCRIPTION_FIELD  7
#define MAJOR_DESCRIPTION_FIELD 8


/* used to identify what type of validation check to perform for course */
#define COURSEID_FIELD            0
#define COURSE_PROGID_FIELD       1
#define COURSE_TITLE_FIELD        2
#define COURSE_CODE_FIELD         3
#define COURSE_CREDIT_POINT_FIELD 4
#define COURSE_TEACH_PERIOD       5 /*only used when reading course files in*/
#define COURSE_COORDINATOR_FIELD  6
#define COURSE_DESCRIPTION_FIELD  7

#define COURSE_TEACH_SEMESTER     8
#define COURSE_TEACH_YEAR         9
/* enumeration that defines the BOOLEAN data type as two possible integers,
 * 0 and 1
 */
typedef enum truefalse
{
    FALSE=0,TRUE
} BOOLEAN;

/* predeclare the program and course structs */
/*pointer that will point to of type program*/
typedef struct program *ProgramTypePtr;
typedef struct course *CourseTypePtr;

/* Structure definitions. */

typedef struct pms
{

    ProgramTypePtr headProgram;
    unsigned numPrograms;
} PMSType;


#endif

