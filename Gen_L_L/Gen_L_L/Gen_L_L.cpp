// Gen_L_L.cpp: Okre�la punkt wej�cia dla aplikacji konsoli.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "stdafx.h"

int main (int argc, char *argv[]) 
{
	
int randomData;
int myRandomInteger;
size_t randomDataLen = 0;
int i=0;
FILE *fp;
printf("%s %s %s\n", "Generuje:", argv[1], "liczb losowych");
fp = fopen("/dev/random", "r");

for(i=0;i<atoi(argv[1]);i++)
{
	fread(&myRandomInteger, 1, 4, fp);
	printf("Wygenerowalo %d: %d\n",i, myRandomInteger);
}

fclose(fp);
return 0;

}
