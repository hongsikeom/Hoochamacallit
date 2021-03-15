/* ===============================================================================
* FILE : encodeInput.h
* PROJECT : SENG2330 - Assignment 2
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : February 14,2021
* DESCRIPTION :
* this include file contains the necessary prototypes and constants for the encodeInput application
* ================================================================================*/


#ifndef __MASTER_LIST_H__
#define __MASTER_LIST_H__

#define MAX_DC_ROLES 10
#define OUT_OF_DC_INDEX -1

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

void deleteDC(MasterList *masterList, pid_t dcProcessID);
void updateDC(MasterList *masterList, pid_t dcProcessID);