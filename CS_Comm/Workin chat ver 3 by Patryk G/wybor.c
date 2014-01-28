#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "komunikacja.h"



struct zmienne 
{
  int portno;
  int k;
  char hostname[20];
};
  
  

void * wczytywanie(void *arguments)
{
  struct zmienne *wybieranie=arguments;
  printf("podaj numer portu ");
  scanf("%d",&wybieranie->portno);
  printf("podaj kim chcesz byc: \n 1 :serwer \n 2 : klient\n");
  scanf("%d",&wybieranie->k);
  return NULL;
}

int main(int argc,char* argv[])
{
  
  pthread_t wybor;
  struct zmienne zm_glowne;
  
   char *host=zm_glowne.hostname;
   host=argv[1];
   pthread_create(&wybor,NULL,&wczytywanie,(void*)&zm_glowne);
   pthread_join(wybor, NULL);
  printf("\nZaczynam dzialac\n Aby wyjsc z czatu nalezy wpisac -e \n tekst wysylasz po wcisnieciu <Enter> \n");
  printf("Czekam na polacznie... ");
  if(zm_glowne.k==1)
  {
    server(zm_glowne.portno);
  }
  if(zm_glowne.k==2)
  {
    if(argc==1)
  {
    printf("wywolujac jako klient nalezy podac hostname jako argument programu \n");
    return 2; }
    client(zm_glowne.portno,host);
  }
  
  return 0;
}