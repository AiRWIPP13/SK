CXXFLAGS = -pthread
LDLIBS = -lpthread

one: Chat.exe 

two: Chat2.exe

Chat.exe: Core.o Server_Comm.o Client_Comm.o
	gcc -lncurses -pthread -o chat.exe Core.o Server_Comm.o Client_Comm.o
Core.o: Core.c 
	gcc -c Core.c
Server_Comm.o: Server_Comm.c
	gcc -c Server_Comm.c
Client_Comm.o: Client_Comm.c
	gcc -c Client_Comm.c
clean:
	rm Server_Comm.o Core.o chat.exe Client_Comm.o

Chat2.exe: Core.o Server_Comm2.o Client_Comm2.o
	gcc -lncurses -pthread -o chat2.exe Core.o Server_Comm2.o Client_Comm2.o
Server_Comm2.o: Server_Comm2.c
	gcc -c Server_Comm2.c
Client_Comm2.o: Client_Comm2.c
	gcc -c Client_Comm2.c
clean2:
	rm Server_Comm2.o Core.o chat2.exe Client_Comm2.o
