#===============================================================================
# FILE 			: makefile
# PROJECT 		: SENG2330 - Assignment #3
# PROGRAMMER    : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 20,2021
# DESCRIPTION   : this makefile will compile and and all source
# 		          found in the "DR" folder. 
#===============================================================================


# =======================================================
#                  DataReader
# =======================================================
# FINAL BINARY Target
./bin/DR	: ./obj/dataReaderMain.o ./obj/dataReaderUtils.o ./obj/dataReaderWorker.o 
	cc ./obj/dataReaderMain.o ./obj/dataReaderUtils.o ./obj/dataReaderWorker.o ../common/obj/loggerFunctions.o  -o ../common/bin/DR


#
# =======================================================
#                  Dependencies
# =======================================================    

./obj/dataReaderWorker.o	: ./src/dataReaderWorker.c  ../common/inc/masterList.h ../common/inc/loggerHeader.h ./inc/dataReader.h ../common/inc/message_struct.h
	cc -c ./src/dataReaderWorker.c -o ./obj/dataReaderWorker.o

./obj/dataReaderUtils.o	: ./src/dataReaderUtils.c  ../common/inc/masterList.h ../common/inc/loggerHeader.h ./inc/dataReader.h ../common/inc/message_struct.h
	cc -c  ./src/dataReaderUtils.c -o ./obj/dataReaderUtils.o

./obj/dataReaderMain.o : ./src/dataReaderMain.c  ../common/inc/masterList.h ../common/inc/loggerHeader.h ./inc/dataReader.h ../common/inc/message_struct.h
	cc -c ./src/dataReaderMain.c  -o ./obj/dataReaderMain.o 


#
# =======================================================
# 					Other targets
# =======================================================     

clean	:
	rm -f ./bin/*
	rm -f ./obj/*.o
