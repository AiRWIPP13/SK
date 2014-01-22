// Client Comm.cpp : Defines the entry point for the console application.
//

#define CC
#include "stdafx.h"
#define strtok_r strtok_s

/*void error(const char *msg)
{
	perror(msg);
	exit(1);
}
*/

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



	printf("Napisz wiadomosc: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));

	if (n < 0)
		error("ERROR writing to socket");

	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);

	if (n < 0)
		error("ERROR reading from socket");

	printf("%s\n", buffer);

//Zamykanie
	close(sockfd);
	return 0;
}