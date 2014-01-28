#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
//#include <pthread.h>
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
  

int main(int argc,char* argv[])
{
  
  char buffer[10];
  int ilosc=10;
  printf("podaj ktore chcesz zapalic");
  do
  {
    bzero(buffer,10);
    fgets(buffer,9,stdin);
     if((buffer[0]=='0' || buffer[0]=='1')==1)
   if((buffer[1]=='0' || buffer[1]=='1')==1)
   if((buffer[2]=='0' || buffer[2]=='1')==1)
   {
     
	    zapalanie(buffer[0],buffer[1],buffer[2]);
	    bzero(buffer,10);
	    printf("zapalono\n",9);
   }
   else { 
	    printf("miga\n"); miganie(ilosc); }
   else { 
	    printf("miga\n"); miganie(ilosc); }
   else { 
	    printf("miga\n"); miganie(ilosc); }
  }
  while(buffer[3]!='k');

  return 0;
}
