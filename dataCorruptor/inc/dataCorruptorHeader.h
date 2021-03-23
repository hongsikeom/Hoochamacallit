// #===============================================================================
// # FILE : dataCorruptorHeader.h
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// # 	    this include file contains the necessary prototypes 
//          and constants for the dataCorruptor program 
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
#include "../../common/inc/masterList.h"
//#include "../../dataCreator/inc/dataCreatorHeader.h"  //maybe delete?
#include <signal.h>
#include <sys/shm.h>


//Struct Definition


//Constants
#define CHECK_SM_ATTEMPS    100         //value of attemps check existance of shared memory
#define KEY_ID_SHAREDMEM    16535       //key id to create message queue Key using ftok()
#define ERROR_OCCURED       -1          //return value from function when error occurs
#define CHECK_SM_EXISTANCE  0           //Only check existance of shared memory
#define READ_ONLY           0           //attach to shared memory with read-only permissions 
#define DC_CHK_SM_TIMER     10          //timer in seconds between checks if SharedMemory doesnt exists 
#define MIN_SLEEP_TIMER     10          //minimum timer in seconds for Sleeping Corruptor
#define MAX_SLEEP_TIMER     30          //max timer in seconds for Sleeping Corruptor
#define MIN_WOD_ACTION      0           //minimum value for Action in the Wheel of destruction 
#define MAX_WOD_ACTION      20          //max value for Action in the Wheel of destruction
#define INI_VALUE           -1          // initial value of timer variable
#define CHECK_PID_EXIST     0           //check process exists
#define CHECK_MSG_QUEUE     0           //value to check existance of queue 

//Wheel of Destruction Action
#define WOD_ACTION_ZERO	         0
#define WOD_ACTION_ONE	         1
#define WOD_ACTION_TWO	         2
#define WOD_ACTION_THREE	     3
#define WOD_ACTION_FOUR	         4
#define WOD_ACTION_FIVE	         5
#define WOD_ACTION_SIX	         6
#define WOD_ACTION_SEVEN	     7
#define WOD_ACTION_EIGHT	     8
#define WOD_ACTION_NINE	         9
#define WOD_ACTION_TEN	         10
#define WOD_ACTION_ELEVEN	     11
#define WOD_ACTION_TWELVE        12
#define WOD_ACTION_THIRTEEN	     13
#define WOD_ACTION_FOURTEEN	     14
#define WOD_ACTION_FIFTEEN       15
#define WOD_ACTION_SIXTEEN       16
#define WOD_ACTION_SEVENTEEN     17
#define WOD_ACTION_EIGHTEEN	     18
#define WOD_ACTION_NINETEEN	     19
#define WOD_ACTION_TWENTY	     20

//DC list
#define DC_01	                 1
#define DC_02	                 2
#define DC_03	                 3
#define DC_04	                 4
#define DC_05	                 5
#define DC_06	                 6
#define DC_07	                 7
#define DC_08	                 8
#define DC_09	                 9
#define DC_10	                 10



#define SUCCESSFUL             100
#define FAIL                -1
#define RUN                 1


//Function Prototypes
int checkSharedMemory();
MasterList * attachToSharedMemory(int shmID);
int detachFromSharedMemory(MasterList * pML);
int checkMsgQueueCorruptor(MasterList * pML);
int getRandomWODAction();
void getWOD(MasterList * pML, int RandomWODAction);
int getRandomSleepTime();