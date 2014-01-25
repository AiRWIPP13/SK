//Klient

#define CC
#include "stdafx.h"
#define strtok_r strtok_s


char name[20];
int sockfd;
WINDOW *top;
WINDOW *bottom;
int line=1; 
int input=1;
int maxx,maxy; // rozmiar okna
int done=false;
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;


int client(int argc, char *argv[])
{
	
	printf("Podaj swoj username: ");

	scanf("%s",name);


//Tworz socket
	int portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	//char buffer[256];

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
	initscr();  
	getmaxyx(stdscr,maxy,maxx);

	top = newwin(maxy/2,maxx,0,0);
	bottom= newwin(maxy/2,maxx,maxy/2,0);

	scrollok(top,TRUE);
	scrollok(bottom,TRUE);
 	box(top,'|','=');
	box(bottom,'|','-');

 	wsetscrreg(top,1,maxy/2-2);
 	wsetscrreg(bottom,1,maxy/2-2);

	pthread_t threads[2];
	void *status;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   // Stwórz s/l deamons
	    pthread_create(&threads[0], &attr, sendmessage, (void *)name);
	    pthread_create(&threads[1], &attr, listener, NULL);

    // utrzymanie do finishu
	    while(!done);




    /*while(1)
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
    }*/

//Zamykanie
	close(sockfd);
	return 0;
}



void *sendmessage(void *name)
{

    char str[80];
    char msg[100];
    int bufsize=maxx-4;
    char *buffer=malloc(bufsize);

    while(1)
    {
        bzero(str,80);
        bzero(msg,100);
        bzero(buffer,bufsize);
        wrefresh(top);
        wrefresh(bottom);

        // zbierz msg
        mvwgetstr(bottom,input,2,str);

        // Utworz: "username: message"
        strcpy(msg,name);
        strncat(msg,": \0",100-strlen(str));
        strncat(msg,str,100-strlen(str));

        // sprawdz czy 'exit'
        if(strcmp(str,"exit")==0)
        {

            done = true;

            // Czyść
            endwin();      
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
            close(sockfd);
        }    

        // Send msg
        write(sockfd,msg,strlen(msg));

        // wyswietl w oknie
        mvwprintw(top,line,2,msg);


        // przesuniecie kol
        pthread_mutex_lock (&mutexsum);

        if(line!=maxy/2-2)
            line++;
        else
            scroll(top);

        // przesuniecie wie
        if(input!=maxy/2-2)
            input++;
        else
            scroll(bottom);

        pthread_mutex_unlock (&mutexsum);
    }
}


// Nasluchuj msg od serwera
void *listener()
{
    char str[80];
    int bufsize=maxx-4;
    char *buffer=malloc(bufsize);

    while(1)
    {
        bzero(buffer,bufsize);
        wrefresh(top);
        wrefresh(bottom);

        //otrzymaj wiad
        read(sockfd,buffer,bufsize);

        //Wyswietl
        mvwprintw(top,line,3,buffer);

      // przewijanie
        pthread_mutex_lock (&mutexsum);
        if(line!=maxy/2-2)
            line++;
        else
            scroll(top);
        pthread_mutex_unlock (&mutexsum);
    }
}
