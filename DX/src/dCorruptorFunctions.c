// #===============================================================================
// # FILE : dCorruptorFunctions.c
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// #   this program emulates a contains all the functions used by the dataCorruptor
// #   by killing a DC hoochamacallit machine from the masterList or Deleting the msg Queue 
// #   used between the DR and the DC machines. The data corruptor ataches to the 
// #   shared memory managed by the DataReader.
// #===============================================================================

#include "../inc/dataCorruptorHeader.h"



//create function that checks for shared memory
//return shmID
int checkSharedMemory(){

    key_t shmKey = 0;
    int errnum = 0, checkCounter = 0, shmID=0;
    char logStr[DX_BUFF] ="";    
    MasterList *pML = NULL;             //pointer to master list

    //get sharedMemory key 
    shmKey  = ftok(".", KEY_ID_SHAREDMEM);    
    errnum = errno;
    //check if error happens
    if(shmKey == ERROR_OCCURED) 
    {
        //LOG errno value
        sprintf(logStr, "[Error Creating Shared Memory] Errno = %d", errnum);                
        logManager(DX_LOGGER, logStr);          
    }       
  
    //check if SharedMemory exists loop
    while(checkCounter <= CHECK_SM_ATTEMPS)
    {
        shmID = shmget(shmKey,sizeof (MasterList), CHECK_SM_EXISTANCE);   

        //if SharedMemory doesnt exist
        if(shmID == ERROR_OCCURED) 
        {
            //sleep for 10 seconds
            sleep(DC_CHK_SM_TIMER);
            checkCounter++;                    
        }
        else {  break; }
    }

    return shmID;
}



//create function that attach to masterList (shared memory)
//return pointer to shared memory
MasterList * attachToSharedMemory(int shmID){

    MasterList *pML = NULL;             //pointer to master list
    int errnum = 0;
    pML = (MasterList*) shmat(shmID, NULL, READ_ONLY); //attach 
    errnum = errno;

    //check if attach failed
    if(errnum == ERROR_OCCURED) 
    {
        printf("(CORRUPTOR) Error occured -- Errno : [%d] --\n", errnum);                 
    }
    
    return pML; 
}

//create function that detach from masterList (shared memory)
//return pointer to shared memory
 int detachFromSharedMemory(MasterList * pML){

     int result = 0, errnum = 0;

    result = shmdt(pML);
    errnum = errno;
    //check if attach failed
    if(result == ERROR_OCCURED) 
    {
         printf("(CORRUPTOR) Error occured -- Errno : [%d] --\n", errnum);           
    }
    else{  result = SUCCESSFUL; }
    
    return result; 
}

//create function that checks for queue
//return msgQID
int checkMsgQueueCorruptor(MasterList * pML){

    int smhKey = 0, msgQID = 0, errnum = 0;    

    //get msgQueue key 
    smhKey = ftok("/tmp", 'A');      
  
    msgQID = msgget(smhKey, CHECK_MSG_QUEUE);   
    errnum = errno;
     //if queue doesnt exist
     if(msgQID == ERROR_OCCURED) 
     {
        printf("(CORRUPTOR) Error occured -- Errno : [%d] --\n", errnum); 
        //detach from shared memory
        detachFromSharedMemory(pML);         
     }     
    
    return msgQID;
}


//create function that randomly creates action for wheel of destruction
//need to call srand(time(NULL));  before calling this function in main
// original = https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRandomWODAction(){

    int result = INI_VALUE, lower = MIN_WOD_ACTION, upper = MAX_WOD_ACTION; 

    result = (rand() % (upper - lower + 1)) + lower; 

    result = 10;
    return result; 
}


