#ifndef komunikacja
#define komunikacja
void error(const char *msg);
void * sluchanie_serwer(void *arguments);
void * wysylanie_serwer(void *arguments);
void * sluchanie_client(void *arguments); 
void * wysylanie_client(void *arguments);
int server(int portno);
int client(int portno,char host[] );
#endif 