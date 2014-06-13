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

#include "pms_program.h"
#include <ctype.h> /* used for cmp */
/* provide the implementation of functions to manage the pms_program list 
 * data structure here.
 */

 
/****************************************************************************
* Function cmp() is used for comparing titles for programs and courses. 
* compares which of the titles alphabetically comes before the other
* 
****************************************************************************/
int cmp(char* string1, char* string2)
{

	int result = -5;

	result = strcmp(string1, string2);
/*
printf("\nCurrent NODE: %s COMPARE New NODE: %s\n",string1,string2);
*/

	if(result == 0)
	{
		/*printf("Strings are Equal\n"); */
		result = 0;
	}
	else if(result < 0)
	{
		/*printf("1ST string %s is SMALLER\n", string2);*/
		result = 0;
	}
	else if(result> 0)
	{
		/*printf("1ST string %s is LARGER\n", string1);*/
		result = 1;
	}
	return result;
}

/****************************************************************************
* Create program Node and the data struct inside the node
* Returns the pointer to the Node
****************************************************************************/
ProgramTypePtr createPNode()
{
	ProgramTypePtr newProgram;

/* ###############CREATING NEW NODE ##############*/
	
/* Allocating space for the node*/
	newProgram = malloc(sizeof(ProgramType));
			
	
/*Allocating the space for the program data */
/* dereference the pointer(newProgram) to assign data to point to 
new allocated space for struct program_data
*/
	newProgram -> data = malloc(sizeof(struct program_data));
		
/* Default, new program stucts point to null*/
	newProgram -> nextProgram = NULL;
/* ###############END CREATING NEW NODE ##############*/

return newProgram;
}


/****************************************************************************
* Add node to the linked list
****************************************************************************/ 
BOOLEAN addToProgList(PMSType *pms, ProgramType *newProgram)
{
	ProgramTypePtr previousProgram, currentProgram;

		/*IF the the head is pointing to NULL then the linked list is empty 
		  make the headpointer point to the first node
		*/
		if(pms->headProgram == NULL)
		{
			/* head now points to new node*/
			pms->headProgram = newProgram;
			
		}
		else /* Enter the else when nodes exist in the linked list already*/
		{
		/*#############  LOCATING WHERE TO INSERT NODE ################## */
	
		/* ALWAYS NEED A NODE TO START FROM, HENCE CURRENT NODE STARTS FROM 
		HEAD PROGRAM*/
		/* tempvariable to keep track where to start iterating from 
		in the linked list
		Also serves to keep track where im currently at in the linked list*/
		currentProgram = pms -> headProgram;
	
		/* loop used to traverse the linked list to determine the node to be 
		stationed at to start insertion
		*/

		/* while the current node is not pointing to NULL, i havent 
		reached the end, keep going*/
		/* The .... node stops when the next node title is  < >.... */
			
		/* Used to keep track of the previous node, usually used when 
		inserting into linkedlist to keep track of the previous end points*/
			previousProgram = NULL;

			
			while(currentProgram != NULL && \
cmp(newProgram->data->progTitle, currentProgram->data->progTitle))  
			{
				/* need to set the current program(iteration) as the previous 
				before we iterate to the next node
				 * Allows me to connect the previous node to point to the 
				 new node if its needed*/
				previousProgram = currentProgram;
				/* iterate the current program to point to the next node*/
				currentProgram = currentProgram-> nextProgram; 
			}


	
			/*########### INSERTING THE DATA ################# */
		
			if(previousProgram == NULL)
			{
/*printf("New created Node ProgramID: %s %s now points to old \node %s %s\n",\
newProgram->data-> progID,newProgram->data->progTitle, \
pms->headProgram->data->progID,pms->headProgram->data->progTitle); */

/*point the newprogram to the old pointer that previously 
connected to the head*/
				newProgram->nextProgram = pms->headProgram; 
/* head now points to the new node made  */
				pms->headProgram = newProgram; 
				
				/*
printf("Head of list now pointing to %s\n", pms->headProgram->data->progID);
printf("%s\n", pms->headProgram->data->progTitle);
*/
			}
			else /* Middle Insertion  */
			{
				newProgram->nextProgram = currentProgram;
			
/*printf("Previous Node %s now points to %s\n",previousProgram->data->progID,\
newProgram->data-> progID);*/

				previousProgram->nextProgram = newProgram;	
			}

		} /* end ELSE*/ 
		pms->numPrograms++;

return TRUE;
}

