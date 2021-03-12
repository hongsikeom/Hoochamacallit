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

typedef struct
{
	pid_t dcProcessID;
	int lastTimeHeardFrom;
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
