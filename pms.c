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

int main(int argc, char* argv[])
{
/* create an instance of pms (struct)
 * then passing the reference to the functions*/
    PMSType pms;

    int initFlag, dataFlag;
	
	
	/* Test and see if the number of arguments is correct*/
	if(argc < 3 || argc > 3)
	{
		printf("USAGE: ./pms program.dat course.dat\n");
		exit(EXIT_FAILURE); 
	}
	
    /* Initialise the program management system to a safe empty state. */
    initFlag = systemInit(&pms);

    /*Populate the program management system with data from the data files. 
      Uncomment this line when you are ready to use command line 
      arguments: */
       dataFlag = loadData(&pms, argv[1], argv[2]);  

    
    if (initFlag == FAILURE || dataFlag == FAILURE){
		if(dataFlag == FAILURE)
		{
			systemFree(&pms);
		}
        exit(EXIT_FAILURE); 
    }
    /* Interactive menu providing user with access to the 9 menu options */
	menu(&pms,argv[1], argv[2]);

    /* Deallocate all dynamically allocated memory. */
    systemFree(&pms);

    exit(EXIT_SUCCESS);
}
