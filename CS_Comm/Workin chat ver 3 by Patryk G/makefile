all:program

program:wybor.o client.o server.o 
	gcc -o program wybor.o client.o server.o  -D_REENTRANT -lpthread -Wall

wybor.o:wybor.c
	gcc -c wybor.c -pthread
	
server.o:server.c
	gcc -c server.c -pthread
	
client.o:client.c
	gcc -c client.c -pthread
clean:
	rm -f wybor.o