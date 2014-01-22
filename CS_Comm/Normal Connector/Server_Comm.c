// Aplikacja Serwera Komunikacji

#define SC
#include "stdafx.h"
#define strtok_r strtok_s


void error(const char *msg)
{
	perror(msg);
	exit(1);
}


int server(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	

//--------------> Start obsługi wyjatkow + Otwarcie portów <--------------
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	printf("\n Ready for connection ...\n");

// ----------> Ports Ready! <------------

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
		(struct sockaddr *) &cli_addr,
		&clilen);

	if (newsockfd < 0)
		error("ERROR on accept");

	bzero(buffer, 256);
	n = read(newsockfd, buffer, 255);

	if (n < 0) error("ERROR reading from socket");

	printf("Wiadomosc: %s\n", buffer);
	n = write(newsockfd, "Otrzymano.", 18);

	if (n < 0) error("ERROR writing to socket");



//Zamykanie portów
	close(newsockfd);	
	close(sockfd);
	return 0;
}
