#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1000

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

int main(int argc , char * argv[])
{
    if(argc < 3)
    {
        printf("ERROR , please enter server IP and port number \n !!");
    }

    char *ip_address = argv[1];
    char *port_num = argv[2];
    int port = atoi(port_num);


    int sockfd, n;
    struct sockaddr_in servaddr;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(port); 
    servaddr.sin_addr.s_addr=inet_addr(ip_address);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 
    while (1) { 
        int i = 0;
        char message[100];
        char buffer[100];
        char buffer1[100];
        printf("Sent to server : \n");
        i = scanf("%[^\n]",message);
        if(i==0) break;
        getchar();
        if(message == "")
        {
            close(sockfd);
            return 0;
        }
        sendto(sockfd,message,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
        
        printf("Get form server : \n ");
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)NULL,NULL);
        recvfrom(sockfd,buffer1,sizeof(buffer1),0,(struct sockaddr*)NULL,NULL);
        if(check_host(buffer) == 1)
        {
            printf("Official name: ");
            puts(buffer);
            printf("\nAlias name : \n");
        }
        else  
        {
            printf("Official IP: ");
            puts(buffer);
            printf("\nAlias IP : \n");
        }
        
        if(strlen(buffer1)>1)
        {
            for(int i =0;i<strlen(buffer1);i++)
            {
                if(buffer1[i] == ' ')
                {
                    printf("\n");
                }
                else printf("%c",buffer1[i]);
            }
        }
        else printf("%s",buffer1);
        puts("___________________________________");
    } 
    close(sockfd);
    return 0;
}

