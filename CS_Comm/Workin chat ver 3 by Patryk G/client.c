#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>
#include <unistd.h>
struct ArgumentyProgramu
{
  int sockfd;
  int newsockfd;
  int portno;
  int n;
  char buffer[256];
  pthread_t sluchanie;
  pthread_t wysylanie;
};


void * sluchanie_client(void *arguments) 
{
  
   struct ArgumentyProgramu *argumenty=arguments;
   do
  {
   bzero(argumenty->buffer,256);
   argumenty->n = read(argumenty->sockfd,argumenty->buffer,255);
   if (argumenty->n < 0) error("ERROR reading from socket");
   if((argumenty->buffer[0]=='-' && argumenty->buffer[1]=='e')==1) 
      {
	printf("serwer rozlaczony\nBye\n");
	pthread_cancel(argumenty->wysylanie);
	return NULL; }
   printf("server: %s",argumenty->buffer); 
   
   
  }
    while(argumenty->n > 0 );
    return NULL;
}
void * wysylanie_client(void *arguments)
{
  struct ArgumentyProgramu *argumenty1=arguments;
  do
  {
    bzero(argumenty1->buffer,256);
    fgets(argumenty1->buffer,255,stdin);  
    if((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==1 ) 
    {
	bzero(argumenty1->buffer,256);
	strcpy(argumenty1->buffer,"client rozlaczony wpisz -e aby rowniez sie rozlaczyc\n");
	//printf("spr rozlaczanie: %s",argumenty1->buffer); 
	argumenty1->n = write(argumenty1->sockfd,argumenty1->buffer,255);
	sleep(1); //poczekac na wyslanie komunikatu
       return NULL; 
    }
    else {
     argumenty1->n = write(argumenty1->sockfd,argumenty1->buffer,255); }
  }
    while((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==0);
    return NULL;
}



int client(int portno,char host[] )
{
    struct ArgumentyProgramu argumenty;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    argumenty.portno = portno;
    argumenty.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (argumenty.sockfd < 0) 
    {
        error("ERROR opening socket");
	return 4;
    }
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(argumenty.portno);
    if (connect(argumenty.sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        error("ERROR connecting");
	return 6;
    }
  
   pthread_create(&argumenty.sluchanie,NULL,&sluchanie_client,(void*)&argumenty);
   pthread_create(&argumenty.wysylanie,NULL,&wysylanie_client,(void*)&argumenty);
   pthread_join(argumenty.wysylanie, NULL);
   pthread_cancel(argumenty.sluchanie);
   close(argumenty.sockfd);
   return 0;
    
}

  