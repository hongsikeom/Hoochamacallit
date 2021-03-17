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
                masterList->dc[i] = masterList->dc[i + 1];
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

    printf("size of the masterList = %d\n", masterList->numberOfDCs);
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