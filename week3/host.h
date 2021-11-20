#include <stdio.h>  //printf
#include <string.h> //memset
#include <stdlib.h> //for exit(0);
#include <sys/socket.h>
#include <errno.h> //For errno - the error number
#include <netdb.h> //hostent
#include <arpa/inet.h>

struct hostent *he;
struct hostent *temp;
struct in_addr **addr_list;
struct in_addr addr;

int hostname_to_ip(char *hostname);
int ip_to_hostname(char* hostname);
int check_host(char* hostname);




