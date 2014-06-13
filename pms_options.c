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
#include "pms_options.h"
#include "pms_utility.h"

/****************************************************************************
* Menu option #1 and #2: Summary of Programs
* Allows the user to display a summary of all undergrad or postgrad programs
* and associated courses.
****************************************************************************/
void displaySummary(PMSType* pms, char* programType)
{
	
	ProgramTypePtr currentProgram;
	CourseTypePtr currentCourse;
	char creditPointString[MAX_TITLE_LEN + MAX_CREDIT_POINT_TXT ];
	
	/* STARTING POINT  */
	currentProgram = pms -> headProgram;

	/* check for empty course list*/
	if(currentProgram !=NULL && strcmp(programType, "PG") == 0)
	{
		printf("Summary of PostGrad Programs\n");
		printf("-----------------------------\n\n");
	}else if(currentProgram != NULL && strcmp(programType, "UG") == 0)
	{
		printf("Summary of UnderGrad Programs\n");
		printf("-----------------------------\n\n");
	}
	
	/* traversing the linked list & look for progType match*/
	while(pms->headProgram != NULL && currentProgram != NULL)
	{
		if(strcmp(currentProgram->data->progType, programType) == 0 )
		{
			printf("%-5s - %-35s\n",currentProgram-> data -> progID, currentProgram-> data -> progTitle);
			printf("%-7s(%s)  (%d Courses)\n","",currentProgram-> data -> progMajor, currentProgram->numCourses);
			printf("---------------------------------------------------------------------\n");
			printf("%3s%-5s %-42s %s \n","","ID","Course Title","Teach Period");

			printf("%3s%5s %-42s %s\n", "","-----","------------------------------------------", "-----------------");

			currentCourse = currentProgram-> headCourse;
			while(currentProgram -> headCourse != NULL && currentCourse != NULL)
			{
				sprintf(creditPointString, "%s(%dCPS)",currentCourse->data->courseTitle,currentCourse->data->creditPoints);	
				printf("%3s%5s %-42s %s %d %d\n", "",currentCourse->data->courseID,creditPointString, "Semester",currentCourse->data->teachPeriods[0].semester,currentCourse->data->teachPeriods[0].year);
				currentCourse = currentCourse-> nextCourse;
			}
			printf("\n");
		}
			/*the current node now points to the next node for the next iternation */
			currentProgram = currentProgram-> nextProgram;
	}/* end outer while */
}

/****************************************************************************
* Menu option #3: Detailed Program Report
* Allows the user to make a new report file for a chosen program.
****************************************************************************/
void programReport(PMSType* pms)
{
	char inputProgID[PROG_ID_LEN + EXTRA_SPACES];
	ProgramTypePtr programFound;

	printf("Detailed Program Report\n");
	printf("--------------------\n");
	printf("Enter program id (5 characters):");
	getUserInput(PROG_ID_LEN + EXTRA_SPACES,inputProgID);

	/* Call function to find program and return pointer to it*/
	programFound = findProgram(pms,inputProgID);
	
	if(programFound != NULL)
	{
		writeProgramReport(inputProgID,programFound);
	}
	else
	{
        printf("Cannot Generate Program Report for program: %s\n",inputProgID);
        printf("Returning back to menu\n\n");
	}
}


