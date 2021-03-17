/* ===============================================================================
* FILE : dataReaderMain.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This file creates the mesage queue and shared memory space to receive
* messages from DCs and processes them. When MasterList does not contain any DCs then
* exits the program.
* ================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "../../common/inc/hoochamacallit.h"
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"
#include "../inc/dcProcessIDList.h"
// #include "../inc/semaphoreStruct.h"

#include <time.h>
#include <signal.h>


void main(int argc, char *argv[])
{
	int qID = -1;       				      // Message queue ID
	int shmID = -1;     				   	  // Shared memory ID
	int msgRun = 1;     					  // For loop	
	MasterList *masterList = NULL;    		  // MasterList
	DCProcessIDList *DCProcessIDList = NULL;  // DC ProcessIDList (It will hold the ProcessIDs that have been 
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

	//======================================================================================================
	// DCs PID  List Test=============================================================================
	//======================================================================================================
	

	int check = 0;

	check = addDCprocessID(&DCProcessIDList, 111);
	if(check != SUCCESS) {
		printf("already exists\n");
	}
	
	check = addDCprocessID(&DCProcessIDList, 222);
	if(check != SUCCESS) {
		printf("already exists\n");
	}

	check = addDCprocessID(&DCProcessIDList, 111);
	if(check != SUCCESS) {
		printf("already exists\n");
	}

	check = addDCprocessID(&DCProcessIDList, 333);
	if(check != SUCCESS) {
		printf("already exists\n");
	}

	check = addDCprocessID(&DCProcessIDList, 111);
	if(check != SUCCESS) {
		printf("already exists\n");
	}

	check = addDCprocessID(&DCProcessIDList, 333);
	if(check != SUCCESS) {
		printf("already exists\n");
	}

	printList(DCProcessIDList);


	//======================================================================================================
	// DCs PID  List Test END=============================================================================
	//======================================================================================================





	// //======================================================================================================
	// // MasterList Update Delete Test=============================================================================
	// //======================================================================================================

	// updateDC(masterList, 455);
	// updateDC(masterList, 452);
	// updateDC(masterList, 459);

	// printf("\nThe number of DCs in the Master List = %d\n", masterList->numberOfDCs);
	
	// deleteDC(masterList, masterList->dc[2].dcProcessID);
	// deleteDC(masterList, masterList->dc[1].dcProcessID);
	// deleteDC(masterList, masterList->dc[0].dcProcessID);

	// for (int i = 0; i < MAX_DC_ROLES; i++)
	// {
	// 	printf("\n\nDC array [%d]'s dcProcessID = %d", i, masterList->dc[i].dcProcessID);
	// 	printf("\nDC array [%d]'s lastTimeHeardFrom = %ld\n", i, masterList->dc[i].lastTimeHeardFrom);	
	// }

	// printf("\nThe number of DCs in the Master List = %d\n", masterList->numberOfDCs);
	

	// //======================================================================================================
	// // MasterList Deletion END =============================================================================
	// //======================================================================================================


	// Signal handler
	signal(SIGALRM, alarmHandler);
	alarm(2);

	// Listening messages from DCs
	while (msgRun == 1)
	{
		printf("Waiting for messages...\n");
		fflush(stdout);

		msgRun = 0;
		sleep(1.5);
	}

	// Close the DR and free the message queue and shared memory
	printf("Data Reader is closed\n");
	DCProcessIDList = freeDCProcessIDList(DCProcessIDList);
	msgctl(qID, IPC_RMID, (struct msqid_ds *)NULL);
	shmdt(masterList);
	shmctl(shmID, IPC_RMID, 0);

	return;
}
