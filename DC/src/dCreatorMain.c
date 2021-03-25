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


#include "../inc/dataCreatorHeader.h"

void main(int argc, char *argv[]){
    
    //check message queue 
    int msgQID = checkMsgQueue();

    //get process id
    pid_t myPid = getpid();

    //initialize message
    MESSAGECONTENT msg = {0, "", 0 };
    int sendTimer = 0;
    int firstMsg = 0;

    //main loop
    while(msg.message_code != MACHINE_OFFLINE){

        //Build msg
        msg.machinePID = myPid;

        //get Random msg Status if not first message
        srand(time(NULL));
        if (firstMsg == 0) {
            msg.message_code = EVERYTHING_OK;
            firstMsg++;
        } else {
            msg.message_code = getRandomMsgStatus();
            firstMsg++;
        }
        //msg description
        getMsgCodeDescription(msg.msgDescription, msg.message_code);
        
        //send msg
        int msgSize = sizeof(msg) - sizeof(long);        
        msgsnd(msgQID, (void*)&msg,msgSize, IPC_NOWAIT);
        //log info
        logDataCreator(msg.machinePID,msg.message_code,msg.msgDescription);

        //sleep between 10-30 sec
        srand(time(NULL));
        sendTimer = getRandomTimer();    
        sleep(sendTimer);
   
    }
     
    return;
}