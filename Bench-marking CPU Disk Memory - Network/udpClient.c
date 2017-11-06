#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<time.h>
#include<sys/time.h>
#include<malloc.h>
#include <pthread.h>

#define size 65000
#define lp_addr "127.0.0.1"
#define iter (8 * 1024 * 1024) / 64

void *connection_handler(void *);
float ops(double cpu_time_used);
char *pack_src;
char *pack_dest;
int cl_sock, sock_size,th_count;
struct sockaddr_in server;

int main(void)
{

    int i;
    sock_size = sizeof(server);
    pack_src = (char *) malloc(size);
    pack_dest = (char *) malloc(size);
    clock_t start, end;
    float cpu_time_used;
    scanf("%d", &th_count);
    pthread_t th_ar[th_count];

        if ( (cl_sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        {
            perror("socket");
            exit(1);
        }

        memset((char *) &server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons( 6000 );
        memset(pack_src,'$',size);

        if (inet_aton(lp_addr , &server.sin_addr) == 0)
        {
            fprintf(stderr, "inet_aton() failed\n");
            exit(1);
        }

        if(1)
        {
            start = clock();
            for(i=0;i<th_count;i++)
            {
                  pthread_create(&th_ar[i],NULL,connection_handler,NULL);
           }
          for(i=0;i<th_count;i++)
           {
                  pthread_join(th_ar[i],NULL);
           }
           end = clock();
           cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
           ops(cpu_time_used);
       }

       close(cl_sock);
     }

     void *connection_handler(void *socket_desc)
     {
       int i;
       for(i=0;i<iter/th_count;i++)
       {

       if (sendto(cl_sock, pack_src, strlen(pack_src) , 0 , (struct sockaddr *) &server, sock_size)==-1)
           {
               perror("sendto()");
               exit(1);
           }

         }

         if (recvfrom(cl_sock, pack_dest, size, 0, (struct sockaddr *) &server, &sock_size) == -1)
         {
             perror("recvfrom()");
             exit(1);
           }
     }
     return 0;
   }


   float ops(double cpu_time_used)
   {

     double time = cpu_time_used * 1000;
     double latancy = (double)(time)/iter;
     double band,band_mb;
     band = (double)(64 * iter * 8 * th_count)/cpu_time_used;
     band_mb = (double)(band)/1024;
     printf("latancy in milliseconds:%f\n",latancy);
     printf("throughput in Mb/sec:%f\n",band_mb);

     return 0;
   }