/****************************************************************************
* Finds program and returns pointer
* Returns the program pointer that matches the progID of the new course to add
* else it returns null
* used by functions to search for a program in the linklist by prog ID
****************************************************************************/
ProgramTypePtr findProgram(PMSType *pms, char *programID )
{
	ProgramTypePtr currentProgramNode;
	currentProgramNode = pms->headProgram;
	
	while(currentProgramNode != NULL)
	{
		if(strcmp(currentProgramNode->data->progID, programID) == 0)
		{
			return currentProgramNode;
		}
		currentProgramNode = currentProgramNode->nextProgram;
	}
	/*printf("Program ID %s not found - DEBUG PMS_PROGRAM.C \n",programID);*/
return NULL;
}


/****************************************************************************
* Function will traverse the linklist and delete the program associated with
* the ID passed in and also clear all the courses the program contains.
* 
* 
****************************************************************************/
BOOLEAN deleteProgramNode(PMSType *pms, char *programID)
{
	ProgramTypePtr currentProgram;

/* Used to keep track of the previous node, usually used when inserting into
 linkedlist to keep track of the previous end points*/
	ProgramTypePtr previousProgram = NULL;
	
	/* start point of linked list*/
	currentProgram = pms->headProgram;
	
	while(currentProgram != NULL && \
strcmp(currentProgram->data->progID, programID)!= 0)  
	{
	/* need to set the current program(iteration) as the previous before we
		iterate to the next node
		 * Allows me to connect the previous node to 
		 point to the new node if its needed*/
		previousProgram = currentProgram;
		/* iterate the current program to point to the next node*/
		currentProgram = currentProgram-> nextProgram; 
	}
	

		/* deleting the node attached to the head */
	if(previousProgram == NULL)
	{
/*head now points to the node the to be deleted node pointed to (ptr or null)*/
		pms->headProgram = currentProgram->nextProgram; 
		bulkDeleteCourses(currentProgram);
		free(currentProgram->data);
		free(currentProgram);
	}
	else /* deleting program node that has nodes connected on both endpoints */
	{
	/*previous node point to the nextnode the to be deleted program points to*/
		previousProgram->nextProgram = currentProgram->nextProgram;
		
		/*call function to remove all courses in a given program pointer */
		bulkDeleteCourses(currentProgram);
		
		free(currentProgram->data);
		free(currentProgram);
			}
return FALSE;
}


/****************************************************************************
* Function will traverse the program node(given via pointer) and
* loop and remove all the courses inside the node in bulk
* 
****************************************************************************/
BOOLEAN bulkDeleteCourses(ProgramTypePtr currentProgram)
{
	CourseTypePtr currentCourse, nextCourse;
	/* delete courses in the program*/
	
	if(currentProgram-> headCourse == NULL)
	{
		return TRUE;
	}
	else /* program to delete still has courses, loop */
	{
		currentCourse = currentProgram->headCourse;
		while(currentCourse != NULL)
		{
			nextCourse = currentCourse->nextCourse;
			free(currentCourse->data);
			free(currentCourse);
			currentCourse = nextCourse;
		}
		return TRUE;
	}
return FALSE;
}

/****************************************************************************
*Function will free the new program node that was created partially but has not
*been added to the linked list yet
*Called by validateProgramData() pms_utility.c, when 1 of the fields is invalid
****************************************************************************/
void removeTempProgram(ProgramTypePtr program)
{
    free(program);
}

