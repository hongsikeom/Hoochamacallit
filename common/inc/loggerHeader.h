/* ===============================================================================
* FILE : loggerHeader.h
* PROJECT : SENG2330 - Assignment 3
* PROGRAMMER : Hongsik Eom and Janeth Santos
* FIRST VERSION : March 20,2021
* DESCRIPTION : This include file contains the necessary constants and prototypes 
* for the logger functions.
* ================================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h> 


//Constants
#define DC_LOG_PATH     "/tmp/dataCreator.log"           //path for DataCreator log file
#define DR_LOG_PATH     "/tmp/dataMonitor.log"           //path for DataReader log file
#define DX_LOG_PATH     "/tmp/dataCorruptor.log"         //path for DataCorruptor log file

#define DC_LOGGER       1           //DataCreator log option
#define DR_LOGGER       2           //DataReader  log option
#define DX_LOGGER       3           //DataCorruptor log option
#define TIME_LOG_SIZE   25          //size of string for current time
#define TIME_MIN_YEAR   1900        //year 1900
#define TIME_MIN_MONTH  1           //add 1 month since tm_month goes from 0-11
#define LOG_STR_SIZE    251         //size of log string
#define LOG_FAIL        -1          // failed to log entry
#define LOG_SUCCESS      1          // Success to log entry

#define DR_BUFF             221         //buffer for string
#define DR_ERROR            -1          //error occurred 
#define DR_PERMISSION       432         // 0660 permission for creating queue and shared memory
#define FLAG_ON             1 
#define FLAG_OFF            0
#define NON_RESPONSIVE      5


// Function prototypes  
int logManager(int loggerOption, char* logMsg);    
int logEntry(char* loggerFilePath, char* logEntry);
void logDataReader(int DCindex, long dcPID, char* event, int msgCode, char* msgDescription, int flag);
