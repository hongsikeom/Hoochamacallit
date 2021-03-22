// #===============================================================================
// # FILE : message_struct.h
// # PROJECT : SENG2330 - Assignment #3
// # PROGRAMMER : Hongsik Eom and Janeth Santos
// # FIRST VERSION : March 20,2021
// # DESCRIPTION :
// # 		this  file contains the message structure between  
// #        client and server 
// #===============================================================================

//constants
#define MSG_LEN 121     //char length of message 


typedef struct MSG_CONTENT
{
	long message_code;
	char msgDescription[MSG_LEN];
	pid_t machinePID;
	
} MESSAGECONTENT;


// typedef struct MSG_ENVELOPE 
// {
// 	long type;
// 	MESSAGECONTENT data;
// } MSGENVELOPE;


//STATUS MSG
#define EVERYTHING_OK	         0
#define	HYDRAULIC_PRESSURE_FAIL	 1
#define SAFETY_BTN_FAIL       	 2
#define NO_RAW_MATERIAL     	 3
#define OPERATION_TMP_OUT_RANGE	 4
#define OPERATOR_ERROR           5
#define MACHINE_OFFLINE          6

//STATUS MSG DESCRIPTION
#define OK_DESCRIPTION	            "EVERYTHING is OKAY"
#define	HP_FAIL_DESCRIPTION         "Hydraulic Pressure Failure"	 
#define SBTN_FAIL_DESCRIPTION       "Safety Button Failure"
#define NO_RAW_DESCRIPTION     	    "No Raw Material in the Process"
#define TMP_OUT_RANGE_DESCRIPTION	"Operating Temperature Out of Range"
#define OPERATOR_ERROR_DESCRIPTION  "Operator Error"
#define OFFLINE__DESCRIPTION        "Machine is off-line"