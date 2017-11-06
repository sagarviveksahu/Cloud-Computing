#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/time.h>
#include<malloc.h>
#include <pthread.h>

#define size 64 * 1024
#define iter (8 * 1024 * 1024) / 64

void *connection_handler(void *);
float ops(double cpu_time_used);
int cl_sock,charcount,len,th_count;
char *pack_src;
char *pack_dest;

int main(int argc , char *argv[])
{
    int i;
    struct sockaddr_in server;
    pack_src = (char *) malloc(size);
    pack_dest = (char *) malloc(size);
    clock_t start, end;
    double cpu_time_used;
    scanf("%d", &th_count);
    pthread_t th_ar[th_count];

    cl_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (cl_sock == -1)
    {
        printf("Socket Creation Failed");
      }
      puts("Socket Created");

      server.sin_addr.s_addr = inet_addr("127.0.0.1");
      server.sin_family = AF_INET;
      server.sin_port = htons( 5000 );

      memset(pack_src,'$',size);
      if (connect(cl_sock , (struct sockaddr *)&server , sizeof(server)) == -1)
      {
          perror("Connect Failed");
          return 1;
      }

      puts("Connected\n");

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
           cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
           ops(cpu_time_used);
       }
       close(cl_sock);
     }

     void *connection_handler(void *socket_desc)
     {
         int i;
         for(i=0;i<iter/th_count;i++)
         {
         if( send(cl_sock , pack_src , strlen(pack_src) , 0) == -1)
             {
                 puts("Send Failed");
             }
             if( recv(cl_sock , pack_dest , size , 0) == -1)
             {
                 puts("Receive Failed");
             }
         }

         return 0;
     }

     float ops(double cpu_time_used)
     {
  //      printf("%f",cpu_time_used);
       double tim = cpu_time_used * 1000;
  //      printf("%f",time);
       double latancy = (double)(tim)/iter;
  //      printf("%f",latancy);
       double band,band_mb;
       band = (double)(64 * iter * 8 * th_count)/cpu_time_used;
  //      printf("%f",band);
       band_mb = (double)(band)/1024;
  printf("latancy in milliseconds:%f\n",latancy);
  printf("throughput in Mb/sec:%f\n",band_mb);

  return 0;
}
