#===============================================================================
# FILE : makefile
# PROJECT : SENG2330 - Assignment #3
# PROGRAMMER : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 20,2021
# DESCRIPTION :
# 		this makefile will compile and and all source
# 		found in the "DataCreator" folder.  
#===============================================================================

# =======================================================
#                  DataCreator
# =======================================================
# FINAL BINARY Target
./bin/dataCreator : ./obj/dCreatorFunctions.o  ./obj/dCreatorMain.o	            
	cc  ./obj/dCreatorFunctions.o  ./obj/dCreatorMain.o  -o ./bin/dataCreator         
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dCreatorFunctions.o : ./src/dCreatorFunctions.c ./inc/dataCreatorHeader.h ../common/inc/message_struct.h
	cc  -c ./src/dCreatorFunctions.c -o ./obj/dCreatorFunctions.o
	
./obj/dCreatorMain.o : ./src/dCreatorMain.c ./inc/dataCreatorHeader.h ../common/inc/message_struct.h
	cc  -c ./src/dCreatorMain.c -o ./obj/dCreatorMain.o	

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/myApp # ********DELETE IT

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	



