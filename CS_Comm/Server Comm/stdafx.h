// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

int server(int argc, char *argv[]);

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>
#include <sys/types.h>

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