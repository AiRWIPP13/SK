#include "server.h"
#include "client.h"

int main (int argc, char *argv[])
{
	if (argc==2)
		server( argc, argv);
	else 
		client(argc, argv);

	return 0;
}

