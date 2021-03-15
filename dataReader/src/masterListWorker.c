/* ===============================================================================
* FILE : encodeInput.c
* PROJECT : SENG2330 - Assignment 2
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : February 14,2021
* DESCRIPTION :
* 
* ================================================================================*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../common/inc/masterList.h"

void deleteDC(MasterList *masterList, pid_t dcProcessID)
{
    // Check the process ID from the DCInfo array
    for (int i = 0; i < masterList->numberOfDCs; i++)
    {
        // If the DC's ID is in the array,
        if (masterList->dc[i].dcProcessID == dcProcessID)
        {
            if (i == 0)
            {
                masterList->dc[i] = masterList->dc[i + 1];
            }
            else
            {
                // Remove and reset and re-arrange them.
                for (int j = i - 1; j < masterList->numberOfDCs; j++)
                {
                    masterList->dc[j] = masterList->dc[j + 1];
                }
            }
        }
    }

    // Decrement numberOfDCs by 1;
    masterList->numberOfDCs -= 1;

    printf("size of the masterList = %d\n", masterList->numberOfDCs);
}

void updateDC(MasterList *masterList, pid_t dcProcessID)
{
    // Get the index for the new DC in the dcArray
    if (masterList->numberOfDCs == 10)
    {
        printf("No more DC!\n");
        return;
    }
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