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
#include <sys/ipc.h>
#include <sys/ioctl.h>
#include <fcntl.h>


#define LED0 "/sys/class/leds/test/brightness"
#define LED1 "/sys/class/leds/led2/brightness"
#define LED2 "/sys/class/leds/led3/brightness"
//#define LED0 "brightness1.txt"
//#define LED1 "brightness2.txt"
//#define LED2 "brightness3.txt"
struct ArgumentyProgramu
{
  int sockfd;
  int newsockfd;
  int portno;
  int n;
  char buffer[10];
};
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void zapalanie(char dat0,char dat1,char dat2)
{
	int f_led0, f_led1, f_led2;
	unsigned char i = 0;
	//unsigned char dat0, dat1, dat2;
	if((f_led0 = open(LED0, O_RDWR)) < 0){
		printf("error in open %s",LED0);
		//return -1;
	}
	if((f_led1 = open(LED1, O_RDWR)) < 0){
		printf("error in open %s",LED1);
		//return -1;
	}
	if((f_led2 = open(LED2, O_RDWR)) < 0){
		printf("error in open %s",LED2);
		//return -1;
	}
	//for(;;){
	//i++;
		//dat0 = i&0x1 ? '1':'0';
		//dat1 = (i&0x2)>>1 ? '1':'0';
		//dat2 = (i&0x4)>>2 ? '1':'0';
		write(f_led0, &dat0, sizeof(dat0));
		write(f_led1, &dat1, sizeof(dat1));
		write(f_led2, &dat2, sizeof(dat2));
		//usleep(300000);
	//}
		
}
void miganie(int ilosc)
{
  char dat0='1';
  char dat1='0';
  char dat2='0';
  int i=0;
  char tmp;
  while(i<ilosc)
  {
	zapalanie(dat0,dat1,dat2);
	tmp=dat0;
	dat0=dat2;
	dat2=dat1;
	dat1=tmp;
	i=i+1;
	sleep(1);
  }
}
  


void * sluchanie_serwer(void *arguments) 
{
  
   struct ArgumentyProgramu *argumenty=arguments; 
   do
  {
   bzero(argumenty->buffer,10);
   argumenty->n = read(argumenty->newsockfd,argumenty->buffer,9);
   if (argumenty->n < 0) error("ERROR reading from socket");
   printf("client: %s",argumenty->buffer);
   //sleep(0.5);
   if((argumenty->buffer[0]=='-' && argumenty->buffer[1]=='e')==1) 
      {
	printf("client rozlaczony\naby wyjsc wpisz -e\nBye\n"); }
	//return NULL; }
   
   if((argumenty->buffer[0]=='0' || argumenty->buffer[0]=='1')==1)
   if((argumenty->buffer[1]=='0' || argumenty->buffer[1]=='1')==1)
   if((argumenty->buffer[2]=='0' || argumenty->buffer[2]=='1')==1)
   {
     
	    zapalanie(argumenty->buffer[0],argumenty->buffer[1],argumenty->buffer[2]);
	    bzero(argumenty->buffer,10);
	    argumenty->n = write(argumenty->newsockfd,"zapalono\n",9);
   }
   else { bzero(argumenty->buffer,10);
	    argumenty->n = write(argumenty->newsockfd,"miga\n",9); miganie(10); }
   else { bzero(argumenty->buffer,10);
	    argumenty->n = write(argumenty->newsockfd,"miga\n",9); miganie(10); }
   else { bzero(argumenty->buffer,10);
	    argumenty->n = write(argumenty->newsockfd,"miga\n",9); miganie(10); }
   
   
  }
    while(argumenty->n > 0); //argumenty->buffer[0]!='e'
    return NULL;
}
void * wysylanie_serwer(void *arguments)
{
  struct ArgumentyProgramu *argumenty1=arguments;
  do
  {
    bzero(argumenty1->buffer,10);
    fgets(argumenty1->buffer,9,stdin);
    
    if((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==1) 
    {
	argumenty1->n = write(argumenty1->newsockfd,argumenty1->buffer,9);
	printf("Bye!\n");
       return NULL; 
    }
    else {
    argumenty1->n = write(argumenty1->newsockfd,argumenty1->buffer,9); }
  }
    while((argumenty1->buffer[0]=='-' && argumenty1->buffer[1]=='e')==0);
    return NULL;
}
int main(int argc,char* argv[])
{
     if(argc<2)
     {
       printf("musisz podac port jako argument programu  \n");
       return 1;
     }
     pthread_t sluchanies;
     pthread_t wysylanies;
     struct ArgumentyProgramu argumenty;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	argumenty.portno=atoi(argv[1]);
     argumenty.sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (argumenty.sockfd < 0) 
     { 
        error("ERROR opening socket");
	return 1; 
    }
     bzero((char *) &serv_addr, sizeof(serv_addr));
     //portno = portno;
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
     printf("Zaczynam nasluchiwac polecen\n");
    pthread_create(&sluchanies,NULL,&sluchanie_serwer,(void*)&argumenty);
    pthread_create(&wysylanies,NULL,&wysylanie_serwer,(void*)&argumenty);
    pthread_join(wysylanies, NULL);
    pthread_cancel(sluchanies);
    //pthread_join(sluchanies, NULL);
    close(argumenty.newsockfd);
     close(argumenty.sockfd);
     return 0;

}
