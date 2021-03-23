#===============================================================================
# FILE 			: makefile
# PROJECT 		: SENG2330 - Assignment #3
# PROGRAMMER    : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 19,2021
# DESCRIPTION   : This file contains commands to build and clean the program. 
#===============================================================================

# Build
./bin/dataReader	: ./obj/dataReaderMain.o ./obj/dataReaderUtils.o ./obj/masterListWorker.o 
	cc ./obj/dataReaderMain.o ./obj/dataReaderUtils.o ./obj/masterListWorker.o  -o ../common/bin/dataReader

./obj/masterListWorker.o	: ./src/masterListWorker.c  ../common/inc/masterList.h ./inc/dataReader.h ./inc/semaphoreStruct.h ../common/inc/message_struct.h
	cc -c ./src/masterListWorker.c -o ./obj/masterListWorker.o

./obj/dataReaderUtils.o	: ./src/dataReaderUtils.c  ../common/inc/masterList.h ./inc/dataReader.h ./inc/semaphoreStruct.h ../common/inc/message_struct.h
	cc -c  ./src/dataReaderUtils.c -o ./obj/dataReaderUtils.o

./obj/dataReaderMain.o : ./src/dataReaderMain.c  ../common/inc/masterList.h ./inc/dataReader.h ./inc/semaphoreStruct.h ../common/inc/message_struct.h
	cc -c ./src/dataReaderMain.c  -o ./obj/dataReaderMain.o 


# Clean

all	: ./bin/dataReader

clean	:
	rm -f ./bin/*
	rm -f ./obj/*.o
