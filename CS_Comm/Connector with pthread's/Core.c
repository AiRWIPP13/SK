// Core.cpp : Rdzeń

#include "stdafx.h"


int main(int argc, char *argv[])
{
	printf("Uruchamiam jako: "); 

	if (argc == 2) {
	printf("\n -> Serwer\n");	
	server(argc, argv); 
	}
	else if (argc == 3) {
		printf("\n -> Klient\n");
		client(argc, argv);
		}
		else printf("\n Error: \n Użycie: \n -> Klient \n ./chat.exe adres_serwera port \n ->Serwer \n ./chat.exe port \n");
	return 0;
}

