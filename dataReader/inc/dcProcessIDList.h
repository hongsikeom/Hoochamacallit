/* ===============================================================================
* FILE : dcProcessIDList.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This include file contains the necessary constants and prototypes 
* for the DCProcessIDList. DCProcessIDList keeps the DCs process ID, which have 
* been connected to the DR and left, and it is used for filtering DCs.
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

// Prototypes
int addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID);
int findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID);
DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead);
void printList(DCProcessIDList *pHead);
