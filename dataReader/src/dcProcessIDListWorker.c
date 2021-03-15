#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include "../inc/dcProcessIDList.h"

int addDCprocessID(DCProcessIDList **pHead, pid_t dcProcessID)
{
    int IDcheck = findDCprocessID(*pHead, dcProcessID);
    if (IDcheck == FOUND)
    {
        return FOUND;
    }

    printf("gogogo\n");
    DCProcessIDList *newNode = NULL;
    newNode = (DCProcessIDList *)malloc(sizeof(DCProcessIDList));

    if (newNode == NULL)
    {
        printf("No Memory!");
        return ERROR;
    }

    newNode->dcProcessID = dcProcessID;
    newNode->next = *pHead;
    *pHead = newNode;

    return SUCCESS;
}

int findDCprocessID(DCProcessIDList *pHead, pid_t dcProcessID)
{
    DCProcessIDList *current = pHead;

    if (pHead == NULL)
    {
        return NOT_FOUND;
    }

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

DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead)
{
    DCProcessIDList *ptr = pHead;
    DCProcessIDList *curr = pHead;

    while (ptr != NULL)
    {
        curr = ptr;
        ptr = ptr->next;
        free(curr);
    }

    return NULL;
}

void printList(DCProcessIDList *pHead)
{
    DCProcessIDList *ptr = pHead;
    printf("\n[ ");

    //start from the beginning
    while (ptr != NULL)
    {
        printf("(%d) ", ptr->dcProcessID);
        ptr = ptr->next;
    }

    printf(" ]");
}