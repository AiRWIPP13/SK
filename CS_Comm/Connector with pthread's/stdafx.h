
//Inicjalizacja definicji
int client(int argc, char *argv[]);
int server(int argc, char *argv[]);

void *connection_handler(void *); //utrzymanie łączności


//Bibl. linuxa
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <pthread.h>


//Bibl. Windowsa
#ifdef WIN32
#include <winsock2.h>
WORD versionWanted = MAKEWORD(1, 1);
WSADATA wsaData;
//WSAStartup(versionWanted, &wsaData);
#include<WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#endif

