#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX_LINE 4096
#define BUFFSIZE 4096

ssize_t total=0;

void sendfile(FILE *fp, int sockfd) 
{
    int n; 
    char sendline[MAX_LINE] = {0}; 
    while ((n = fread(sendline, sizeof(char), MAX_LINE, fp)) > 0) 
    {
	    total+=n;
        if (n != MAX_LINE && ferror(fp))
        {
            perror("Read File Error");
            exit(1);
        }
        
        if (send(sockfd, sendline, n, 0) == -1)
        {
            perror("Can't send file");
            exit(1);
        }
        memset(sendline, 0, MAX_LINE);
    }
}

int check_jpg(char buff[])
{
    char str[strlen(buff)];
    char str2[10];
    strcpy(str, buff);
    char *token;

    /* lay token dau tien */
    token = strtok(str, ".");

    /* duyet qua cac token con lai */
    while (token != NULL)
    {
        strcpy(str2, token);
        token = strtok(NULL, ".");
    }

    if (strcmp(str2, "jpg") == 0|| strcmp(str2, "png") == 0|| strcmp(str2, "bmp")== 0)
        return 1;

    return (0);
}

int main(int argc, char* argv[])
{
    if (argc != 4) 
    {
        perror("Usage: ./client <IPaddress> <Port> <Path>");
        exit(1);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        perror("Can't allocate sockfd");
        exit(1);
    }
    int SERVERPORT = atoi(argv[2]);
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) < 0)
    {
        perror("IPaddress Convert Error");
        exit(1);
    }

    if (connect(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Connect Error");
        exit(1);
    }
    
    char *filename = basename(argv[3]); 
    if (filename == NULL)
    {
        perror("Can't get filename");
        exit(1);
    }

    int a = check_jpg(filename);
    if (a == 0)
    {
        printf("Wrong file extension \n");
        return 0;
    }
    
    char buff[BUFFSIZE] = {0};
    strncpy(buff, filename, strlen(filename));
    if (send(sockfd, buff, BUFFSIZE, 0) == -1)
    {
        perror("Can't send filename");
        exit(1);
    }

    char result[10];

    recv(sockfd, result, sizeof(result), 0);
    if (strcmp(result, "exist") == 0)
    {
        printf("Error: File already exists!!\n");
        close(sockfd);
        return 0;
    }

    FILE *fp = fopen(argv[3], "rb");
    if (fp == NULL) 
    {
        perror("Can't open file");
        exit(1);
    }

    sendfile(fp, sockfd);
    printf("Send Success, NumBytes = %ld\n", total);
    fclose(fp);
    close(sockfd);
    return 0;
}


