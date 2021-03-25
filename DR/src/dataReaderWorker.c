/* ===============================================================================
* FILE : dataReaderWorker.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 20,2021
* DESCRIPTION : This file contains methods that handle messages from DCs to
*               support DR application.
* ================================================================================*/


#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../common/inc/loggerHeader.h"
#include "../../common/inc/message_struct.h"
#include "../../common/inc/masterList.h"



/*
	Name	: deleteDC(MasterList *masterList, pid_t dcProcessID)
	Purpose : This function is used to delete DCs that are not sending messages within 35 seconds or
              disconnected from the DR
	Inputs	: MasterList *masterList  -  Head of the master list
              DCProcessIDList *dcProcessIDList  -  Head of ProcessIDList
              int indexToBeDeleted  -  Index of dc array to be deleted
	Outputs	: None
	Returns	: None
*/
DCProcessIDList * deleteDC(MasterList *masterList, DCProcessIDList *dcProcessIDList, int indexToBeDeleted)
{
    // Add process ID to the DCProcessIDList
    addDCprocessID(&dcProcessIDList, masterList->dc[indexToBeDeleted].dcProcessID);


    // Remove and reset and re-arrange them.
    for (int i = indexToBeDeleted; i < masterList->numberOfDCs; i++)
    {
         masterList->dc[i] = masterList->dc[i + 1];

        // When the index of dc reaches the number of the dc list,
        // Set the last elemnt to 0;
        if (i == masterList->numberOfDCs - 1)
        {
            masterList->dc[i].dcProcessID = 0;
            masterList->dc[i].lastTimeHeardFrom = 0;
        }
    }
    //Decrement numberOfDCs by 1;
    masterList->numberOfDCs -= 1;


    printf("Master->element1: %d\nMaster->element2: %d\n", masterList->msgQueueID, masterList->numberOfDCs);
    for (int i = 0; i < MAX_DC_ROLES ; i++) 
    {
        printf("Master->DCElements[%d]: %d\n", i, masterList->dc[i].dcProcessID);
    }
    return dcProcessIDList;
}



/*
	Name	: updateDC(MasterList *masterList, pid_t dcProcessID)
	Purpose : This function is used to update the new DC to the master list
	Inputs	: MasterList *masterList  -  Head of the master list
              long dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: None
*/
void updateDC(MasterList *masterList, long dcProcessID)
{
    // If the number of DCs in the list is greater than or equal to 10,
    // it does not add it to the list and exit the function
    if (masterList->numberOfDCs >= MAX_DC_ROLES) { return; }

    // Get the new index for the DC to be added
    int newIndex = masterList->numberOfDCs;

    // Get the current time
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    // Increment the numberOfDCs by 1
    masterList->numberOfDCs += 1;

    // Assign DCs process ID and current time
    masterList->dc[newIndex].dcProcessID = dcProcessID;
    masterList->dc[newIndex].lastTimeHeardFrom = currentTime.tv_sec;
}



/*
	Name	: updateDCsLastHeardFrom(MasterList *masterList, long dcProcessID, long currentTime)
	Purpose : This function is used to update the given process ID's lastHeardFrom field in the master list
	Inputs	: MasterList *masterList  -  Head of the master list
              long dcProcessID  -  DC's process ID
              long currentTime  -  Current time
	Outputs	: None
	Returns	: None
*/
void updateDCsLastHeardFrom(MasterList *masterList, long dcProcessID, long currentTime)
{
    for (int i = 0; i < masterList->numberOfDCs; i++){
        if (masterList->dc[i].dcProcessID == dcProcessID)
        {
            masterList->dc[i].lastTimeHeardFrom = currentTime;
        }
    }
}



/*
	Name	: checkMessageFromDC(MasterList *masterList , DCProcessIDList *dcProcessIDList, int messageNum, long processID)
	Purpose : This function is used to check and process the message from DCs and log the messages to the log file.
              If the message is "MACHINE_OFFLINE", It will remove the DC from the master list
	Inputs	: MasterList *masterList  -  Head of the master list
              DCProcessIDList *dcProcessIDList  -  Head of ProcessIDList
              int messageNum  -  Message number from DC
              long dcProcessID  -  DC's process ID
              char* msgDescription  -  Message description 
	Outputs	: None
	Returns	: DCProcessIDList *dcProcessIDList - Head of ProcessIDList
*/
DCProcessIDList * checkMessageFromDC(MasterList *masterList, DCProcessIDList *dcProcessIDList, int messageNum, long processID, char* msgDescription) 
{
    // Get index of the currrent DC
    int indexOfDC = checkPIDFromMasterList(masterList, processID);

    switch (messageNum)
    {
        case EVERYTHING_OK:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case HYDRAULIC_PRESSURE_FAIL:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case SAFETY_BTN_FAIL:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case NO_RAW_MATERIAL:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case OPERATION_TMP_OUT_RANGE:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case OPERATOR_ERROR:
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            break;
        case MACHINE_OFFLINE:
            // Call deleteDC function to delete current DC from the master list
            logDataReader(indexOfDC, processID, "updated in the master list", messageNum, msgDescription, 0);
            dcProcessIDList = deleteDC(masterList, dcProcessIDList, indexOfDC);
            break;
        default:
            break;  
    }
    return dcProcessIDList;
}



