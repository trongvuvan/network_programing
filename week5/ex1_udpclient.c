#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<string.h>
#define MAXLINE 1000 
 
int main(int argc, char *argv[]) 
{
	if(argc < 3){
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);

	int sockfd, n; 
	struct sockaddr_in servaddr; 
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr(ip_address); 
	servaddr.sin_port = htons(port); 
	servaddr.sin_family = AF_INET; 
		
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

	do {
		int g= 0;
		char buffer[100];
		char message[100];
		// get message
		printf("Send to server: ");
		//g = fgets(message,sizeof(message),stdin);
		g = scanf("%[^\n]", message); 
		if (g == 0) break;
		getchar();
		sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	    printf("Get form server : \n");
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
		puts(buffer); 
		recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
		puts(buffer);
		puts("-------------------------");
	}while(1);	
	close(sockfd); 
	return 0;
}
