CXXFLAGS = -pthread
LDLIBS = -lpthread

all: Core.exe 
	ln -s Core.exe Serwer
	ln -s Core.exe Klient

Core.exe: Core.o Server_Comm.o Client_Comm.o
	gcc -lncurses -pthread -o chat.exe Core.o Server_Comm.o Client_Comm.o
Core.o: Core.c 
	gcc -c Core.c
Server_Comm.o: Server_Comm.c
	gcc -c Server_Comm.c
Client_Comm.o: Client_Comm.c
	gcc -c Client_Comm.c
clean:
	rm Server_Comm.o Core.o chat.exe Client_Comm.o Serwer Klient
