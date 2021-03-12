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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "../../common/inc/hoochamacallit.h"
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"
#include "../inc/semaphoreStruct.h"

int createMessageQueue()
{
	key_t msgKey;
	int qID = -1;

	// Generate the key
	msgKey = ftok("/tmp", 'A');

	// Check the key
	if (msgKey == -1)
	{
		printf("Server cannot create key!\n");
		fflush(stdout);
	}

	// Check the message queue ID
	if ((qID = msgget(msgKey, 0)) == -1)
	{
		// If it doesn't exist, Create message queue
		qID = msgget(msgKey, (IPC_CREAT | 0660));
		printf("Message Queue ID is created: %d\n", qID);
	}

	return qID;
}

int createSharedMemory()
{
	key_t shmem_key;
	int shmID = -1;
	MasterList *p;
	
	// Check the message queue ID
	if ((shmID = shmget(shmem_key, sizeof(MasterList), 0)) == -1)
	{
		// If it doesn't exist, Create message queue
		shmID = shmget(shmem_key, sizeof(MasterList), (IPC_CREAT | 0660));
		printf("Shared Memory ID is created: %d\n", shmID);
	}

	return shmID;
}
