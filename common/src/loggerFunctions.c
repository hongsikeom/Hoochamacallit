// #===============================================================================
// # FILE : loggerFunctions.c
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// #   this program emulates a contains all the functions used to log entries 
// #   in the correspondant log file of the DataReader, DataCreator and DataCorruptor
// #===============================================================================


#include "../inc/loggerHeader.h"


//LOGs activity into logfile based on the loggerOption (DC, DR or DX)
int logManager(int loggerOption, char* logMsg) {

    int result = 0;

    switch(loggerOption)
    {
        case DC_LOGGER:
        {
            //log into DataCreator Logfile
            result = logEntry(DC_LOG_PATH, logMsg);
            break;
        }            
        case DR_LOGGER:
        {
            //log into DataReader Logfile
            result = logEntry(DR_LOG_PATH, logMsg);
            break;
        }           
        case DX_LOGGER:
        {
            //log into DataCorruptor Logger
            result = logEntry(DX_LOG_PATH, logMsg);
            break;
        }

    }
  
  return result;
}



//log entry into log file
int logEntry(char* loggerFilePath, char* logEntry){

     int result = 0;
     char timeStr[TIME_LOG_SIZE] = "";
     char logEntryStr[LOG_STR_SIZE] = "";
     time_t currentTime;
     struct tm * timeptr = NULL;

    //build time string
    time ( &currentTime );
    timeptr = localtime( &currentTime ); 
    sprintf(timeStr, "[%4d-%02d-%02d %.2d:%.2d:%.2d] ", TIME_MIN_YEAR + timeptr->tm_year, TIME_MIN_MONTH + timeptr->tm_mon, timeptr->tm_mday,   
    timeptr->tm_hour,timeptr->tm_min, timeptr->tm_sec);
    
    //build log string
    sprintf(logEntryStr, "%s %s", timeStr, logEntry);
    printf("%s\n", logEntryStr); //DELETE *******************


    FILE *pLogfile = NULL;
    
    //open or create log file
    pLogfile = fopen(loggerFilePath, "a");    
    if (pLogfile == NULL) {
        printf("Can NOT open %s for Logging.\n", loggerFilePath); 
        result = LOG_FAIL;       
    }
    else
    {
        // Insert log msg
        fprintf(pLogfile,"%s",logEntryStr);   
        result = LOG_SUCCESS;     
    }  
 
    //close file
    fclose(pLogfile);

    return result;
}



//create function that LOGs activity into logfile
void logDataReader(int DCindex, long dcPID, char* event, int msgCode, char* msgDescription, int flag)
{
    char logStr[DR_BUFF] ="";
    if (flag == NON_RESPONSIVE)
    {
        sprintf(logStr, " DC-%02d [%ld] removed from master list - NON-RESPONSIVE\n", DCindex ,dcPID);
    }
    else
    {
        sprintf(logStr, " DC-%02d [%ld] %s - MSG RECEIVED - Status %d (%s)\n", DCindex ,dcPID, event, msgCode, msgDescription);
    }
    
    logManager(DR_LOGGER, logStr);

}