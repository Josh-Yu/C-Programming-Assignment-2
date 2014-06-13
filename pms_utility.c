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
* Function readRestOfLine() is used for buffer clearing. 
* Please refer to "test_fgets.c" on Blackboard: 
* "Course Documents"->"Function Examples"->"Input Validation Examples" 
****************************************************************************/
void readRestOfLine()
{
   int c;
   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}

/****************************************************************************
* Initialises the system to a safe empty state.
****************************************************************************/
BOOLEAN systemInit(PMSType* pms)
{
	pms->headProgram = NULL;
	pms->numPrograms = 0; /* intial size of linkedlist*/
   	return TRUE;
}

/****************************************************************************
* Loads all data into the system.
****************************************************************************/
BOOLEAN loadData(PMSType* pms, char* programFile, char* courseFile)
{
FILE *fh;
char programBuffer[ID_LEN + PROG_TYPE_LEN + MAX_TITLE_LEN + MAX_TITLE_LEN \
+ PROG_CODE_LEN + MAX_PROG_DURATION + MODE_LEN + MAX_DESC_LEN \
+ MAX_DESC_LEN + EXTRA_SPACES];
int counter = 0;
char *token;
char *delimiter = "|";


char courseBuffer[COURSE_ID_LEN + PROG_ID_LEN + MAX_TITLE_LEN \
+ COURSE_CODE_LEN + MAX_CREDIT_LEN + MAX_SEMESTER_LEN + MAX_YEAR_LEN \
+ MAX_COORDINATOR_LEN  + MAX_DESC_LEN + EXTRA_SPACES];

/* variables used for processing teachperiod string */
char *teachPeriodLine;
char *teachPeriodToken;
int teachColumn;
char *teachPeriodDelimiter = ", ";

/* Declare program struct type pointers, currently not pointing to 
  *any structs of type program*/
ProgramTypePtr newProgram, programMatched;
CourseTypePtr  newCourse;

/* opening file for opening */
fh = fopen(programFile, "r"); 
if(fh == NULL)
{
    printf("ERROR- Cannot open Program File)\n");
    return FALSE;
}
while(!feof(fh))
{
   if(fgets(programBuffer, ID_LEN + PROG_TYPE_LEN + MAX_TITLE_LEN \
+ MAX_TITLE_LEN + PROG_CODE_LEN + MAX_PROG_DURATION + MODE_LEN \
+ MAX_DESC_LEN + MAX_DESC_LEN + EXTRA_SPACES, fh))
   {
    
     /* check if the line has enough delimiters */
        if(checkProgFieldNum(programBuffer))
        {
        printf("Data corruption in %s, field/delimiters count\n", programFile);
        return FALSE;
        }
        /*get the first token */
        token = strtok(programBuffer, "|");
    
    /* method call to pms_program to create and empty node and data 
     * struct(malloc)*/
        newProgram = createPNode();

        /* reset the counter back */
        counter = 0;
        /* loops through the delimiters colums 
        and assign the value to the empty struct variables via references in 
        the validation function*/
    while(token != NULL)
    {
        switch(counter)
        {
         case PROGID_FIELD:
            if(!validateProgramData(PROGID_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
         case PROG_TYPE_FIELD:
            if(!validateProgramData(PROG_TYPE_FIELD,token,newProgram,pms))
                return FALSE;

            break;
        
         case PROG_TITLE_FIELD:
            if(!validateProgramData(PROG_TITLE_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
         case PROG_MAJOR_FIELD:
            if(!validateProgramData(PROG_MAJOR_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
        
         case PROG_CODE_FIELD:
            if(!validateProgramData(PROG_CODE_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
        
         case PROG_DURATION_FIELD:
            if(!validateProgramData(PROG_DURATION_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
        
         case PROG_MODE_FIELD:
            if(!validateProgramData(PROG_MODE_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
         case PROG_DESCRIPTION_FIELD:
         if(!validateProgramData(PROG_DESCRIPTION_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        
        
         case MAJOR_DESCRIPTION_FIELD:
         if(!validateProgramData(MAJOR_DESCRIPTION_FIELD,token,newProgram,pms))
                return FALSE;
            break;
        }/* End of case/switch statement*/
        
     token = strtok(NULL, delimiter);
     counter++;
    } /* end inner while*/
        
    addToProgList(pms, newProgram); 
    
   } /* end if fgets*/
}
fclose(fh);

/* opening coursefile for opening */
fh = fopen(courseFile, "r");
if (fh == NULL)
{
	printf("ERROR- Cannot open course File)\n");
    
	return FALSE;
}
while(!feof(fh)) 
{
    if(fgets(courseBuffer, COURSE_ID_LEN + PROG_ID_LEN + MAX_TITLE_LEN \
+ COURSE_CODE_LEN + MAX_CREDIT_LEN + MAX_SEMESTER_LEN + MAX_YEAR_LEN \
+ MAX_COORDINATOR_LEN  + MAX_DESC_LEN + EXTRA_SPACES, fh))
    {
       /* check if the line has enough delimiters */
       if(checkCourseFieldNum(courseBuffer))
       {
        printf("Data corruption in %s, field/delimiters count\n", courseFile);
        systemFree(pms);
        return FALSE;
       }
        /*get the first token */
        token = strtok(courseBuffer, "|");
        
        newCourse =  createCourseNode();
    
        /* reset the counter back */
        counter = 0;
        /* loops through the delimiters and assign the value to the empty 
         * struct variables via references */
        while(token != NULL)
        {
         switch(counter)
         {
          case COURSEID_FIELD: 
          if(!checkStringLength(token,COURSE_ID_LEN,COURSE_ID_LEN ))
          {
            printf("COURSE ID FIELD- malformed character length\n");
            return FALSE;
          }else{
                strcpy(newCourse -> data -> courseID, token);
          }
          break;

          case COURSE_PROGID_FIELD:
            if(!validateCourseData(COURSE_PROGID_FIELD,token,newCourse,\
            programMatched,pms))
                return FALSE;

            break;
            
            
          case COURSE_TITLE_FIELD:
            if(!validateCourseData(COURSE_TITLE_FIELD,token,newCourse,\
            programMatched,pms))
            return FALSE;

            break;
            
          case COURSE_CODE_FIELD:
            if(!validateCourseData(COURSE_CODE_FIELD,token,newCourse,\
            programMatched,pms))
            return FALSE;
            
            break;
            
            
          case COURSE_CREDIT_POINT_FIELD:
            if(!validateCourseData(COURSE_CREDIT_POINT_FIELD,\
            token,newCourse,programMatched,pms))
            return FALSE;
            
            break;
            
            
          case COURSE_TEACH_PERIOD:
            teachPeriodLine = token;
            break;
            
            
          case COURSE_COORDINATOR_FIELD:
            if(!validateCourseData(COURSE_COORDINATOR_FIELD,token,\
            newCourse,programMatched,pms))
            return FALSE;
            
            break;
            

          case COURSE_DESCRIPTION_FIELD:
            if(!validateCourseData(COURSE_DESCRIPTION_FIELD,token,newCourse,\
            programMatched,pms))
            return FALSE;
            break;
         }

            token = strtok(NULL, delimiter);
            counter++;
        } /* end inner while*/

                
      /* Process the teach period token outside the 
        strtok because cant perform another strok inside another strtok*/
        teachColumn = 1;
        teachPeriodToken = strtok(teachPeriodLine,teachPeriodDelimiter);
        while(teachPeriodToken != NULL)
        {
            if(teachColumn == 2)
            {
                if(!validateCourseData(COURSE_TEACH_SEMESTER,teachPeriodToken,\
                newCourse,programMatched,pms)){
                return FALSE;
                }
            }
        
            if(teachColumn == 3) 
            {
                if(!validateCourseData(COURSE_TEACH_YEAR,teachPeriodToken,\
                newCourse,programMatched,pms)){
                    return FALSE;
                }
            }
            teachColumn++;
            teachPeriodToken = strtok(NULL,teachPeriodDelimiter);
		}

        /*finds the program to insert the course into */
        programMatched = findProgram(pms, newCourse->data->progID);
        if(programMatched != NULL)
        {
            /*check if the program already has the same course code inside it*/
            if(findCourse(programMatched,newCourse->data->courseID) == NULL)
            {
				printf("Adding Course %s to list\n",newCourse->data->courseID);
				/* insert the node into the program in the linkedlist*/
                addToCourseList(pms, programMatched, newCourse);
            }else{
                printf("Course ID %s already exist in \
the program node you are adding to\n",newCourse->data->courseID);
                removeTempCourse(newCourse);
                return FALSE;
            }
        }else if(programMatched == NULL){
            printf("Unable to find program in system to \
insert/associate course\n");
            removeTempCourse(newCourse);
            return FALSE;
        }
	} /*end fgets */
}/* End while loop*/
    fclose(fh);

  return TRUE;
} /*end load Data  function*/


/****************************************************************************
* Check if the correct number of delimters are in the program file per line
* check if the line does not have too little or too many delimiters
****************************************************************************/
BOOLEAN checkProgFieldNum(char *string)
{
 BOOLEAN status = FALSE;
 int i;
 int delimiterCount =0;
 for(i = 0; i <strlen(string); i++)
 {
    if(string[i] == '|')
        delimiterCount++;
 }
    if(delimiterCount > 9)
    {
        printf("Too many data Fields in .dat file.\n Terminating Program\n");
        status = TRUE;
    }
    if(delimiterCount < 8)
    {
        printf("Not enough data fields detected in .dat file\n");
        status = TRUE;
    }
return status;
}

/****************************************************************************
* Check if the correct number of delimters are in the course file per line
* check if the line does not have too little or too many delimiters
****************************************************************************/
BOOLEAN checkCourseFieldNum(char *string)
{
 BOOLEAN status = FALSE;
 int i;
 int delimiterCount =0;
 for(i = 0; i <strlen(string); i++)
 {
    if(string[i] == '|')
        delimiterCount++;
 }
 printf("Delimiter Count is: %d\n",delimiterCount );
    if(delimiterCount > 7)
    {
        printf("Too many data Fields in .dat file.\n Terminating Program\n");
        status = TRUE;
    }
    if(delimiterCount < 7)
    {
        printf("Not enough data fields detected in .dat file\n");
        status = TRUE;
    }
return status;
}

/****************************************************************************
*Check if the data for program are correct and valid to be placed in the system
* If the values are correct then the data will be assigned
****************************************************************************/
BOOLEAN validateProgramData(int type, char *token, ProgramTypePtr newProgram,\
PMSType* pms)
{
int errorFound = 0; /* used for cases where multiple checks are needed */
int tempNumber; /* used for numerical checks */
switch(type)
{
    case PROGID_FIELD:
        if(!checkStringLength(token,PROG_ID_LEN,PROG_ID_LEN))
        {
         errorFound++;
         printf("PROGRAM ID ERROR - The characters are not within ranges\n");
        }
            /* validate whether the program code already exists*/
        else if(findProgram(pms,token) != NULL)
        {
         errorFound++;
         printf("Program ID ERROR - ID: %s exist in system already\n",token);
        }
        if(errorFound > 0)
        {
         removeTempProgram(newProgram);
         return FALSE;
        }else{
            strcpy(newProgram -> data -> progID, token);
        }
        break;

    case PROG_TYPE_FIELD:
        if(strcmp(token,"UG") == 0 || strcmp(token,"PG") == 0){
        strcpy(newProgram -> data -> progType,token);
        }
        else{
            printf("Program TYPE FIELD ERROR - Field Data: %s not \
'UG'or 'PG'\n", token);
            removeTempProgram(newProgram);
            return FALSE;
			}
		break;

	case PROG_TITLE_FIELD:
			if(checkStringLength(token,MIN_TITLE_LEN,MAX_TITLE_LEN))
			{
                strcpy(newProgram -> data -> progTitle,token);
			}else{
                printf("PROGRAM TITLE ERROR - The characters are not within \
ranges\n");
				removeTempProgram(newProgram);
				return FALSE;
			}
		break;
		
	case PROG_MAJOR_FIELD:
			if(checkStringLength(token,MIN_TITLE_LEN,MAX_TITLE_LEN))
			{		
				strcpy(newProgram -> data -> progMajor,token);
			}
			else{
                printf("Program MAJOR FIELD ERROR - The characters are not \
within ranges\n");
				removeTempProgram(newProgram);
				return FALSE;
			}
		break;
		
	case PROG_CODE_FIELD:
		if(checkStringLength(token,PROG_CODE_LEN,PROG_CODE_LEN))
		{
			strcpy(newProgram -> data -> progCode,token);
		}else
		{
			printf("Program CODE FIELD ERROR - 5 characters required\n");
			removeTempProgram(newProgram);
			return FALSE;
		}
		break;


	case PROG_DURATION_FIELD:
		tempNumber = atof(token);
		if(tempNumber == 0.00)
		{
			errorFound++;
			printf("Program DURATION FIELD ERROR - \n");
		}else if(tempNumber < 1 || tempNumber > 10)
		{
			errorFound++;
			printf("Program DURATION FIELD ERROR - Range 1-10\n");
		}
		if(errorFound > 0){
			removeTempProgram(newProgram);
			return FALSE;
		}else
			newProgram -> data -> progDuration = atof(token);

		break;


	case PROG_MODE_FIELD:
		if(strcmp(token,"FT") == 0 || strcmp(token,"PT") == 0){
				strcpy(newProgram -> data -> progMode,token);
			}
			else{
				printf("Program MODE FIELD ERROR - Field Data: not \
'FT'or 'PT'\n");
				removeTempProgram(newProgram);
				return FALSE;
			}
		break;

	case PROG_DESCRIPTION_FIELD:
		if(checkStringLength(token,MIN_DESC_LEN,MAX_DESC_LEN))
			{		
				strcpy(newProgram -> data -> progDescription,token);
			}
			else{
				printf("Program DESCRIPTION FIELD ERROR - The \
characters are not within ranges\n");
				removeTempProgram(newProgram);
				return FALSE;
			}

		break;

	case MAJOR_DESCRIPTION_FIELD: 
		if(checkStringLength(token,MIN_DESC_LEN,MAX_DESC_LEN))
		{
        /* - Comented code creates buffer issues when writing to 
        file, not sure why
        printf(">>>>>Major Description token is %s|<<<<\n", token);
        printf("THe string length of Major Description is %d\n", \
        strlen(token));
        if (token[strlen(token)] == '\0')
        {
            printf("Adding Newline char\n");
            token[strlen(token)] = '\n';
        }
        printf("AFTER NEW LINE CHAR Major Description is %s|<\n", \
        token);
        */
        
            strcpy(newProgram -> data -> majorDescription,token);
		}
		else{
			printf("Program MAJOR FIELD ERROR - The characters are \
not within ranges\n");
			removeTempProgram(newProgram);
			return FALSE;
		}

		break;
	}
return TRUE;
}
/****************************************************************************
 Checks if the string length is the correct size
 Return true if the char is correct range ELSE return false 
****************************************************************************/
BOOLEAN checkStringLength(char* string, int charMin, int charMax)
{
if(string[0] != '\n')
{
	if(strlen(string) > charMax)
	{
		printf("String is too long\n");
		return FALSE;
	}else if(strlen(string) < charMin)
	{
		printf("String to short\n");
		return FALSE;
	}
}else{
return FALSE;
}
	
return TRUE;

}


/****************************************************************************
* Check if the data for courses are correct and valid to be placed in the system
* If the values are correct then the data will be assigned
****************************************************************************/
BOOLEAN validateCourseData(int type, char *token, CourseTypePtr \
newCourse, ProgramTypePtr programFound, PMSType *pms)
{
int errorFound =0;
int tempNumber;
switch(type)
	{
	case COURSEID_FIELD:
    if(!checkStringLength(token,COURSE_ID_LEN,COURSE_ID_LEN))
    {
        errorFound++;
        printf("Course ID Error: Characters are not within range\n");
    }
    else if(findCourse(programFound,token) != NULL)
    {
        errorFound++;
        printf("Course ID already exist inside the current Program you \
are adding to\n");
    }
    if(errorFound > 0){
    removeTempCourse(newCourse);
    return FALSE;
    }else{
    strcpy(newCourse -> data -> courseID, token);
    }
	break;

	case COURSE_PROGID_FIELD:
    if(!checkStringLength(token,PROG_ID_LEN,PROG_ID_LEN))
    {
        errorFound++;
        printf("Prog ID Error: Characters are not within range\n");
    }else if(findProgram(pms,token) == NULL)
    {
        errorFound++;
        printf("Program ID: %s not found in the system\n", token);
    }
    if(errorFound > 0)
    {
        removeTempCourse(newCourse);
        return FALSE;
    }else{
        strcpy(newCourse -> data -> progID,token);
    }
	break;

	case COURSE_TITLE_FIELD:
    if(checkStringLength(token,MIN_TITLE_LEN,MAX_TITLE_LEN))
    {
        strcpy(newCourse -> data -> courseTitle,token);
    }else{
    printf("Course Title Error - Characters not within range\n");
    removeTempCourse(newCourse);
    return FALSE;
    }
	break;

    case COURSE_CODE_FIELD:
    if(checkStringLength(token,COURSE_CODE_LEN,COURSE_CODE_LEN))
    {
        strcpy(newCourse -> data -> courseCode,token);
    }else
    {
        printf("Couse CODE FIELD ERROR - 5 characters required\n");
        removeTempCourse(newCourse);
			return FALSE;
		}
	break;

	case COURSE_CREDIT_POINT_FIELD:
    tempNumber = atoi(token);
    if(tempNumber == 0)
    {
        errorFound++;
        printf("Course Credit Point format Error\n");
    }else if(tempNumber < MIN_CREDIT_POINT_RANGE ||tempNumber > \
    MAX_CREDIT_POINT_MAX_RANGE)
    {
    errorFound++;
    printf("Course CreditPoint Error- range 1-48");
    }
    if(errorFound > 0)
    {
    removeTempCourse(newCourse);
    return FALSE;
    }else{
    newCourse->data->creditPoints = atoi(token);
    }
	break;

	case COURSE_TEACH_PERIOD:
    /* TeachPeriod Info - Case is redudant for userInput due to strtok not 
    being able to be used while already performing strtok
        Validation for teach period is done by other cases below*/
	break;

	case COURSE_COORDINATOR_FIELD:
        if(checkStringLength(token,MIN_COORDINATOR_LEN,MAX_COORDINATOR_LEN))
        {
			strcpy(newCourse -> data -> courseCoordinator,token);
        }
	else{
        printf("Course Co-ordinator FIELD ERROR - The characters are not \
within ranges\n");
		removeTempCourse(newCourse);
		return FALSE;
		}
	break;

	case COURSE_DESCRIPTION_FIELD:
	if(checkStringLength(token,MIN_DESC_LEN,MAX_DESC_LEN))
	{
        strcpy(newCourse -> data -> courseDescription,token);
	}
	else{
        printf("Course Description FIELD ERROR - The characters are not \
within ranges\n");
		removeTempCourse(newCourse);
		return FALSE;
		}
	
	break;

	case COURSE_TEACH_SEMESTER:
    tempNumber = atoi(token);
    
    if(tempNumber == 0)
    {
        errorFound++;
        printf("Semester Number invalid\n");
    }else if(tempNumber < 1 || tempNumber > 2)
    {
        errorFound++;
        printf("Semester Number Not 1 OR 2\n");
        }
    if(errorFound > 0)
    {
        removeTempCourse(newCourse);
        return FALSE;
    }else{
        newCourse->data->teachPeriods[0].semester = tempNumber;
    }
	break;
	
	case COURSE_TEACH_YEAR:
    tempNumber = atoi(token);
    if(tempNumber == 0)
    {
        errorFound++;
        printf("Year is invalid\n");
    }else if(tempNumber < MIN_COURSE_YEAR_YEAR || tempNumber > \
    MAX_COURSE_TEACH_YEAR)
    {
    errorFound++;
    printf("Year Range is invalid\n");
    }
    if(errorFound > 0)
    {
        removeTempCourse(newCourse);
    }else{
        newCourse->data->teachPeriods[0].year = tempNumber;
    }
    break;

    }
return TRUE;
}



/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(PMSType* pms)
{
ProgramTypePtr currentProgram, nextProgram;
/* start point of linked list*/
	currentProgram = pms->headProgram;	
			
	while(currentProgram != NULL)  
	{
	nextProgram = currentProgram->nextProgram;
		/*call function to remove all courses in a given program pointer */
		bulkDeleteCourses(currentProgram);
		free(currentProgram->data);
		free(currentProgram);
        /* iterate the current program to point to the next node*/
		currentProgram = nextProgram; 
	}
	printf("Finish freeing memory\n");
}

/****************************************************************************
* Shows menu of the program
****************************************************************************/
void menu(PMSType* pms, char* programFile, char* courseFile)
{
int choice;
char* endPtr;
/*Holds the char array of user selections via menu */
char userInput[MAX_OPTION_INPUT + EXTRA_SPACES];

do{
	printf("Main Menu\n");
	printf("1) Summary of Undergrad Programs\n");
	printf("2) Summary of Postgrad Programs\n");
	printf("3) Detailed Program Report\n");
	printf("4) Add Program\n");
	printf("5) Delete Program\n");
	printf("6) Add Course\n");
	printf("7) Delete Course\n");
	printf("8) Save & Exit\n");
	printf("9) Abort\n");
		
	printf("\n Select your option (1-9)\n");
	getUserInput(MAX_OPTION_INPUT+ EXTRA_SPACES,userInput);

		/* Convert char to string */
		choice = (int) strtol(userInput, &endPtr, 10);
		switch(choice)
		{
			case 1:
			displaySummary(pms,"UG");
			break;

			case 2:
			displaySummary(pms,"PG");
			break;

			case 3:
			programReport(pms);
			break;

			case 4:
			addProgram(pms);
			break;

			case 5:
			deleteProgram(pms);
			break;

			case 6:
			addCourse(pms);
			break;

			case 7:
			deleteCourse(pms);
			break;

			case 8:
			saveData(pms, programFile, courseFile);
			return;

			case 9:
			/* abort function to free all structs */
			break;
	
			default:
			printf("Input does not match any of the options\n");
			break;

		}/* Close switch statement*/
	}while(choice!= 9);
}/* close menu() method*/


/* Function code has been referenced from 'getInteger-advanced.c' 
 * file that is on blackboard
 * Does basic buffer check*/
BOOLEAN getUserInput(int charLimit, char array[])
{
int inputValid = FALSE;

	do{
	inputValid = FALSE;
	
	fgets(array, charLimit, stdin);
	
	/* Checks if the user has entered a space  */
	if(array[0] == '\n')
	{
		return TRUE;
	}
    else /* Checks if the char length is witin the array container size*/
	{
    /* Checks if the last index was an \n to signify it was 1 character 
     * and not too long
   If the user input did not have \n, it means it was too long for the buffer*/

	if (array[strlen(array) - 1] != '\n')
	{
		/*printf("(DEBUG - Last character does not have \\n \n"); */
		printf("Input buffer overflow- Clearing buffer\n");
		printf("Re-enter Input, too many characters previously entered\n");
		readRestOfLine();
		inputValid = FALSE;
	}
	else
		{
            /* String length was ok. Replacing \n with \0 */
            /*printf("DEBUG-String Length is okay, replace \\n with \\0\n");*/
		array[strlen(array) - 1] = '\0';
		inputValid = TRUE;
		}
	}

	/* cases where no integer range check needed */
	}while(!inputValid);
	return FALSE;
}



/****************************************************************************
* Function generates a unique program ID for new programs to add
*
****************************************************************************/
void generateProgID(PMSType *pms, char * generateProgID)
{

BOOLEAN progIDExists = FALSE;
int programID = 1;
ProgramTypePtr currentProgramNode;


do{
    sprintf(generateProgID,"%c%04u",'P',programID);
    currentProgramNode = pms-> headProgram;

    while(currentProgramNode != NULL)
    {
        if(strcmp(currentProgramNode->data->progID,generateProgID) == 0)
        {
            progIDExists = TRUE;
            programID++;
            sprintf(generateProgID,"%c%04u",'P',programID);
            break;
        }
        progIDExists = FALSE;
        currentProgramNode = currentProgramNode->nextProgram;
    }

}while(progIDExists);
}


/****************************************************************************
* Function generates a unique course ID for new courses to add
*
****************************************************************************/
void generateCourseID(ProgramTypePtr program, char * generateCourseID)
{

/*Searches the program node and checks if the CourseID exist or not */
int courseID = 1;
BOOLEAN courseIDExists = FALSE;


do{
    sprintf(generateCourseID,"%c%04u",'C',courseID);
    if(findCourse(program, generateCourseID))
    {
        courseIDExists = TRUE;
        courseID++;
        sprintf(generateCourseID,"%c%04u",'C',courseID);
    }
    else{
        courseIDExists = FALSE;
    }
}while(courseIDExists);
}

/****************************************************************************
* Function will write the system program information to file
* used by save & abort option

****************************************************************************/
BOOLEAN writeProgramFile(PMSType* pms, char *programFile)
{
FILE* fp = NULL;
ProgramTypePtr currentProgram;

fp = fopen(programFile, "w");
currentProgram = pms->headProgram;

/* traversing the linked list & look for progType match*/
    while(pms->headProgram != NULL && currentProgram != NULL)
    {
    fprintf(fp,"%s",currentProgram->data->progID); /*ProgID */
    fprintf(fp,"|%s",currentProgram->data->progType); /*Prog Type */
    fprintf(fp,"|%s",currentProgram->data->progTitle); /*Prog Title */
    fprintf(fp,"|%s",currentProgram->data->progMajor); /*Major */
    fprintf(fp,"|%s",currentProgram->data->progCode); /*Code */
    fprintf(fp,"|%.0f",currentProgram->data->progDuration); /*Duration */
    fprintf(fp,"|%s",currentProgram->data->progMode); /*Mode */
    fprintf(fp,"|%s",currentProgram->data->progDescription);/*ProgDescription*/
    fprintf(fp,"|%s",currentProgram->data->majorDescription);/*MajDescription*/
    /*the current node now points to the next node for the next iternation */
		currentProgram = currentProgram-> nextProgram;
    }/* end outer while */

    printf("Finished writing Program File\n");

fclose(fp);

return FALSE;
}


/****************************************************************************
* Function will write the system course information to file
* used by save & abort option
* called by saveData() in pms_options.c
****************************************************************************/
BOOLEAN writeCourseFile(PMSType *pms, char *courseFile)
{
ProgramTypePtr currentProgram;
CourseTypePtr currentCourse;
FILE* fp = NULL;

fp = fopen(courseFile, "w"); 

if(fp == NULL)
{
printf("Error writing course file: %s", courseFile);
return FALSE;
}
currentProgram = pms->headProgram;

/* traversing the program nodes in the linked list */
	while(pms->headProgram != NULL && currentProgram != NULL)
	{
        /*Iterate through each course that resides inside the current program*/
		currentCourse = currentProgram->headCourse;
		if(currentCourse != NULL)
		{
			while(currentCourse != NULL)
			{
            fprintf(fp,"%s",currentCourse->data->courseID);
            fprintf(fp,"|%s",currentProgram->data->progID);
            fprintf(fp,"|%s",currentCourse->data->courseTitle);
            fprintf(fp,"|%s",currentCourse->data->courseCode);
            fprintf(fp,"|%d",currentCourse->data->creditPoints);
            fprintf(fp,"|Semester %d, %d",\
            currentCourse->data->teachPeriods[0].semester,\
            currentCourse->data->teachPeriods[0].year);
            fprintf(fp,"|%s",currentCourse->data->courseCoordinator);
            fprintf(fp,"|%s",currentCourse->data->courseDescription);
            currentCourse = currentCourse-> nextCourse;
            }
		}
       /*the current node now points to the next node for the next iternation*/
		currentProgram = currentProgram-> nextProgram;
	}/* end outer while */

	printf("Finished writing Course FILE\n");
fclose(fp);
return FALSE;
}


/****************************************************************************
* Creates detailed report for program code and program pointer passed in
* Pass in proID for file name and pointer to the program found.
*
* used for Menu option #3: Detailed Program Report
* called by programReport() in pms_options.c
****************************************************************************/
BOOLEAN writeProgramReport(char *inputProgID,ProgramTypePtr programFound)
{
	char extension[] = ".report";
	CourseTypePtr currentCourse;
	FILE* fp = NULL;
	char *fileName = strcat(inputProgID,extension);
	
	fp = fopen(fileName, "w");
	if(fp == NULL)
	{
		printf("Error writing/creating program file: %s", fileName);
		return FALSE;
	}
        fprintf(fp,"%-5s - %-35s\n",programFound-> data -> progID,\
        programFound-> data -> progTitle);
		fprintf(fp,"%-7s(%s)  - Detailed Report\n","",\
        programFound-> data -> progMajor);
		fprintf(fp,"--------------------------------------------------------\
-------------\n");
	
		/* Iterate through courses inside the specific program and write 
         * each course to the file 
		 * Also, first check if the specified program has any courses first*/
		currentCourse = programFound-> headCourse;
		if(currentCourse != NULL)
		{
			while(programFound -> headCourse != NULL && currentCourse != NULL)
			{
           fprintf(fp,"%-15s: %s\n","Course ID",currentCourse->data->courseID);
            fprintf(fp,"%-15s: %s\n","Course Title",\
            currentCourse->data->courseTitle);
            fprintf(fp,"%-15s: %d\n","Credit Points",\
            currentCourse->data->creditPoints);
            fprintf(fp,"%-16s: Semester %d, %d\n","Teaching Period",\
            currentCourse->data->teachPeriods[0].semester,\
            currentCourse->data->teachPeriods[0].year);
            fprintf(fp,"%-12s: %s\n","Description",\
            currentCourse->data->courseDescription);
            currentCourse = currentCourse-> nextCourse;
            printf("\n");
            }
        }
        printf("File %s has been created.\n", fileName);
        fclose(fp);
return TRUE;
}




