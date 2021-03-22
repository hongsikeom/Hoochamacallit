/* ===============================================================================
* FILE : dataReaderUtils.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This file contains the methods that supports dataReader application.
* ================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <errno.h>
#include "../../common/inc/masterList.h"
#include "../inc/dataReader.h"
#include "../inc/semaphoreStruct.h"




/*
	Name	: createMessageQueue()
	Purpose : This function is used to create message queue to receive messages from DCs
	Inputs	: None
	Outputs	: None
	Returns	: int qID  -  Message queue ID
*/
int createMessageQueue()
{
	// Message key and Queue ID
	key_t msgKey;
	int qID = 0;

	// Generate the key
	msgKey = ftok("/tmp", 'A');

	// Check the key
	if (msgKey == -1)
	{
		printf("Server cannot create key!\n");
		fflush(stdout);
		qID = -1;
		return qID;
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



/*
	Name	: createSharedMemory()
	Purpose : This function is used to create shared memory space to store DCs information
	Inputs	: None
	Outputs	: None
	Returns	: int shmID  -  Shared memory ID
*/
int createSharedMemory()
{
	// Shared memory key and ID
	key_t shmem_key;
	int shmID = 0;

	shmem_key = ftok (".", SHMKEY);

	// If ftok fails
	if (shmem_key == -1) {
		shmID = -1;
		return shmID;
	}

	// Check the message queue ID
	if ((shmID = shmget(shmem_key, sizeof(MasterList), 0)) == -1)
	{
		// If it doesn't exist, Create message queue
		shmID = shmget(shmem_key, sizeof(MasterList), (IPC_CREAT | 0660));
		printf("Shared Memory ID is created: %d\n", shmID);
	}

	return shmID;
}
