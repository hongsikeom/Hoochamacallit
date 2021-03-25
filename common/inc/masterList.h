/* ===============================================================================
* FILE : masterList.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 20,2021
* DESCRIPTION : This include file contains the necessary constants and prototypes 
* for the master list. The master list keeps the information of message queue id and
* information about DCs that connected to the DR
* ================================================================================*/

#ifndef __MASTER_LIST_H__
#define __MASTER_LIST_H__

// Constants
#define MAX_DC_ROLES 		10       // Max number of DC


// MasetrList / DCInfo / DCProcessIDList struct
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

typedef struct DCProcessIDList
{
    pid_t dcProcessID;
	struct DCProcessIDList* next;
} DCProcessIDList;

#else

extern struct DCInfo DCInfo;
extern struct MasterList MasterList;
extern struct DCProcessIDList DCProcessIDList;

#endif

