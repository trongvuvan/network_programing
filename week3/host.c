#include "host.h"

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
int hostname_to_ip(char *hostname)
{
    int i;
    he = gethostbyname(hostname);
    if (he == NULL)
    {                        
        printf("No infomation found !! \n");
        exit(1);
    }

    printf("Official name is: %s\n", he->h_name);
    printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)he->h_addr));
    printf("Alias addresses: \n");
    addr_list = (struct in_addr **)he->h_addr_list;
    for (i = 0; addr_list[i] != NULL; i++)
    {

        printf("%d: %s \n",i+1,inet_ntoa(*addr_list[i]));
    }

    printf("\n");
    return 0;
}

int ip_to_hostname(char *hostname){
    
    inet_aton(hostname, &addr);
    he = gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if ( he == NULL) {
		printf("No infomation found !! \n");
		exit(1);
	}
    printf("Host name: %s\n", he->h_name);

    temp = gethostbyname(he->h_name);
    printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)temp->h_addr));
    printf("Alias addresses: \n");
    addr_list = (struct in_addr **)temp->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++)
    {

        printf("%d: %s \n",i+1,inet_ntoa(*addr_list[i]));
    }

    printf("\n");
    return 0;
}