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

#include "../../common/inc/hoochamacallit.h"
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"
// #include "../inc/semaphoreStruct.h"
	



void main(int argc, char *argv[])
{
	int qID = -1;       				      // Message queue ID
	int shmID = -1;     				   	  // Shared memory ID
	int msgRun = 1;     					  // For loop

	struct timeval currentTimeStruct;               // Current time
	long currentTime;
	MasterList *masterList = NULL;    		  // MasterList
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

	


	// //======================================================================================================
	// // MasterList Update
	// //======================================================================================================

	updateDC(masterList, 455);
	updateDC(masterList, 552);
	updateDC(masterList, 659);
	updateDC(masterList, 759);
	updateDC(masterList, 859);

	int checkID = 0;

	// Listening messages from DCs
	while (msgRun == 1)
	{
		printf("Waiting for messages...\n");
		fflush(stdout);

		gettimeofday(&currentTimeStruct, NULL);	
		currentTime = currentTimeStruct.tv_sec;
		dcProcessIDList = checkLastHeardFrom(masterList, currentTime, dcProcessIDList);

		if (currentTime > 36) {
			printf("\n\n\n=====start to check===\n");
			checkID =findDCprocessID(dcProcessIDList, 455);
			if (checkID == 1) {
				printf("Found\n");
			} else {
				printf("NOT FOUND\n");
			}
			checkID =findDCprocessID(dcProcessIDList, 552);
			if (checkID == 1) {
				printf("Found\n");
			} else {
				printf("NOT FOUND\n");
			}
			checkID =findDCprocessID(dcProcessIDList, 659);
			if (checkID == 1) {
				printf("Found\n");
			} else {
				printf("NOT FOUND\n");
			}
			checkID =findDCprocessID(dcProcessIDList, 759);
			if (checkID == 1) {
				printf("Found\n");
			} else {
				printf("NOT FOUND\n");
			}
			checkID =findDCprocessID(dcProcessIDList, 859);
			if (checkID == 1) {
				printf("Found\n");
			} else {
				printf("NOT FOUND\n");
			}
		}
		

		// msgRun = 0;
		sleep(1.5);
	}

	// Close the DR and free the message queue and shared memory
	printf("Data Reader is closed\n");
	dcProcessIDList = freeDCProcessIDList(dcProcessIDList);
	msgctl(qID, IPC_RMID, (struct msqid_ds *)NULL);
	shmdt(masterList);
	shmctl(shmID, IPC_RMID, 0);

	return;
}