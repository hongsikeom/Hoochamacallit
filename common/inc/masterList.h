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
#define FOUND        1
#define NOT_FOUND   -1
#define ERROR       -2
#define SUCCESS      2


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

typedef struct DCProcessIDList{
    pid_t dcProcessID;
	struct DCProcessIDList* next;
} DCProcessIDList;

#else

extern struct DCInfo DCInfo;
extern struct MasterList MasterList;
extern struct DCProcessIDList DCProcessIDList;

#endif

// Prototypes
DCProcessIDList * deleteDC(MasterList *masterList, pid_t dcProcessID, DCProcessIDList *dcProcessIDList);
void updateDC(MasterList *masterList, pid_t dcProcessID);
DCProcessIDList *checkLastHeardFrom(MasterList *masterList, long currentTime, DCProcessIDList *dcProcessIDList);
DCProcessIDList * checkMessageFromDC(MasterList *masterList , DCProcessIDList *dcProcessIDList, int messageNum, pid_t processID);

int addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID);
int findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID);
DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead);
void printList(DCProcessIDList *pHead);