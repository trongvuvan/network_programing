// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Please input IP address and port number\n");
		return 0;
	}
	char *ip_address = argv[1];
	char *port_number = argv[2];
	int port = atoi(port_number);
	int sock = 0;
	struct sockaddr_in serv_addr;


	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address\n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	
	while(1)
	{
		// send message to server
		// return message after split string
		int valread = 0;
		char buffer[1024] = {0};
		char buffer2[1024] = {0};
		int g = 0;
		char message[100];
		// input message
		printf("\nSend to server : ");
		g = scanf("%[^\n]", message);
		// if(strcmp(message,"\n")==0)
		// {
		// 	printf("Disconnect!!");
		// 	return 0;
		// }
		if (g == 0)
			break;
		getchar();
		// send message to server
		send(sock, message, strlen(message), 0);

		// get message from server
		valread = read(sock, buffer, 1024);
		printf("Get from server:\n%s\n", buffer);
		if (strcmp(buffer, buffer2) != 0)
		{
			valread = read(sock, buffer2, 1024);
			printf("%s\n", buffer2);
		}
		puts("-------------------------");
	}

	return 0;
}
