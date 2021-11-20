#include "host.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide a hostname to resolve");
        exit(1);
    }

    char *hostname = argv[1];

    if(check_host(hostname))
    {
        hostname_to_ip(hostname);
    }
    else ip_to_hostname(hostname);

    return 0;
}
