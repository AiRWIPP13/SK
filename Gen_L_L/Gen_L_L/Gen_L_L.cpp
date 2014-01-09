// Gen_L_L.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <iostream>
#endif

#include "stdafx.h"

void Sorting (int tablica[], int n)
{
  int min,i,j,temp;

for (i=0;i<n-1;i++)
    {
   min=i;
   for (j=i+1;j<n;j++)
    if (tablica[j]<tablica[min]) min=j;
   temp=tablica[min];
   tablica[min]=tablica[i];
   tablica[i]=temp;
   }
printf("\nTablica posortowana:");
   for(i=0; i<n; i++) printf("\n%i",tablica[i]);
printf("\n");
}


int main (int argc, char *argv[])
{
int randomData;
int myRandomInteger;
size_t randomDataLen = 0;
int i=0;
int array[255]={};
FILE *fp;
printf("%s %s %s\n", "Wygeneruje:", argv[1], "liczb losowych");
fp = fopen("/dev/random", "r");

for(i=0;i<atoi(argv[1]);i++)
{
        fread(&myRandomInteger, 1, 4, fp);
        printf("Wygenerowalo %d: %d\n",i, myRandomInteger);
	array[i]=myRandomInteger;
}

Sorting(array, i);

fclose(fp);

getch();
return 0;
}
