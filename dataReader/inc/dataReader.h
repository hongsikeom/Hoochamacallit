/* ===============================================================================
* FILE : dataReader.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION :
* this include file contains the necessary prototypes for the dataReader application
* ================================================================================*/


#define     RUN     1
#define     STOP    0
#define     SHMKEY  16535

// Function prototypes
int createMessageQueue();
int createSharedMemory();
// void checkDCProcessID(pid_t *DCProcessIDList, int *listCounter, pid_t DCprocessID);