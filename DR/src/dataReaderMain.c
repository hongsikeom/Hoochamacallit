/* ===============================================================================
* FILE : dataReaderMain.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 20,2021
* DESCRIPTION : This file creates the mesage queue and shared memory space to receive
* messages from DCs and processes them. When MasterList does not contain any DCs then
* exits the program.
* ================================================================================*/

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <errno.h>
#include "../../common/inc/loggerHeader.h"
#include "../../common/inc/message_struct.h"
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"



void main(int argc, char *argv[])
{
	int qID = INI_VALUE;       				  // Message queue ID
	int shmID = INI_VALUE;     			      // Shared memory ID
	int msgRun = RUN;     			          // For loop
	int sizeOfData = INI_VALUE;				  // Size of messagea from the DC
	int rc = INI_VALUE;						  // Retrun code from message processing
	int checkProcessID = INI_VALUE;           // Check the process id in the DCProcessIDList
	int checkFlag = 0;					      // Flag to check if a DC message was ever reveiced 
	int indexOfDC = 0;					      // Index of DC

	struct timeval currentTimeStruct;         // Timeval struct
	long startTime = 0;						  // Start time
	long currentTime = 0; 					  // Current time
	MasterList *masterList = NULL;    		  // MasterList struct
	MESSAGECONTENT messageFromDC;             // Messagecontent struct
	DCProcessIDList *dcProcessIDList = NULL;  // DC ProcessIDList (It will hold the ProcessIDs that have been 	
											  // connnected to ther server and left)

	   									
	//Check Message Queue , create if doesn't exist
	qID = createMessageQueue();
	if (qID == FAILED)
	{
		printf("Data Reader can\'t create queue!\n");
		fflush(stdout);
		return;
	}

	// Create Shared Memoery
	shmID = createSharedMemory();
	if (shmID == FAILED)
	{
		printf("Data Reader can\'t create shared memory!\n");
		fflush(stdout);
		return;
	}

	// Attach the MasterList to the shared memory area
	masterList = (MasterList *)shmat(shmID, NULL, 0);
	if (masterList == NULL)
	{
		printf("Data Reader can\'t attach to shared memory!\n");
		alarm(1);
	}
	
	// Set the message queue id and initialize default(0) value
	// to elements in the dc array
	masterList->msgQueueID = qID;
	masterList->numberOfDCs = 0;
	for (int i = 0; i < MAX_DC_ROLES; i++)
	{
		masterList->dc[i].dcProcessID = 0;
		masterList->dc[i].lastTimeHeardFrom = 0;
	}

	sleep(SLEEP_BEFORE_START);  //fix magic number

	// Test output to the console to be removed
	printf("\n============================================");
	printf("\nMessage queue ID is: %d\n", masterList->msgQueueID);
	printf("Shared Memory ID is: %d\n", shmID);
	printf("============================================\n\n");

	// Set start time
	gettimeofday(&currentTimeStruct, NULL);	
	startTime = currentTimeStruct.tv_sec;
	
	
	//Listening messages from DCs
	while (msgRun == RUN)
	{
		if(checkFlag == CHECK_NUM_DC){
			if (masterList->numberOfDCs == 0) 
			{
        		// Put log here

        		printf("Number of DC is zero i'm out of here\n");
        		break;

        	}
		}

		// Check if any of DCs have not sent any messages more than 35 seconds to the DR
		dcProcessIDList = checkLastHeardFrom(masterList, currentTime, dcProcessIDList);

		// Get the current time in seconds
		gettimeofday(&currentTimeStruct, NULL);	
		currentTime = currentTimeStruct.tv_sec;

		// Getting message from the DC
		rc = msgrcv (qID, (void *)&messageFromDC, sizeof(MESSAGECONTENT) - sizeof(long), 0, IPC_NOWAIT);
		if (rc == -1)
		{ 
			// If error is not NO_MESSAGE (any other errors), exit the program
			int errsv = errno;
			if (errsv != NO_MESSAGE) 
			{ 
				break;
			}

	    
			// Sleep 1.5 seconds and continue to the next loop
			usleep(ONE_HALF_SECONDS);
			continue;
		}

		if (checkFlag == 0) 
		{
			checkFlag =CHECK_NUM_DC;
		}

		// Reset the startTime
		gettimeofday(&currentTimeStruct, NULL);
		startTime = currentTimeStruct.tv_sec;

		// Check if the DCs process ID is in the DCProcessIDList (It has already been connected to the DR and left)
		if ((checkProcessID = findDCprocessID(dcProcessIDList, messageFromDC.machinePID)) == FOUND)
		{ 
			
			continue; 
		}

		// If the process ID is not in the master list, update the DC to the master list
		indexOfDC = checkPIDFromMasterList(masterList, messageFromDC.machinePID);
		if (indexOfDC == NOT_FOUND) 
		{
			logDataReader(masterList->numberOfDCs, messageFromDC.machinePID, "added to the master list", messageFromDC.message_code, messageFromDC.msgDescription, 0);
			updateDC(masterList, messageFromDC.machinePID);
			
		} 
		// If the process ID is already in the master list, update the lastHeardFrom field to the current time.
		else 
		{
			updateDCsLastHeardFrom(masterList, messageFromDC.machinePID, currentTime);
		}
		
		// Check the message from the DC
		dcProcessIDList = checkMessageFromDC(masterList, dcProcessIDList, messageFromDC.message_code, messageFromDC.machinePID, messageFromDC.msgDescription);
		
    	printf("Master->element1: %d\nMaster->element2: %d\n", masterList->msgQueueID, masterList->numberOfDCs);
    	for (int i = 0; i < MAX_DC_ROLES ; i++) 
    	{
			if(masterList->dc[i].dcProcessID > 0){
				printf("Master->DCElements[%d]: %d\n", i, masterList->dc[i].dcProcessID);
			}        	
    	}

		// Sleep 1.5 seconds and continue
		usleep(ONE_HALF_SECONDS);
	}

	// Close the DR and free the message queue and shared memory
	printf("Data Reader is closed\n");
	fflush(stdout);

	// Free up resources that used in DR
	dcProcessIDList = FreeUpResources(qID, shmID, dcProcessIDList, masterList);

	return;
}
