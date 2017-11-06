#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include<pthread.h>
#include<time.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

FILE *fp,*fp1;
double dataTime;
struct timeval start_time,end_time;
struct thread_args {
    long memsize;
    int thread_count;
};
long long int File_size(FILE *fp)
{
  fseek(fp,0,SEEK_END);
  long long int size = (long long int)ftell(fp);
  fseek(fp,0,0);
  return size;
}
void *seqreadaccess(void *arg)
{
  long  i =0;
  long long int  file_size = File_size(fp);
	struct thread_args *params = arg;
	long  memsize = params->memsize;
	int thread_count = params->thread_count;
  char* mydata = malloc(memsize);
  gettimeofday(&start_time,NULL);
	fseek(fp,0,SEEK_SET);
  while(i<(file_size/memsize)/thread_count)
  {
    fread(mydata,memsize,1,fp);
    fflush(fp);
    i++;
  }
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
  double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
  dataTime+=(data2-data1);
}
void *randomreadaccess(void *arg)
{
  long  i =0;
  long long int  file_size = File_size(fp);
	struct thread_args *params = arg;
	long  memsize = params->memsize;
	int thread_count = params->thread_count;
  char* mydata = malloc(memsize);
  gettimeofday(&start_time,NULL);
	fseek(fp,0,0);
  while(i<(file_size/memsize)/thread_count)
  {
    
  }
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
  double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
  dataTime+=(data2-data1);
}

void *readwriteops(void *arg)
{
  long i =0;
  long long int file_size = File_size(fp);
	struct thread_args *params = arg;
	long memsize = params->memsize;
	int thread_count = params->thread_count;
  char* mydata = malloc(memsize);
  gettimeofday(&start_time,NULL);
int random;
	while(i<(file_size/memsize)/thread_count)
  {
    random = rand()%memsize;
        fseek(fp,random,SEEK_SET);
        fread(mydata,memsize,1,fp);
    i++;
  }
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
  double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
  dataTime+=(data2-data1);
}

int main(int argc,char *argv[])
{
	clock_t start, end;
  fp = fopen("read.txt","r+");
  fp1 = fopen("read1.txt","w+");
  if(!fp)
  {
    printf("File not created");
    exit(0);
  }
	float totaltime;
	int ops,thread_count;
  long block_size,memsize;
  float throughput,latency;
  long long int file_size = File_size(fp);
  ops = atoi(argv[1]);
  thread_count = atoi(argv[2]);
  block_size = atoi(argv[3]);
  switch(block_size)
	{
		case 1: memsize = 8;
			break;
		case 2: memsize = 8*1024;
			break;
		case 3: memsize = 8*1024*1024;
			break;
		case 4: memsize = 80*1024*1024;
			break;
	}
	struct thread_args readParams;
	readParams.memsize = memsize;
	readParams.thread_count = thread_count;
	pthread_t thread[thread_count];
	for(int i=0;i<thread_count;i++)
	{
		if(ops==1){
			pthread_create(&thread[i],NULL,seqreadaccess,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
		if(ops==2){
			pthread_create(&thread[i],NULL,randomreadaccess,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
		else if(ops==3){
			pthread_create(&thread[i],NULL,readwriteops,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
	}
	totaltime = dataTime;
  printf("Time_used for %d and %d operations:%f \n", thread_count,memsize,totaltime);
  throughput=(float)(file_size)/(totaltime);  //(no of loops*size*2/time taken)
  latency=(float)(totaltime)/(file_size);
  FILE *fp2 = fopen("Diskoutlat.txt","a");
  FILE *fp3 = fopen("Diskoutthvssize.txt","a");
  FILE *fp4 = fopen("Diskoutthvsthread.txt","a");
  char *c = (char *)malloc(sizeof(char)*10000);
  char *s = (char *)malloc(sizeof(char)*100);
  			c[0] = '\0';
  if(memsize==8)
  {
    printf("Latency for the 8B operations is %lf\n", latency*1000*memsize*1000);

    sprintf (s,"%d",(int)thread_count);
    strcat(c,s);
    strcat(c,"  ");

    sprintf (s,"%f",(float)latency*1000*memsize*1000);
    strcat(c,s);
    strcat(c,"\r\n");

    fwrite(c,sizeof(char)*10000,1,fp2);
    fclose(fp2);
  }
  else{
    printf("Throughput for the %ld operations is %lf MBps\n",memsize,  throughput/(1024*1024));
    sprintf (s,"%d",(int)memsize);
    strcat(c,s);
    strcat(c,"  ");

    sprintf (s,"%d",(int)ops);
    strcat(c,s);
    strcat(c,"  ");

    sprintf (s,"%d",(int)thread_count);
    strcat(c,s);
    strcat(c,"  ");

    sprintf (s,"%f",(float)throughput/(1024*1024));
    strcat(c,s);
    strcat(c,"\r\n");
    fwrite(c,sizeof(char)*10000,1,fp4);
    fclose(fp4);
  }


	return 0;

}

