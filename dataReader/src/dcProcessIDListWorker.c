/* ===============================================================================
* FILE : dcProcessIDListWorker.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This file contains methods that support DcProcessIDList.
* DCProcessIDList keeps the DCs process ID, which have been connected to the DR
* and left, and it is used for filtering DCs.
* ================================================================================*/



#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include "../inc/dcProcessIDList.h"



/*
	Name	: addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID)
	Purpose : This function is used to add DC's process id to the list
	Inputs	: DCProcessIDList **pHead  -  Head of ProcessIDList
              pid_t dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: int SUCCESS  -  Successfully added to the list
              int ERROR  -  Error has occurred when allocating space for the DCProcessIDList
              int FOUND  -  DC's process ID is already in the list.
*/
int addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID)
{
    // Check if the DC's process ID is already in the DCProcessIDList
    int IDcheck = findDCprocessID(*pHead, dcProcessID);
    if (IDcheck == FOUND)
    {
        return FOUND;
    }

    // Allocate the space for the new DCProcessIDList
    DCProcessIDList *newNode = NULL;
    newNode = (DCProcessIDList *)malloc(sizeof(DCProcessIDList));

    // If failed
    if (newNode == NULL)
    {
        printf("No Memory!");
        return ERROR;
    }

    // Assign the DC's process ID to the newly created list
    newNode->dcProcessID = dcProcessID;
    
    // Newly created list will be the head and points to the one that was previosuly the head.
    newNode->next = *pHead;
    *pHead = newNode;

    return SUCCESS;
}



/*
	Name	: findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID)
	Purpose : This function is used to find if the DC's process ID is already in the DCProcessIDList.
	Inputs	: DCProcessIDList *pHead  -  Head of ProcessIDList
              pid_t dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: int FOUND  -  DC's process ID is already in the DCProcessIDList
              int NOT_FOUND  -  DC's process ID is not in the DCProcessIDList
*/
int findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID)
{
    // Get the head
    DCProcessIDList *current = pHead;

    // If pHead is NULL, it means there is no DC's process ID in the list
    if (pHead == NULL)
    {
        return NOT_FOUND;
    }

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



/*
	Name	: printList(DCProcessIDList *pHead)
	Purpose : This function is used to display all process IDs in the DCProcessIDList
	Inputs	: DCProcessIDList *pHead  -  Head of ProcessIDList
	Outputs	: None
	Returns	: None
*/
void printList(DCProcessIDList *pHead)
{
    // Get the head
    DCProcessIDList *ptr = pHead;
    printf("\n[ ");

    // Display all process ID from the beginning
    while (ptr != NULL)
    {
        printf("(%d) ", ptr->dcProcessID);
        ptr = ptr->next;
    }

    printf(" ]");
}