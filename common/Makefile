#===============================================================================
# FILE : makefile
# PROJECT : SENG2330 - Assignment #3
# PROGRAMMER : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 20,2021
# DESCRIPTION :
# 		this makefile will clean all files in the bin folder.  
#===============================================================================
# =======================================================
#                  Common Files
# =======================================================
# FINAL BINARY Target
#./bin/dataCorruptor : ./obj/dCorruptorFunctions.o  ./obj/dCorruptorMain.o	            
#	cc  ./obj/dCorruptorFunctions.o  ./obj/dCorruptorMain.o  ../common/obj/loggerFunctions.o -o ../common/bin/dataCorruptor         
#
# =======================================================
#                     Dependencies
# =======================================================                     

./obj/loggerFunctions.o : ./src/loggerFunctions.c ./inc/loggerHeader.h
	cc  -c ./src/loggerFunctions.c -o ./obj/loggerFunctions.o	
#
# =======================================================
# Other targets
# =======================================================    
# Clean
clean	:
	rm -f ./bin/*
	rm -f ./obj/*.o
