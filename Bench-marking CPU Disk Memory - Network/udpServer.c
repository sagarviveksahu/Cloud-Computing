#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define block_size 65000


int main(void)
{
    struct sockaddr_in client, server;

    int sr_sock, i, sock_size = sizeof(server) , recv_len;
    char *pack_dest=(char *) malloc(block_size);

    if ((sr_sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *) &client, 0, sizeof(client));

    client.sin_family = AF_INET;
    client.sin_port = htons(6000);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

        if( bind(sr_sock , (struct sockaddr*)&client, sizeof(client) ) == -1)
        {
          perror("bind");
          exit(1);
        }

                while(1)
                {
                    printf("Waiting for Connection\n");
                    fflush(stdout);

                    if ((recv_len = recvfrom(sr_sock, pack_dest, block_size, 0, (struct sockaddr *) &server, &sock_size)) == -1)
                    {
                        perror("recvfrom()");
                        exit(1);
                    }

                       if (sendto(sr_sock, pack_dest, strlen(pack_dest), 0, (struct sockaddr*) &server, sock_size) == -1)
                       {
                           perror("sendto()");
                           exit(1);
                       }
                   }

                   close(sr_sock);
                   return 0;
               }
