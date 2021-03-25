/* ===============================================================================
* FILE : dataReader.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 20,2021
* DESCRIPTION :
* this include file contains the necessary prototypes for the dataReader application
* ================================================================================*/


#define     RUN                     1
#define     SUCCESS      		    2        // SUCCESS
#define     FOUND        		    3        // Used when a certain DC is found in the master list
#define     DELETE_DC               4        // Delete the current DC
#define     MESSAGE_QUEUE_EXIST     5  	     // If message queue does exist
#define     NO_MESSAGE_QUEUE        6	     // If message queue does not exist
#define     CHECK_NUM_DC            7        // Start checking number of DCs
#define     SLEEP_BEFORE_START      15       // 15 seconds - Used to sleep before starting to listen to messages from DCs
#define     TIME_LIMIT              35       // 35 seconds - Used to check if any of DCs in the master list has not sent messages
                                             // for 35 seconds
#define     NO_MESSAGE              42       // Errno value (No-Message)
#define     ONE_HALF_SECONDS        1500000  // 1.5 seconds - Used to sleep before going to the next loop
#define     SHMKEY                  16535    // Shared memory key
#define     INI_VALUE               -1       // Initial value of timer variable
#define     FAILED                  -2       // Used When a operation is failed
#define     NOT_FOUND   		    -3       // Used When a certain DC is not found in the master list
#define     OUT_OF_DC_INDEX 	    -4       // ERROR - Out of the index of the dc array
#define     ERROR       		    -5       // ALL ERRORS



// Function prototypes
int createMessageQueue();
int createSharedMemory();

DCProcessIDList * deleteDC(MasterList *masterList, DCProcessIDList *dcProcessIDList, int indexToBeDeleted);
void updateDC(MasterList *masterList, long dcProcessID);
void updateDCsLastHeardFrom(MasterList *masterList, long dcProcessID, long currentTime);
DCProcessIDList *checkLastHeardFrom(MasterList *masterList, long currentTime, DCProcessIDList *dcProcessIDList);
DCProcessIDList * checkMessageFromDC(MasterList *masterList, DCProcessIDList *dcProcessIDList, int messageNum, long processID, char* msgDescription);
int checkPIDFromMasterList(MasterList *masterList, long processID);
DCProcessIDList* FreeUpResources(int qID, int shmID, DCProcessIDList* dcProcessIDList, MasterList *masterList);

void addDCprocessID(DCProcessIDList **pHead, long dcProcessID);
int findDCprocessID(DCProcessIDList *pHead, long dcProcessID);
DCProcessIDList *freeDCProcessIDList(DCProcessIDList *pHead);