/****************************************************************************
* Menu option #4: Add Program
* Allows the user to add a new "program" record to the linked list.
****************************************************************************/
void addProgram(PMSType* pms)
{
char generatedProgID[PROG_ID_LEN + EXTRA_SPACES];
char inputProgramTitle[MAX_TITLE_LEN + EXTRA_SPACES];
char inputProgramType[PROG_TYPE_LEN + EXTRA_SPACES];
char inputProgramMajor[MAX_TITLE_LEN + EXTRA_SPACES];
char inputProgramCode[PROG_CODE_LEN + EXTRA_SPACES];
char inputProgramDuration[MAX_PROG_DURATION + EXTRA_SPACES];
char inputProgramMode[MODE_LEN + EXTRA_SPACES];
char inputProgramDescription[MAX_DESC_LEN + EXTRA_SPACES];
char inputMajorDescription[MAX_DESC_LEN + EXTRA_SPACES];

ProgramTypePtr newProgram;

/* prog ID generates automatically generateProgID()*/
newProgram = createPNode();


generateProgID(pms,generatedProgID);
printf("Program ID: %s\n",generatedProgID);
validateProgramData(PROGID_FIELD,generatedProgID,newProgram,pms);



printf("Program Title (1-35)\n");
if(getUserInput(MAX_TITLE_LEN + EXTRA_SPACES,inputProgramTitle)){
	return;
}
else{
	validateProgramData(PROG_TITLE_FIELD,inputProgramTitle,newProgram,pms);
}

printf("Undergrad (UG) or Postgrad (PG) program?: ");
if(getUserInput(PROG_TYPE_LEN + EXTRA_SPACES,inputProgramType))
{
	return;
}else{
	if(!validateProgramData(PROG_TYPE_FIELD,inputProgramType,newProgram,pms))
	return;
}

printf("Program Major: ");
if(getUserInput(MAX_TITLE_LEN + EXTRA_SPACES,inputProgramMajor))
{
return;
}else{
	validateProgramData(PROG_MAJOR_FIELD,inputProgramMajor,newProgram,pms);
}

printf("Program Code: ");
if(getUserInput(PROG_CODE_LEN + EXTRA_SPACES,inputProgramCode))
{
return;
}else{
	validateProgramData(PROG_CODE_FIELD,inputProgramCode,newProgram,pms);
}

printf("Program Duration (years): ");
if(getUserInput(MAX_PROG_DURATION + EXTRA_SPACES,inputProgramDuration))
{
return;
}else{
	validateProgramData(PROG_DURATION_FIELD,inputProgramDuration,newProgram,pms);
}

printf("Program Mode: ");
if(getUserInput(MODE_LEN + EXTRA_SPACES,inputProgramMode))
{
return;
}else{
	validateProgramData(PROG_MODE_FIELD,inputProgramMode,newProgram,pms);
}

printf("Program Description (1-300 character): ");
if(getUserInput(MAX_DESC_LEN + EXTRA_SPACES,inputProgramDescription))
{
return;
}else{
	validateProgramData(PROG_DESCRIPTION_FIELD,inputProgramDescription,newProgram,pms);
}

printf("Major Description (1-300): ");
if(getUserInput(MAX_DESC_LEN + EXTRA_SPACES,inputMajorDescription))
{
return;
}else{
    /* adding a newline character so when it is written to file the next programs will be written on a new line */
        if (inputMajorDescription[strlen(inputMajorDescription)] == '\0')
        {
            inputMajorDescription[strlen(inputMajorDescription)] = '\n';
        }
    validateProgramData(MAJOR_DESCRIPTION_FIELD,inputMajorDescription,newProgram,pms);
}

addToProgList(pms, newProgram); 

}
/****************************************************************************
* Menu option #5: Delete Program
* Deletes a "prorgam" and all corresponding courses.
****************************************************************************/
void deleteProgram(PMSType* pms)
{
	char inputProgID[PROG_ID_LEN + EXTRA_SPACES];

	ProgramTypePtr programNode;
	printf("Delete Program\n");
	printf("--------------------\n\n");

	printf("Warning: All course data for a program will be deleted if you proceed.\n\n");
	printf("Program ID: ");

	if(getUserInput(PROG_ID_LEN + EXTRA_SPACES,inputProgID))
	return;

	
	programNode = findProgram(pms, inputProgID);
	if(programNode == NULL)
	{
		printf("Program ID not found in the system!\n");
	}else
	{
		/* create variables to hold the char values of the data to delete */
		printf("Program \"%s - %s\" deleted for the system\n", programNode->data->progID, programNode->data->progTitle);
		deleteProgramNode(pms, inputProgID);
	}
} /*end deleteProgram() */

