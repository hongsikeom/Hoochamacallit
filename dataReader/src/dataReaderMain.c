/* ===============================================================================
* FILE : encodeInput.c
* PROJECT : SENG2330 - Assignment 2
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : February 14,2021
* DESCRIPTION :
* 
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
#include "../inc/semaphoreStruct.h"

void main(int argc, char *argv[])
{

	int qID = -1;
	int shmID = -1;
	int msgRun = 1;
	MasterList *masterList;

	qID = createMessageQueue();

	if (qID == -1)
	{
		printf("Data Reader can\'t create queue!\n");
		fflush(stdout);
		return;
	}

	shmID = createSharedMemory();

	if (shmID == -1){
		printf("Data Reader can\'t create shared memory!\n");
		fflush(stdout);
		return;
	}

	masterList = (MasterList *)shmat(shmID, NULL, 0);
	if (masterList == NULL ){
		printf("Data Reader can\'t attach to shared memory!\n");
	}

	printf("\n============================================");
	printf("\nMessage queue ID is: %d\n", qID);
	printf("Shared Memory ID is: %d\n", shmID);
	printf("============================================\n\n");

	while (msgRun == 1)
	{
		printf("Waiting for messages...\n");
		fflush(stdout);


		sleep(1.5);
		msgRun = 0;
	}

	// Close the DR and free the message queue and shared memory
	printf("Data Reader is closed\n");
	shmdt(masterList);

	msgctl(qID, IPC_RMID, (struct msqid_ds *)NULL);
	shmctl (shmID, IPC_RMID, 0);
	return;
}
