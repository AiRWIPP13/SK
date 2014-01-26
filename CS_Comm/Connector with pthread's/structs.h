#define BUFFSIZE 1024
#define ALIASLEN 32
#define OPTLEN 16
#define LINEBUFF 2048
#define BACKLOG 10
#define CLIENTS 10 //MAX KLIENTOW


//Inicjalizacja definicji
int client(int argc, char *argv[]);
int server(int argc, char *argv[]);

void *connection_handler(void *); //utrzymanie łączności

void *sendmessage(void *name);
void *listener();




