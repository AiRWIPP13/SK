// Client Comm.cpp : Defines the entry point for the console application.
//

#define CC
#include "stdafx.h"
#define strtok_r strtok_s


int client(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

//------------> Ready! <--------------


    while(1)
    {
        printf("Napisz wiadomosc: ");
        scanf("%s" , buffer);
         
        //Wysylanie msg
        if( send(sockfd , buffer , strlen(buffer) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
         
        //Otrzymanie odp msg
        if( recv(sockfd , buffer , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("Odpowiedz :");
        puts(buffer);
    }
//Zamykanie
	close(sockfd);
	return 0;
}
