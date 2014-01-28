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
  char buffer[10];
  pthread_t sluchanie;
  pthread_t wysylanie;
};

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


void * fsluchanie(void *arguments) 
{
  
   struct ArgumentyProgramu *argumenty=arguments;
   do
  {
   bzero(argumenty->buffer,10);
   argumenty->n = read(argumenty->sockfd,argumenty->buffer,9);
   if (argumenty->n < 0) error("ERROR reading from socket");
   if((argumenty->buffer[0]=='-' && argumenty->buffer[1]=='e')==1) 
      {
	printf("serwer rozlaczony\nBye\n");
	pthread_cancel(argumenty->wysylanie);
	return NULL; }
   printf("diody: %s",argumenty->buffer); 
   
   
  }
    while(argumenty->n > 0 );
    return NULL; 
}
void * fwysylanie(void *arguments)
{
  struct ArgumentyProgramu *argumenty1=arguments;
  do
  {
    //printf("Please enter the message:\n");
    bzero(argumenty1->buffer,10);
    fgets(argumenty1->buffer,9,stdin);  
    
    // argumenty1->n = write(argumenty1->sockfd,argumenty1->buffer,3);
    if((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==1 ) 
    {
      argumenty1->n = write(argumenty1->sockfd,argumenty1->buffer,9);
      sleep(1);
       return NULL; 
    }
    else {
     argumenty1->n = write(argumenty1->sockfd,argumenty1->buffer,9); }
  }
    while((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==0);
    return NULL;
}



int main(int argc,char* argv[])
{
    struct ArgumentyProgramu argumenty;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    
    if (argc < 3) {
        printf("musisz podac host i port jako argumenty programu\n");
       return 1;
    }
    argumenty.portno = atoi(argv[2]);
    argumenty.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (argumenty.sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
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
        error("ERROR connecting");
   
    printf(" 1-dioda ON\n 0-dioda OFF\n masz do dyspozycji 3 diody wpisz np 111\n ");
    printf("gdy wpiszesz inne znaki diody beda migac 3 razy\n");
   
      
   pthread_create(&argumenty.sluchanie,NULL,&fsluchanie,(void*)&argumenty);
   printf("polaczono z plyta\n");
   pthread_create(&argumenty.wysylanie,NULL,&fwysylanie,(void*)&argumenty);
    
    //pthread_join(sluchanie, NULL);
   pthread_join(argumenty.wysylanie, NULL);
   pthread_cancel(argumenty.sluchanie);
    
    close(argumenty.sockfd);
    return 0;
}

  