/*
	Name	: checkLastHeardFrom(MasterList *mastaerList, long currentTime)
	Purpose : This function is used to check if any of DCs have not sent messages to DR 
	          within 35seconds, and remove them from the master list.
	Inputs	: MasterList *masterList  -  Head of the master list
              long currentTime  -  Current time
              DCProcessIDList *dcProcessIDList  -  Head of ProcessIDList
	Outputs	: None
	Returns	: DCProcessIDList *dcProcessIDList - Head of ProcessIDList
*/
DCProcessIDList *checkLastHeardFrom(MasterList *masterList, long currentTime, DCProcessIDList *dcProcessIDList)
{
    int indexOfDC = 0;
	for (int indexOfDC = 0; indexOfDC < masterList->numberOfDCs; indexOfDC++) {

        // Check the timeDifferent (currentTime - DC's lastTimeHeardFrom)
		long timeDifferent = currentTime - masterList->dc[indexOfDC].lastTimeHeardFrom;
		if (timeDifferent > TIME_LIMIT) {
            logDataReader(indexOfDC, masterList->dc[indexOfDC].dcProcessID, NULL, 0, NULL, NON_RESPONSIVE);
            
            // Add process ID to dcProcessIDList
            addDCprocessID(&dcProcessIDList, masterList->dc[indexOfDC].dcProcessID);

            // Delete current DC from the master list
			dcProcessIDList = deleteDC(masterList, dcProcessIDList, indexOfDC);
			indexOfDC--;
		}
	}
    return dcProcessIDList;
}


/*
	Name	: checkPIDFromMasterList(MasterList *masterList, long processID)
	Purpose : This function is used to check if the given DC's process ID is already in the master list
	Inputs	: MasterList *masterList  -  Head of the master list
              long dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: int indexOfDC  -  Index of the dc array
              int NOT_FOUND  -  If the process ID is not in the master list
*/
int checkPIDFromMasterList(MasterList *masterList, long processID)
{
    int indexOfDC = NOT_FOUND;
    for (int indexOfDC = 0; indexOfDC < masterList->numberOfDCs; indexOfDC++) {
        if (masterList->dc[indexOfDC].dcProcessID == processID) {
            return indexOfDC;
        }
    }
    return NOT_FOUND;
}


/*
	Name	: FreeUpResources(int qID, int shmID, DCProcessIDList* dcProcessIDList, MasterList *masterList)
	Purpose : This function is used to check if the given DC's process ID is already in the master list
	Inputs	: int qID  -  Message queue ID
              int shmID  -  Shared memory ID              
              MasterList *masterList  -  Head of the master list
              DCProcessIDList *dcProcessIDList  -  Head of ProcessIDList
	Outputs	: None
	Returns	: DCProcessIDList *dcProcessIDList - Head of ProcessIDList
*/
DCProcessIDList* FreeUpResources(int qID, int shmID, DCProcessIDList* dcProcessIDList, MasterList *masterList) {
    // If message queue does exist, it will close the message queue
    if (CheckMessageQueue() == MESSAGE_QUEUE_EXIST) {
        // Close the message queue
        msgctl(qID, IPC_RMID, (struct msqid_ds *)NULL);
    }

    // Free dcProcessIDList
    dcProcessIDList = freeDCProcessIDList(dcProcessIDList);
    dcProcessIDList = NULL;

    // Detach the master list from the shared memory and free the space
    shmdt(masterList);
    shmctl(shmID, IPC_RMID, 0);

    return dcProcessIDList;
}


/*
	Name	: addDCprocessID(DCProcessIDList **pHead, long dcProcessID)
	Purpose : This function is used to add DC's process id to the list
	Inputs	: DCProcessIDList **pHead  -  Head of ProcessIDList
              long dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: None
*/
void addDCprocessID(DCProcessIDList **pHead, long dcProcessID)
{
    // Check if the DC's process ID is already in the DCProcessIDList
    int IDcheck = findDCprocessID(*pHead, dcProcessID);
    if (IDcheck == FOUND) { return; }

    // Allocate the space for the new DCProcessIDList
    DCProcessIDList *newNode = NULL;
    newNode = (DCProcessIDList *)malloc(sizeof(DCProcessIDList));

    // If failed
    if (newNode == NULL) { return; }

    // Assign the DC's process ID to the newly created list
    newNode->dcProcessID = dcProcessID;
    
    // Newly created list will be the head and points to the one that was previosuly the head.
    newNode->next = *pHead;
    *pHead = newNode;
}



/*
	Name	: findDCprocessID(DCProcessIDList *pHead, long dcProcessID)
	Purpose : This function is used to find if the DC's process ID is already in the DCProcessIDList.
	Inputs	: DCProcessIDList *pHead  -  Head of ProcessIDList
              long dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: int FOUND  -  DC's process ID is already in the DCProcessIDList
              int NOT_FOUND  -  DC's process ID is not in the DCProcessIDList
*/
int findDCprocessID(DCProcessIDList *pHead, long dcProcessID)
{
    // Get the head
    DCProcessIDList *current = pHead;

    // If pHead is NULL, it means there is no DC's process ID in the list
    if (pHead == NULL) { return NOT_FOUND; }

    // Loop through the DCProcessIDList until it founds the DC's process ID in the list
    // If the next one is NULL, it means there is no DC's process ID in the list
    while (current->dcProcessID != dcProcessID)
    {
        if (current->next == NULL)
        {
            return NOT_FOUND;
        }
        else
        {
            current = current->next;
        }
    }

    return FOUND;
}



/*
	Name	: *freeDCProcessIDList(DCProcessIDList *pHead)
	Purpose : This function is used to free all the memory spaces that allocated for the DCProcessIDList
	Inputs	: DCProcessIDList *pHead  -  Head of ProcessIDList
	Outputs	: None
	Returns	: NULL  -  Null
*/
DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead)
{
    // Get head
    DCProcessIDList *ptr = pHead;
    DCProcessIDList *curr = pHead;

    // Loop until the end of the DCProcessIDList freeing the allocated memories
    while (ptr != NULL)
    {
        curr = ptr;
        ptr = ptr->next;
        free(curr);
    }

    return NULL;
}