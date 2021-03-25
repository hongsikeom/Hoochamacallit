#===============================================================================
# FILE : makefile
# PROJECT : SENG2330 - Assignment #3
# PROGRAMMER : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 20,2021
# DESCRIPTION :
# 		this makefile will compile and and all source
# 		found in the "DC" folder.  
#===============================================================================

# =======================================================
#                  DataCreator
# =======================================================
# FINAL BINARY Target
./bin/DC : ./obj/dCreatorFunctions.o  ./obj/dCreatorMain.o	            
	cc  ./obj/dCreatorFunctions.o  ./obj/dCreatorMain.o  ../common/obj/loggerFunctions.o  -o ./bin/DC         
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

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	
	



