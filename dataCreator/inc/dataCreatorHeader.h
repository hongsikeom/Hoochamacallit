// #===============================================================================
// # FILE : dataCreatorHeader.h
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// # 	    this include file contains the necessary prototypes 
//          and constants for the dataCreator program 
// #===============================================================================

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h> 
#include "../../common/inc/message_struct.h"

//Struct Definition


//Constants
#define CHECK_MSG_QUEUE     0           //value to check existance of queue 
#define KEY_ID              'A'       //key id to create message queue Key using ftok()
#define ERROR_OCCURED       -1          //return value from function when error occurs
#define DC_CHK_Q_TIMER      10          //timer in seconds between checks if msg Queue doesnt exists 
#define MIN_SEND_TIMER      10          //minimum timer in seconds for sending message
#define MAX_SEND_TIMER      30          //max timer in seconds for sending message
#define MIN_STATUS_MSG      0           //minimum value for status message
#define MAX_STATUS_MSG      6           //max value for status message
#define INI_VALUE           -1          // initial value of timer variable

#define SUCCESS             100
#define FAIL                -1


//Function Prototypes
int checkMsgQueue();
long getRandomMsgStatus();
int getRandomTimer();
void getMsgCodeDescription(char* pStrDescription, long RandomMsgStatus);