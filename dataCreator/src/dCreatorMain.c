// #===============================================================================
// # FILE : dCreatorMain.c
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
#include "../inc/dataCreatorHeader.h"

void main(int argc, char *argv[]){

    printf("Data Creator Starting...\n");
    //check message queue 
    int msgQID = checkMsgQueue();

    //get process id
    pid_t myPid = getpid();

    //populate message
    MESSAGECONTENT msg;
    int sendTimer = 0;

    printf("\n queue ID: %d\n", msgQID);
    printf("\n pID ID: %d\n", myPid);

while(msg.message_code != MACHINE_OFFLINE){

    //Build msg
    msg.machinePID = myPid;

    //printf("msgPID = %d\n", msg.machinePID);
    srand(time(NULL));

    msg.message_code = getRandomMsgStatus();
    //printf("MsgStatus = %ld\n", msg.message_code);
    getMsgCodeDescription(msg.msgDescription, msg.message_code);
    printf("MsgStatus description = %s\n", msg.msgDescription);

    srand(time(NULL));
    sendTimer = getRandomTimer();

    //send msg
    int msgSize = sizeof(msg) - sizeof(long);

    printf("message code: %ld\n", msg.message_code);
    msgsnd(msgQID, (void*)&msg,msgSize, 0);

    sleep(sendTimer);

    

}
    printf("\nClosed\n");
    



    return;
}