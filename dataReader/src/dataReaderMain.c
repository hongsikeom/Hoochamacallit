/* ===============================================================================
* FILE : dataReaderMain.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This file creates the mesage queue and shared memory space to receive
* messages from DCs and processes them. When MasterList does not contain any DCs then
* exits the program.
* ================================================================================*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>

#include "../../common/inc/message_struct.h"
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"
// #include "../inc/semaphoreStruct.h"



void main(int argc, char *argv[])
{
	int qID = -1;       				      // Message queue ID
	int shmID = -1;     				   	  // Shared memory ID
	int msgRun = 1;     					  // For loop
	int sizeOfData = 0;						  // Size of messagea from the DC
	int rc = 0;								  // Retrun code from message processing
	int checkProcessID = 0;                   // Check the process id in the DCProcessIDList

	struct timeval currentTimeStruct;               // Current time
	long startTime;
	long currentTime;
	MasterList *masterList;    		  		  // MasterList
	MESSAGECONTENT messageFromDC;
	DCProcessIDList *dcProcessIDList = NULL;  // DC ProcessIDList (It will hold the ProcessIDs that have been 	
											  // connnected to ther server and left)
	
    										
	
	// Create Message Queue
	qID = createMessageQueue();
	if (qID == -1)
	{
		printf("Data Reader can\'t create queue!\n");
		fflush(stdout);
		return;
	}

	// Create Shared Memoery
	shmID = createSharedMemory();
	if (shmID == -1)
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

	// Set the qID to msgQueueID
	masterList->msgQueueID = qID;


	// Test output to the console to be removed
	printf("\n============================================");
	printf("\nMessage queue ID is: %d\n", masterList->msgQueueID);
	printf("Shared Memory ID is: %d\n", shmID);
	printf("============================================\n\n");

	gettimeofday(&currentTimeStruct, NULL);	
	startTime = currentTimeStruct.tv_sec;

	// Listening messages from DCs
	while (msgRun == RUN)
	{
		// KEY CHECK=========================================
		// key_t msgKey;
		// msgKey = ftok("/tmp", 'A');
		// if ((qID = msgget(msgKey, 0)) == -1)
		// {
		// 	printf("qID check %d\n", msgKey);
		// } else {
		// 	printf("qID check %d\n", msgKey);
		// }
		// KEY CHECK=========================================


		printf("Waiting for messages...\n Nuber of DCs: %d\n", masterList->numberOfDCs);
		fflush(stdout);

		// Get the current time in seconds
		gettimeofday(&currentTimeStruct, NULL);	
		currentTime = currentTimeStruct.tv_sec;
		printf("time difference: %ld\n", currentTime - startTime);
		if (currentTime - startTime > 35) {
			printf("Time over done\n ");
			break;
		}

		// Getting message from the DC
		rc = msgrcv (qID, (void *)&messageFromDC, sizeof(MESSAGECONTENT) - sizeof(long), 0, IPC_NOWAIT);
		if (rc == -1) { 
			int errsv = errno;
			if (errsv != 42) {
				printf("Something happens! I'm out of here!");
				break;
			}
			sleep(1.5);
			continue;
		}

		gettimeofday(&currentTimeStruct, NULL);
		startTime = currentTimeStruct.tv_sec;

		printf("\n\n(SERVER) Received: PID: %d\n(SERVER) Received: MSG CODE: %ld\n\n", messageFromDC.machinePID, messageFromDC.message_code);
		fflush(stdout);
		

		// Check if the DCs process ID is in the DCProcessIDList (It has already been connected to the DR and left)
		if ((checkProcessID = findDCprocessID(dcProcessIDList, messageFromDC.machinePID)) == FOUND) { 
			printf("%d is found will continue\n", messageFromDC.machinePID);
			continue; 
		}

		// Update the DC to the master list
		if (checkPIDFromMasterList(masterList, messageFromDC.machinePID) == NOT_FOUND) {
			updateDC(masterList, messageFromDC.machinePID);
		} else {
			updateDCsLastHeardFrom(masterList, messageFromDC.machinePID, currentTime);
		}
		
		// Check the message from the DC
		dcProcessIDList = checkMessageFromDC(masterList, dcProcessIDList, messageFromDC.message_code, messageFromDC.machinePID);

		// Check if the DC has not sent any messages more than 35 seconds to the DR
		dcProcessIDList = checkLastHeardFrom(masterList, currentTime, dcProcessIDList);
		
		// msgRun = STOP;
		sleep(1.5);
	}

	// Close the DR and free the message queue and shared memory
	printf("Data Reader is closed\n");
	fflush(stdout);
	dcProcessIDList = freeDCProcessIDList(dcProcessIDList);
	msgctl(qID, IPC_RMID, (struct msqid_ds *)NULL);
	shmdt(masterList);
	shmctl(shmID, IPC_RMID, 0);

	return;
}