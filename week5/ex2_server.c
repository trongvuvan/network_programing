#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include <errno.h> 
#include <netdb.h> 

#define MAXLINE 1000 

struct hostent *he;
struct hostent *temp;
struct in_addr **addr_list;
struct in_addr addr;

int check_host(char* hostname)
{
    int count=0;
    for(int i =0;i<strlen(hostname);i++){
        if((hostname[i] >= '0' && hostname[i] <= '9' )|| hostname[i]=='.')
        {
            count++;
        }
    }
    if(count==strlen(hostname)) return 0;
    else return 1;
}

int main(int argc,char* argv[])
{
    if(argc < 2)
    {
        printf("Enter port number ,please \n");
        return 0;
    }
    char *port_number = argv[1];
    int port = atoi(port_number);

    char mess1[1000],mess2[100];
    char buffer[100];
    int listenfd,len;
    struct sockaddr_in servaddr,cliaddr;
    printf("Server is listenning : \n\n");
    bzero(&servaddr,sizeof(servaddr));

    listenfd = socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    servaddr.sin_family = AF_INET;
    
    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    while(1)
    {
        len = sizeof(cliaddr);
        int n = recvfrom(listenfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
        buffer[n] ='\0';
        
        addr.s_addr =inet_addr(buffer);
        he = gethostbyaddr( &addr, 4, AF_INET);
        temp = gethostbyname(buffer);
        if (he != NULL){
        //printf("Official name: %s\n", he->h_name);
        sendto(listenfd,he->h_name,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        //printf("Alias name:\n");
        for (int i = 0; he->h_aliases[i] != NULL; i++)
        {
            printf("%s\n", he -> h_aliases[i]);
            strcat(mess1,he -> h_aliases[i]);
            strcat(mess1," ");
        }
        if(strlen(mess1) > 1)
        {
            sendto(listenfd,mess1,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        }
        else{
            strcpy(mess1," ");
            sendto(listenfd,mess1,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        }
        memset(mess1,0,strlen(mess1));
    }else if (temp != NULL){
        addr.s_addr =  *(int*)(temp->h_addr_list[0]);
        //printf("Offical IP: %s\n",inet_ntoa(addr));
        sendto(listenfd,inet_ntoa(addr),MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        //printf("Alias IP: \n");
        for (int i = 1; temp->h_addr_list[i] != NULL; i++) {
            addr.s_addr = *((uint32_t*) temp->h_addr_list[i]);
            //printf("%s\n", inet_ntoa(addr));
            strcat(mess1,inet_ntoa(addr));
            strcat(mess1," ");
        }
        if(strlen(mess1) > 1)
        {
            sendto(listenfd,mess1,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        }
        else{
            strcpy(mess1," ");
            sendto(listenfd,mess1,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
        }
        memset(mess1,0,strlen(mess1));
    }
    else
    {
        //printf("No Information found\n");
        strcpy(mess2,"No information found");
        sendto(listenfd,mess2,MAXLINE,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

    }
    }
}
