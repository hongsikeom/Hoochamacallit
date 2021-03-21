// #===============================================================================
// # FILE : dCreatorFunctions.c
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// #   this program emulates a contains all the functions used by the dataCreator
// #   by generating and sending status conditions of the hoochamacallit machine to 
// #   the server implementing a message queue.  
// #===============================================================================

//#include <unistd.h>
#include "../inc/dataCreatorHeader.h"



//create function that checks for queue
//return msgQID
int checkMsgQueue(){

    int smhKey = 0, msgQID = 0, errnum = 0;    

    //get msgQueue key 
    smhKey = ftok(".", KEY_ID);      
  
    //check if msgQ exixst loop
    while(msgQID <= CHECK_MSG_QUEUE)
    {
        msgQID = msgget(smhKey, CHECK_MSG_QUEUE);   

        //if queue doesnt exist
        if(msgQID == ERROR_OCCURED) 
        {
            //sleep for 10 seconds
            sleep(DC_CHK_Q_TIMER);

            //check error with errno ???   
            // errnum = errno;
            // fprintf(stderr, "Value of errno: %d\n", errno);
            // fprintf(stderr, "Error: %s\n", strerror( errnum ));         
        }     
    }
 
    return msgQID;
}




//create function that randomly creates message status
//need to call srand(time(NULL));  before calling this function in main
// original = https://www.geeksforgeeks.org/generating-random-number-range-c/
long getRandomMsgStatus(){

    long result = INI_VALUE, lower = MIN_STATUS_MSG, upper = MAX_STATUS_MSG; 

    result = (rand() % (upper - lower + 1)) + lower; 

    return result; 
}


//populate msg description
void getMsgCodeDescription(char* pStrDescription, long RandomMsgStatus){

    switch (RandomMsgStatus)
    {
        case EVERYTHING_OK:
        {
            strcpy(pStrDescription, OK_DESCRIPTION);
            break;
        }
        case HYDRAULIC_PRESSURE_FAIL:
        {
            strcpy(pStrDescription, HP_FAIL_DESCRIPTION);
            break;
        }
        case SAFETY_BTN_FAIL:
        {
            strcpy(pStrDescription, SBTN_FAIL_DESCRIPTION);
            break;
        }
        case NO_RAW_MATERIAL:
        {
            strcpy(pStrDescription, NO_RAW_DESCRIPTION);
            break;
        }
        case OPERATION_TMP_OUT_RANGE:
        {
            strcpy(pStrDescription, TMP_OUT_RANGE_DESCRIPTION);
            break;
        }
        case OPERATOR_ERROR:
        {
            strcpy(pStrDescription, OPERATOR_ERROR_DESCRIPTION);
            break;
        }
        case MACHINE_OFFLINE:
        {
            strcpy(pStrDescription, OFFLINE__DESCRIPTION);
            break;
        }
    }

}

//function that randomly creates time between 10-30 secs
//need to call srand(time(NULL));  before calling this function in main
// original = https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRandomTimer(){

    int result = INI_VALUE, lower = MIN_SEND_TIMER, upper = MAX_SEND_TIMER; 

    result = (rand() % (upper - lower + 1)) + lower; 

    return result; 
}

//create function that LOGs activity into logfile

