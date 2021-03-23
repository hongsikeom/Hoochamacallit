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

//#include <unistd.h>
#include "../inc/dataCorruptorHeader.h"



//create function that checks for shared memory
//return shmID
int checkSharedMemory(){

    key_t shmKey = 0;
    int errnum = 0, checkCounter = 0, shmID=0;    
    MasterList *pML = NULL;             //pointer to master list

    //get sharedMemory key 
    shmKey  = ftok(".", KEY_ID_SHAREDMEM);    
        //check if error happens
        if(shmKey == ERROR_OCCURED) 
        {
            //check error with errno   
            // errnum = errno;
            // fprintf(stderr, "Value of errno: %d\n", errno);
            // fprintf(stderr, "Error: %s\n", strerror( errnum ));         
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
            printf("Attemp: %d\n", checkCounter);
            //check error with errno ???   
            // errnum = errno;
            // fprintf(stderr, "Value of errno: %d\n", errno);
            // fprintf(stderr, "Error: %s\n", strerror( errnum ));         
        }
        else {
            printf ("(CORRUPTOR) Our Shared-Memory ID is %d\n", shmID); //***DELETE
            break; }
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
         printf("Errno : %d", errnum);
         //check error with errno ???   
         // errnum = errno;
         // fprintf(stderr, "Value of errno: %d\n", errno);
         // fprintf(stderr, "Error: %s\n", strerror( errnum ));         
    }
    else if(pML == NULL){
        printf ("(CORRUPTOR) Cannot attach to Shared-Memory!\n");   //***DELETE
    }
    else{
         printf ("(CORRUPTOR) attached to Shared-Memory!\n");   //***DELETE
    }

    return pML; 
}

//create function that detach from masterList (shared memory)
//return pointer to shared memory
 int detachFromSharedMemory(MasterList * pML){

     int result = 0;

    result = shmdt(pML);

    //check if attach failed
    if(result == ERROR_OCCURED) 
     {
         //check error with errno ???   
         // errnum = errno;
         // fprintf(stderr, "Value of errno: %d\n", errno);
         // fprintf(stderr, "Error: %s\n", strerror( errnum ));   

          printf ("(CORRUPTOR) Cannot DETACH FROM Shared-Memory!\n");   //***DELETE      
    }
    else{
         printf ("(CORRUPTOR) DETACHed FROM Shared-Memory!\n");   //***DELETE    
         result = SUCCESSFUL;
    }
    
    return result; 
}

//create function that checks for queue
//return msgQID
int checkMsgQueueCorruptor(MasterList * pML){

    int smhKey = 0, msgQID = 0, errnum = 0;    

    //get msgQueue key 
    smhKey = ftok("/tmp", 'A');      
  
    msgQID = msgget(smhKey, CHECK_MSG_QUEUE);   

     //if queue doesnt exist
     if(msgQID == ERROR_OCCURED) 
     {
        
        //log MQ was not found

        //detach from shared memory
        detachFromSharedMemory(pML);
        printf ("(CORRUPTOR) DETACHed FROM Shared-Memory!\n");   //***DELETE           
     }     
    
    return msgQID;
}


//create function that randomly creates action for wheel of destruction
//need to call srand(time(NULL));  before calling this function in main
// original = https://www.geeksforgeeks.org/generating-random-number-range-c/
int getRandomWODAction(){

    int result = INI_VALUE, lower = MIN_WOD_ACTION, upper = MAX_WOD_ACTION; 

    result = (rand() % (upper - lower + 1)) + lower; 

    return result; 
}


//Action of Wheel of destruction
void getWOD(MasterList * pML, int RandomWODAction){

    pid_t dcPID = 0;
    int doesItExist = INI_VALUE, msgQID = 0, errnum = 0;
   

    switch (RandomWODAction)
    {
        case WOD_ACTION_ZERO:
        {
            //DO NOTHIN 
            break;
        }
        case WOD_ACTION_ONE:
        {
            //get DC-01 PID
            dcPID = pML->dc[DC_01].dcProcessID;  

            //check if DC-01 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_TWO:
        {
            //get DC-03 PID
            dcPID = pML->dc[DC_03].dcProcessID;  

            //check if DC-03 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_THREE:
        {
            //get DC-02 PID
            dcPID = pML->dc[DC_02].dcProcessID;  

            //check if DC-02 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_FOUR:
        {
            //get DC-01 PID
            dcPID = pML->dc[DC_01].dcProcessID;  

            //check if DC-01 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   
                
                //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_FIVE:
        {
            //get DC-03 PID
            dcPID = pML->dc[DC_03].dcProcessID;  

            //check if DC-03 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_SIX:
        {
            //get DC-02 PID
            dcPID = pML->dc[DC_02].dcProcessID;  

            //check if DC-02 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_SEVEN:
        {
            //get DC-04 PID
            dcPID = pML->dc[DC_04].dcProcessID;  

            //check if DC-04 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_EIGHT:
        {
              //DO NOTHIN 
            break;
        }
        case WOD_ACTION_NINE:
        {
            //get DC-05 PID
            dcPID = pML->dc[DC_05].dcProcessID;  

            //check if DC-05 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_TEN:
        {
            //get msgQID
            msgQID = pML->msgQueueID;  

            //kill it
            int retCode = msgctl(msgQID, IPC_RMID, NULL);  
            if(retCode == ERROR_OCCURED)
            {
                //LOG errno value                
            }      
            break;
        }
         case WOD_ACTION_ELEVEN:
        {
            //get DC-01 PID
            dcPID = pML->dc[DC_01].dcProcessID;  

            //check if DC-01 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_TWELVE:
        {
            //get DC-06 PID
            dcPID = pML->dc[DC_06].dcProcessID;  

            //check if DC-06 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_THIRTEEN:
        {
            //get DC-02 PID
            dcPID = pML->dc[DC_02].dcProcessID;  

            //check if DC-02 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_FOURTEEN:
        {
            //get DC-07 PID
            dcPID = pML->dc[DC_07].dcProcessID;  

            //check if DC-07 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_FIFTEEN:
        {
            //get DC-03 PID
            dcPID = pML->dc[DC_03].dcProcessID;  

            //check if DC-03 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_SIXTEEN:
        {
            //get DC-08 PID
            dcPID = pML->dc[DC_08].dcProcessID;  

            //check if DC-08 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
         case WOD_ACTION_SEVENTEEN:
        {
            //get msgQID
            msgQID = pML->msgQueueID;  

            //kill it
            int retCode = msgctl(msgQID, IPC_RMID, NULL);  
            if(retCode == ERROR_OCCURED)
            {
                //LOG errno value                
            }      
            break;
        }
        case WOD_ACTION_EIGHTEEN:
        {
            //get DC-09 PID
            dcPID = pML->dc[DC_09].dcProcessID;  

            //check if DC-09 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }
        case WOD_ACTION_NINETEEN:
        {
            //DO NOTHIN 
            break;
        }
        case WOD_ACTION_TWENTY:
        {
            //get DC-10 PID
            dcPID = pML->dc[DC_10].dcProcessID;  

            //check if DC-10 exists
            doesItExist = kill(dcPID,CHECK_PID_EXIST);
            if(doesItExist == ERROR_OCCURED)
            {
                errnum = errno;
                //check errno value
                if(errnum == ESRCH)
                { 
                     break;  //pid doesnt exist
                }
            }
            else{   //kill it
                kill(dcPID, SIGHUP);
            }         
            break;
        }

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