/****************************************************************************
* Menu option #6: Add Course
* Allows the user to add a new course to an existing "program". An error 
* message is given if the "program" doesn't exist.
****************************************************************************/
void addCourse(PMSType* pms)
{
char inputProgID[PROG_ID_LEN + EXTRA_SPACES];
char generatedCourseID[COURSE_ID_LEN + EXTRA_SPACES];
char inputCourseTitle[MAX_TITLE_LEN+ EXTRA_SPACES];
char inputCreditPoint[MAX_CREDIT_LEN + EXTRA_SPACES];
char inputTeachSemester[NUM_TEACHPERIODS + EXTRA_SPACES];
char inputTeachYear[MAX_YEAR_LEN + EXTRA_SPACES];
char inputCourseCoodinator[MAX_COORDINATOR_LEN + EXTRA_SPACES];
char inputDescription[MAX_DESC_LEN+ EXTRA_SPACES];

ProgramTypePtr programFound;
CourseTypePtr newCourse;


/*create a new empty course Node if program is found*/
newCourse =  createCourseNode();



printf("Add Course\n");
printf("------------\n\n");

printf("Program ID (5 Characters): ");
if(getUserInput(PROG_ID_LEN + EXTRA_SPACES,inputProgID))
return;

programFound = findProgram(pms,inputProgID);
if(programFound == NULL)
{
    printf("Program ID: %s not found\n",inputProgID);
    return;
}
validateCourseData(COURSE_PROGID_FIELD,inputProgID,newCourse,programFound,pms);

generateCourseID(programFound,generatedCourseID);
printf("New Course ID is %s|\n",generatedCourseID);  


validateCourseData(COURSEID_FIELD, generatedCourseID,newCourse,programFound,pms); 


printf("Course Title (1-35 characters ):");
if(getUserInput(MAX_TITLE_LEN + EXTRA_SPACES,inputCourseTitle)){
return;
}
else{
	validateCourseData(COURSE_TITLE_FIELD,inputCourseTitle, newCourse,programFound,pms);
}
printf("Credit Points: ");
if(getUserInput(MAX_CREDIT_LEN + EXTRA_SPACES,inputCreditPoint)){
return;
}else{
validateCourseData(COURSE_CREDIT_POINT_FIELD,inputCreditPoint, newCourse,programFound,pms);
}

printf("Teaching Semester: ");
if(getUserInput(NUM_TEACHPERIODS + EXTRA_SPACES,inputTeachSemester))
{
return;
}else{
validateCourseData(COURSE_TEACH_SEMESTER,inputTeachSemester, newCourse,programFound,pms);
}
printf("Teaching Year: ");
if(getUserInput(MAX_YEAR_LEN + EXTRA_SPACES,inputTeachYear)){
return;
}else{
validateCourseData(COURSE_TEACH_YEAR,inputTeachYear,newCourse,programFound,pms);
}

printf("Course Coordinator: ");
if(getUserInput(MAX_COORDINATOR_LEN + EXTRA_SPACES,inputCourseCoodinator)){
return;
}else{
validateCourseData(COURSE_COORDINATOR_FIELD, inputCourseCoodinator, newCourse,programFound,pms);
}

printf("Description (1-300): ");
if(getUserInput(MAX_DESC_LEN + EXTRA_SPACES,inputDescription)){
return;
}else{
validateCourseData(COURSE_DESCRIPTION_FIELD, inputDescription,newCourse,programFound,pms);
}

/* add the constructed node to the course link list for the program. */
addToCourseList(pms,programFound,newCourse);

}

/****************************************************************************
* Menu option #7: Delete Course
* Deletes a single course from a particular "program".
****************************************************************************/
void deleteCourse(PMSType *pms)
{
	ProgramTypePtr programNode;
	CourseTypePtr courseNode;

	char inputProgID[PROG_ID_LEN + EXTRA_SPACES];
	char inputCourseID[COURSE_ID_LEN + EXTRA_SPACES];
	printf("Delete Course\n");
	printf("----------------\n\n");

	printf("Program ID (5 characters): ");
	if(getUserInput(PROG_ID_LEN + EXTRA_SPACES,inputProgID))
		return;

	printf("Course OD (5 characters):");
	if(getUserInput(COURSE_ID_LEN + EXTRA_SPACES,inputCourseID))
	return;

	/* call function to find program and return null or program pointer */
	programNode = findProgram(pms, inputProgID);

	if(programNode != NULL)
	{		
		courseNode = findCourse(programNode,inputCourseID);
		if(courseNode != NULL)
		{
			deleteCourseNode(programNode,inputCourseID);
		}
		else
		{
			printf("Course ID does not exist in program ID provided\n");
		}
	}
	else
	{
		printf("Program ID does not exist in the system\n");
	}
}


/****************************************************************************
* Menu option #8: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(PMSType* pms, char* programFile, char *courseFile)
{
	writeProgramFile(pms, programFile);
	writeCourseFile(pms, courseFile);
}


