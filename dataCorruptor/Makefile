#===============================================================================
# FILE : makefile
# PROJECT : SENG2330 - Assignment #3
# PROGRAMMER : Hongsik Eom and Janeth Santos
# FIRST VERSION : March 20,2021
# DESCRIPTION :
# 		this makefile will compile and and all source
# 		found in the "DataCorruptor" folder.  
#===============================================================================

# =======================================================
#                  DataCorruptor
# =======================================================
# FINAL BINARY Target
./bin/dataCorruptor : ./obj/dCorruptorFunctions.o  ./obj/dCorruptorMain.o	            
	cc  ./obj/dCorruptorFunctions.o  ./obj/dCorruptorMain.o  -o ../common/bin/dataCorruptor         
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dCorruptorFunctions.o : ./src/dCorruptorFunctions.c ./inc/dataCorruptorHeader.h ../common/inc/message_struct.h
	cc  -c ./src/dCorruptorFunctions.c -o ./obj/dCorruptorFunctions.o
	
./obj/dCorruptorMain.o : ./src/dCorruptorMain.c ./inc/dataCorruptorHeader.h ../common/inc/message_struct.h
	cc  -c ./src/dCorruptorMain.c -o ./obj/dCorruptorMain.o	

#
# =======================================================
# Other targets
# =======================================================                     

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	
	



