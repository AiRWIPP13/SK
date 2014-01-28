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
};
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void * sluchanie_serwer(void *arguments) 
{
  
   struct ArgumentyProgramu *argumenty=arguments;
   do
  {
   bzero(argumenty->buffer,256);
   argumenty->n = read(argumenty->newsockfd,argumenty->buffer,255);
   if (argumenty->n < 0) error("ERROR reading from socket");
   printf("client: %s",argumenty->buffer); 
   
  }
    while(argumenty->n > 0); //argumenty->buffer[0]!='e'
    return NULL;
}
void * wysylanie_serwer(void *arguments)
{
  struct ArgumentyProgramu *argumenty1=arguments;
  do
  {
    bzero(argumenty1->buffer,256);
    fgets(argumenty1->buffer,255,stdin);
    
    if((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==1) 
    {
	argumenty1->n = write(argumenty1->newsockfd,argumenty1->buffer,255);
	printf("Bye!\n");
       return NULL; 
    }
    else {
    argumenty1->n = write(argumenty1->newsockfd,argumenty1->buffer,255); }
  }
    while((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==0);
    return NULL;
}
int server(int portno)
{
     pthread_t sluchanies;
     pthread_t wysylanies;
     struct ArgumentyProgramu argumenty;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     argumenty.sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (argumenty.sockfd < 0) 
     { 
        error("ERROR opening socket");
	return 1; 
    }
     bzero((char *) &serv_addr, sizeof(serv_addr));
     argumenty.portno = portno;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(argumenty.portno);
     if (bind(argumenty.sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
     {
              error("ERROR on binding");
	      return 2; 
       
    }

    listen(argumenty.sockfd,5);
     
    
     clilen = sizeof(cli_addr);
     argumenty.newsockfd = accept(argumenty.sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (argumenty.newsockfd < 0) 
     {
          error("ERROR on accept");
	  return 3;
     }
    pthread_create(&sluchanies,NULL,&sluchanie_serwer,(void*)&argumenty);
    pthread_create(&wysylanies,NULL,&wysylanie_serwer,(void*)&argumenty);
    pthread_join(wysylanies, NULL);
    pthread_cancel(sluchanies);
    //pthread_join(sluchanies, NULL);
    close(argumenty.newsockfd);
     close(argumenty.sockfd);
     return 0;

}