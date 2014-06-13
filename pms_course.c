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

#include "pms_course.h"

/* provide implementations of functions to manage the pms_course list data
 * structure here
 */
/****************************************************************************
* Create course Node and create the data struct inside the node and link it
* Returns the pointer to the Node
****************************************************************************/
 CourseTypePtr createCourseNode()
 {
	CourseTypePtr newCourse;
		
	newCourse = malloc(sizeof(CourseType));
	newCourse -> data = malloc(sizeof(struct course_data));
	newCourse -> nextCourse = NULL;
	return newCourse;
 }
 
/****************************************************************************
* Inserting the course into the program also does comparisons
* PARAMS-uses the program pointer reference to modify the course info for it
****************************************************************************/
void addToCourseList(PMSType *pms, ProgramTypePtr currentProgram,\
CourseTypePtr newCourse)
{
	CourseTypePtr currentCourseNode, previousCourseNode;
	
	/* Inserting the course when their is currently no courses in the 
	course linkedlist*/
	currentCourseNode = currentProgram-> headCourse;
	
	if(currentProgram-> headCourse == NULL)
	{
		/* the head coruse will now point to the newly created course*/
		currentProgram->headCourse = newCourse;
	}
	else 
	{/* for cases where the head of the courseList is already pointing to a 
	node*/
/* Used to keep track of the previous node, usually used when inserting into 
linkedlist between two endpoints*/
		previousCourseNode = NULL;
	
		
		
		while(currentCourseNode != NULL && cmp(newCourse->data->courseTitle,\
currentCourseNode->data->courseTitle))
		{
			previousCourseNode = currentCourseNode;
			/*Next iteration, the next node will be the current */
			currentCourseNode = currentCourseNode->nextCourse; 
		}
	

	
/* Inserting the node at the the head of the linkedlist when nodes already 
exist in the node */
		if(previousCourseNode == NULL)
		{/* new course->next points to the original node pointed by head */
			newCourse->nextCourse = currentProgram->headCourse; 
		/* course head now points to the new course node  */
			currentProgram->headCourse = newCourse; 
		}
		else /* Middle Insertion*/
		{
			newCourse->nextCourse = currentCourseNode; /* */
			previousCourseNode->nextCourse = newCourse;
		}
	}
	
	currentProgram -> numCourses++;
} /* end addToCourse()*/


/****************************************************************************
* Delete Course, pass in the memory address(pointer) of the matching program.
* traverse the course linkedlist searching for the course ID then remove it.
* The prior checks should have been done by findCourseNode() to validate 
* the prog id and course id exist in the system already.
****************************************************************************/
BOOLEAN deleteCourseNode(ProgramTypePtr program, char *courseID)
{
	CourseTypePtr currentCourse;

	/* Used to keep track of the previous node, usually used when inserting 
	into linkedlist to keep track of the previous end points*/
	CourseTypePtr previousCourse = NULL;

/* start point of linked list*/
	currentCourse = program -> headCourse;	
			
	/*finds the node matching the course ID */
	while(currentCourse != NULL && strcmp(currentCourse->data->courseID, \
courseID)!= 0)  
	{
/* need to set the current course(iteration) as the previous before we iterate
to the next node
*Allows to connect the previous node to point to the new node if its needed*/
		previousCourse = currentCourse;
		/* iterate the current course to point to the next node*/
		currentCourse = currentCourse-> nextCourse; 
	}
	
	/* deleting the node attached to the head */
	if(previousCourse == NULL)
	{
/*head now points to the node the to be deleted node pointed to (ptr or null)*/
		program->headCourse = currentCourse->nextCourse; 
		
		free(currentCourse->data);
		free(currentCourse);
		program -> numCourses--;
	}
	else /* deleting course node that has nodes connected on both endpoints */
	{
/* previous node points to the nextnode the to be deleted program points to */
		previousCourse->nextCourse = currentCourse->nextCourse;
	
		free(currentCourse->data);
		free(currentCourse);
		program -> numCourses--;
	}
return FALSE;
}

/****************************************************************************
* Function will traverse the linked list and check if the a programID>courseID
match the prog id and course id passed in 
* returns pointer (checks if they exist) else returns null

* Returns the program pointer that matches the progID of the new course to add
* else it returns null
* used during init to insert courses and used to delete programs


* Function will accept the program(pointer) found by findProgram()
* It will iterate the program and verify whether the course can be found
* returns NULL if their is no match.
****************************************************************************/
CourseTypePtr findCourse(ProgramTypePtr program, char *courseID)
{
 /*iterate inside the program node and check if the course ID exists */
	CourseTypePtr currentCourseNode;
	
	currentCourseNode = program->headCourse;
	while(currentCourseNode != NULL)
	{
		if(strcmp(courseID, currentCourseNode->data->courseID)== 0)
		{
			return currentCourseNode;
		}
		currentCourseNode = currentCourseNode->nextCourse;
	}
/*Returns null if the course cannot be found in the program poniter(node) 
passed in*/
	return NULL;
}


/****************************************************************************
* Function will free the course that was created partially but hasnt been 
* added to the linked list yet.
* Called by validateCourseData() pms_utility.c, when 1 of the data fields 
* is invalid
****************************************************************************/
void removeTempCourse(CourseTypePtr newCourse)
{
    free(newCourse);
}








