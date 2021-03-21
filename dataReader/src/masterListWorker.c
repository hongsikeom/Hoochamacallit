/* ===============================================================================
* FILE : masterListWorker.c
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 29,2021
* DESCRIPTION : This file contains methods that support masterList.
* The master list keeps the information of message queue id and 
* information about DCs that connected to the DR
* ================================================================================*/



#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../common/inc/masterList.h"



/*
	Name	: deleteDC(MasterList *masterList, pid_t dcProcessID)
	Purpose : This function is used to delete DCs that are not sending messages within 35 seconds or
              disconnected from the DR
	Inputs	: MasterList *masterList  -  Head of the master list
              pid_t dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: None
*/
void deleteDC(MasterList *masterList, pid_t dcProcessID)
{
    // Check the process ID from the DCInfo array
    for (int i = 0; i < masterList->numberOfDCs; i++)
    {
        // If the DC's ID is in the array,
        if (masterList->dc[i].dcProcessID == dcProcessID)
        {
            // If the master list is holding only one DC
            if (i == 0)
            {
                // Remove and reset and re-arrange them.
                for (int j = i; j < masterList->numberOfDCs; j++)
                {
                    masterList->dc[j] = masterList->dc[j + 1];
                }
            }
            // If the master list is holding more than one DC
            else
            {
                // Remove and reset and re-arrange them.
                for (int j = i - 1; j < masterList->numberOfDCs; j++)
                {
                    masterList->dc[j] = masterList->dc[j + 1];
                }
            }

            // Decrement numberOfDCs by 1;
            masterList->numberOfDCs -= 1;
        }
    }
}



/*
	Name	: updateDC(MasterList *masterList, pid_t dcProcessID)
	Purpose : This function is used to update the new DC to the master list
	Inputs	: MasterList *masterList  -  Head of the master list
              pid_t dcProcessID  -  DC's process ID
	Outputs	: None
	Returns	: None
*/
void updateDC(MasterList *masterList, pid_t dcProcessID)
{
    // If the number of DCs in the list is greater than or equal to 10,
    // it does not add it to the list and exit the function
    if (masterList->numberOfDCs >= 10)
    {
        printf("No more DC!\n");
        return;
    }

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

    printf("\nThe New DCs index = %d\nThe new DCs processID = %d\n The New DCs lastTimeHeardFrom = %ld\n\n",
           masterList->numberOfDCs, masterList->dc[newIndex].dcProcessID, masterList->dc[newIndex].lastTimeHeardFrom);
}



/*
	Name	: checkLastHeardFrom(MasterList *mastaerList, long currentTime)
	Purpose : This function is used to check if any of DCs have not sent messages to DR 
	          within 35seconds, and remove them from the master list.
	Inputs	: MasterList *masterList  -  Head of the master list
              long currentTime  -  Current time
	Outputs	: None
	Returns	: None
*/
DCProcessIDList *checkLastHeardFrom(MasterList *masterList, long currentTime, DCProcessIDList *dcProcessIDList)
{
	for (int i = 0; i < masterList->numberOfDCs; i++) {
		long timeDifferent = currentTime - masterList->dc[i].lastTimeHeardFrom;
		printf("DC[%d]'s ID-%d  =  last-heard-time: %ld\nCurrent time: %ld\nTime Difference: %ld\n", i, masterList->dc[i].dcProcessID, masterList->dc[i].lastTimeHeardFrom, currentTime, timeDifferent);
		if (timeDifferent > 35) {
			printf("%d is deleted!\n", masterList->dc[i].dcProcessID);
            addDCprocessID(&dcProcessIDList, masterList->dc[i].dcProcessID);
			deleteDC(masterList, masterList->dc[i].dcProcessID);
			i--;
		}
		printf("\nNumber of dcs : %d\n", masterList->numberOfDCs);
	}
    return dcProcessIDList;
}


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