/* ===============================================================================
* FILE : encodeInput.h
* PROJECT : SENG2330 - Assignment 2
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : February 14,2021
* DESCRIPTION :
* this include file contains the necessary prototypes and constants for the encodeInput application
* ================================================================================*/


#ifndef __DC_PROCESS_ID_LIST_H__
#define __DC_PROCESS_ID_LIST_H__

#define FOUND        1
#define NOT_FOUND   -1
#define ERROR       -2
#define SUCCESS      2

typedef struct DCProcessIDList{
    pid_t dcProcessID;
	struct DCProcessIDList* next;
} DCProcessIDList;

#else

extern struct DCProcessIDList DCProcessIDList;

#endif

int addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID);
int findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID);
DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead);
void printList(DCProcessIDList *pHead);
