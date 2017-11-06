#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<malloc.h>

#define size 64 * 1024

void *connection_handler(void *serv_sock)
{

  int sock = *(int*)serv_sock;
  int rcv_size;
  char *pack_dest=(char *) malloc(size);

  while( (rcv_size = recv(sock , pack_dest , size , 0)) > 0 )
  {

      write(sock , pack_dest , strlen(pack_dest));
  }

  if(rcv_size == 0)
  {
      puts("Client Disconnected");
      fflush(stdout);
  }
  else if(rcv_size == -1)
  {
      perror("Receive Failed");
    }

        free(serv_sock);

        return 0;
    }

    int main(int argc , char *argv[])
    {
        int serv_sock , cl_sock , add_size , *nw_socket, rcv_size;
        struct sockaddr_in server , client;
        char *pack_dest=(char *) malloc(size);

        serv_sock = socket(AF_INET , SOCK_STREAM , 0);
        if (serv_sock == -1)
        {
            printf("Socket not Created");
        }
        puts("Socket created");

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 5000 );

        if( bind(serv_sock,(struct sockaddr *)&server , sizeof(server)) < 0)
        {

                  perror("Bind Failed");
                  return 1;
                }
                puts("Bind Done");

                listen(serv_sock , 3);

                puts("Waiting for Client Connections");
                add_size = sizeof(struct sockaddr_in);

                while( (cl_sock = accept(serv_sock, (struct sockaddr *)&client, (socklen_t*)&add_size)) )
                {
                    puts("Connection Accepted");

                    pthread_t srvr_thread;
                    nw_socket = malloc(1);
                    *nw_socket = cl_sock;

                    if( pthread_create( &srvr_thread , NULL ,  connection_handler , (void*) nw_socket) < 0)
                    {
                        perror("Thread not created");
                        return 1;
                    }
                    pthread_join( srvr_thread , NULL);
                    puts("Handler assigned to new client");
                }

                if (cl_sock < 0)
                {
                    perror("Accept Failed");

                    return 1;
        }

        return 0;
      }
