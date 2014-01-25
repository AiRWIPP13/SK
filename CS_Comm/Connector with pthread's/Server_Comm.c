// Aplikacja Serwera Komunikacji

#define SC
#include "stdafx.h"
#define strtok_r strtok_s

char *message , client_message[2000];

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int server(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, *new_sock;
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

	printf("\n Gotowy! ...\n");

// ----------> Ports Ready! <------------

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	
//Niepotrzebne
	/*  newsockfd = accept(sockfd,
		(struct sockaddr *) &cli_addr,
		&clilen);  */

//Pętla połączeń
	while(newsockfd = accept(sockfd,
		(struct sockaddr *) &cli_addr,
		&clilen))
	{
		puts("Polaczony");
		
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = newsockfd;

		if( pthread_create( &sniffer_thread , NULL , connection_handler , (void*) new_sock) < 0 )
		{
			perror("Error with create_thread!");
			return 1;
		}
		
		puts("Klient polaczony");
	}


	if (newsockfd < 0)
			error("ERROR on accept");


//Zamykanie portów
	close(newsockfd);	
	close(sockfd);
	return 0;
}

void *connection_handler(void *socket_desc)
{
    //Deskryptor
    int sock = *(int*)socket_desc;
    int read_size;
    
     
     
    //Otrzymaj msg from klient
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        sleep(1);
	//Zwróć msg
        write(sock , client_message , strlen(client_message));
    }
     
    if(read_size == 0)
    {
        puts("Rozlaczono");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Err RECV");
    }
         
    //Uwolnienie deskryptora
    free(socket_desc);
     
    return 0;
}
