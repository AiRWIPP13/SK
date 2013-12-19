all: chat.exe

chat.exe: Core.o Server_Comm.o Client_Comm.o
	gcc -o chat.exe Core.o Server_Comm.o Client_Comm.o
Core.o: Core.c 
	gcc -c Core.c
Server_Comm.o: Server_Comm.c stdafx.h
	gcc -c Server_Comm.c
Client_Comm.o: Client_Comm.c stdafx.h
	gcc -c Client_Comm.c
celean:
	rm Server_Comm.o Core.o chat.exe Client_Comm.o