//Action of Wheel of destruction
void getWOD(MasterList * pML, int RandomWODAction){

    pid_t dcPID = 0;
    int doesItExist = INI_VALUE, msgQID = 0, errnum = 0, DC = 0;
    char logStr[LOG_STR_SIZE] ="";

    switch (RandomWODAction)
    {
        case WOD_ACTION_ZERO:
        case WOD_ACTION_EIGHT:
        case WOD_ACTION_NINETEEN: //DO NOTHIN 
        {           
            sprintf(logStr, " WOD Action %02d - Do Nothing ",RandomWODAction);
            logManager(DX_LOGGER, logStr);                       
            break;
        }
        case WOD_ACTION_ONE:
        case WOD_ACTION_FOUR:
        case WOD_ACTION_ELEVEN:
        {            
            killDC(pML,DC_01, RandomWODAction);                   
            break;
        }
        case WOD_ACTION_TWO:
        case WOD_ACTION_FIVE:
        case WOD_ACTION_FIFTEEN:
        {           
            killDC(pML,DC_03, RandomWODAction);           
            break;
        }
        case WOD_ACTION_THREE:
        case WOD_ACTION_SIX:
        case WOD_ACTION_THIRTEEN:
        {           
            killDC(pML,DC_02, RandomWODAction);       
            break;      
        }
        case WOD_ACTION_SEVEN:
        {
            killDC(pML,DC_04, RandomWODAction);      
            break;
        }       
        case WOD_ACTION_NINE:
        {
            killDC(pML,DC_05,RandomWODAction);        
            break;
        }
        case WOD_ACTION_TEN:
        case WOD_ACTION_SEVENTEEN:  //kill msgQueue
        {
            killMsgQ(pML,RandomWODAction);     
            break;
        }       
         case WOD_ACTION_TWELVE:
        {
            killDC(pML,DC_06, RandomWODAction);          
            break;
        }        
         case WOD_ACTION_FOURTEEN:
        {
            killDC(pML,DC_07, RandomWODAction);         
            break;
        }
         case WOD_ACTION_SIXTEEN:
        {
            killDC(pML,DC_08, RandomWODAction);         
            break;
        }
        case WOD_ACTION_EIGHTEEN:
        { 
            killDC(pML,DC_09, RandomWODAction);         
            break;
        }       
        case WOD_ACTION_TWENTY:
        {
            killDC(pML,DC_10, RandomWODAction);         
            break;
        }
    }

}

//kill DC in Masterlist with if they exist
int killDC(MasterList * pML,int DC_Index, int wodAction){

    int result = 0;
    int dcPID = INI_VALUE;

    //get DC-XX PID
    dcPID = pML->dc[DC_Index].dcProcessID;  

    //check if DC exists
    if(dcPID > CHECK_PID_EXIST)
    {
        //kill it
        kill(dcPID, SIGHUP);
        //log action
        logDataCorruptor(wodAction,DC_Index, dcPID,"TERMINATED"); 
        result = SUCCESSFUL;          
    }
    else
    {
        result = FAIL;
    }

    return result;
}

//kill message queue between Datacreator and Datareader
int killMsgQ(MasterList * pML, int wodAction){

    char logStr[DX_BUFF] ="";

    //get msgQID
    int msgQID = pML->msgQueueID; 

    //kill it
    int retCode = msgctl(msgQID, IPC_RMID, NULL);
    int errnum = errno;   
    if(retCode == ERROR_OCCURED)
    {
        //error
        sprintf(logStr, "WOD Action %02d : Error deleting msgQueue Errno = %d", wodAction, errnum); 
        printf("(CORRUPTOR) %s \n", logStr);                
    }
    else
    {   //log action 
        sprintf(logStr, "WOD Action %02d : DX deleted the msgQ – the DR/DCs can’t talk anymore - exiting", wodAction);
        logManager(DX_LOGGER, logStr);  
    }   
        
     

}

//function that randomly creates time between 10-30 secs to sleep app
//need to call srand(time(NULL));  before calling this function in main
// original = https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRandomSleepTime(){

    int result = INI_VALUE, lower = MIN_SLEEP_TIMER, upper = MAX_SLEEP_TIMER; 

    result = (rand() % (upper - lower + 1)) + lower; 
    return result; 
}

//create function that LOGs activity into logfile
void logDataCorruptor(int WODAction, int DCNum, int DCPid, char* WOD_Description)
{
    char logStr[DX_BUFF] ="";
    sprintf(logStr, " WOD Action %02d - DC-%02d [%d] %s",WODAction, DCNum,DCPid, WOD_Description);
    logManager(DX_LOGGER, logStr);

}

