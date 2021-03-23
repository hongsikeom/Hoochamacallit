// #===============================================================================
// # FILE : dCorruptorMain.c
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// #   this program emulates a production machine that communicates with a server
// #   it's main purpose is to generate and send status conditions as messages to
// #   the server indicating the state of the hoochamacallit machine.     
// #===============================================================================


//#include <stdio.h>
#include <unistd.h>
#include "../inc/dataCorruptorHeader.h"

void main(int argc, char *argv[]){

    MasterList *pML = NULL;             //pointer to master list
    printf("Data Corruptor Starting...\n");

    //check for shared memory 
    int shmID = checkSharedMemory();
    //exit if shared memory was not found and the attemps are over
    if(shmID <= 0){ return; } 

    //attach to shared memory
    pML = attachToSharedMemory(shmID);
    int errnum = -1;
    errnum = errno;
    if(errnum == ERROR_OCCURED){ printf("pML is -1 ERROR occured\n;"); } //** delete
    if(pML != NULL){ printf("pML is not null\n;"); }   //** delete
    //getMsgQID
    int msgQID = checkMsgQueueCorruptor(pML);

    //get process id
    pid_t myPid = getpid();
    printf("\n SharedMemory ID: %d\n", shmID);
    printf("\n pID ID: %d\n", (int)myPid);
    
    //main loop
    int sleepTimer = 0, wodAction = 0;
    while(RUN){

        //sleep between 10-30 sec
        srand(time(NULL));
        sleepTimer = getRandomSleepTime();
        printf("Sleep for : %d seconds\n", sleepTimer);
        sleep(sleepTimer);

        //check existance of message Queue
        msgQID = checkMsgQueueCorruptor(pML);
        if(msgQID == ERROR_OCCURED){
            printf("msgQID not found error occured");
            break;}

        //Wheel of Destruction - Action to execute
        wodAction = getRandomWODAction();
        printf("WOD Action: %d\n", wodAction);
        getWOD(pML, wodAction);
        //printf("WOD Action # %02d\n", wodAction);
       
    }
    

    printf("\nCorrupted Closed\n");
    



    return;
}