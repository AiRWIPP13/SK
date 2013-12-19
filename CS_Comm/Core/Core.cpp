// Core.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
int server(int argc, char *argv[]);
int client(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if (argc == 2)
		server(argc, argv);
	else
		client(argc, argv);

	return 0;
}

