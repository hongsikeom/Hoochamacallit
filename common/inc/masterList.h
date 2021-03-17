/* ===============================================================================
* FILE : masterList.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This include file contains the necessary constants and prototypes 
* for the master list. The master list keeps the information of message queue id and
* information about DCs that connected to the DR
* ================================================================================*/

#ifndef __MASTER_LIST_H__
#define __MASTER_LIST_H__

// Constants
#define MAX_DC_ROLES 10
#define OUT_OF_DC_INDEX -1


// MasetrList and DCInfo struct

typedef struct
{
	pid_t dcProcessID;
	long lastTimeHeardFrom;
} DCInfo;

typedef struct 
{
	int msgQueueID;
	int numberOfDCs;
	DCInfo dc[MAX_DC_ROLES];
} MasterList;

#else

extern struct DCInfo DCInfo;
extern struct MasterList MasterList;

#endif

// Prototypes
void deleteDC(MasterList *masterList, pid_t dcProcessID, DCProcessIDList** dCProcessIDList);
void updateDC(MasterList *masterList, pid_t dcProcessID);