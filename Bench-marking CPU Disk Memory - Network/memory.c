#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<limits.h>
#include<string.h>
#include <sys/time.h>

double dataTime;
struct timeval start_time,end_time;
struct thread_args {
    long int memsize;
    int thread_count;
};

void seqaccess(void *arg)
{
	struct thread_args *params = arg;
	long int memsize = params->memsize;
	int thread_count = params->thread_count;
	long int blockSize=(long int)(1024*1024*1024)/(thread_count);
	char *mem2;
	mem2 = (char*)malloc(blockSize*sizeof(char));
  /*start = clock();
  if(start_min > start)
  {
    start_min = start;
  }*/
  char *mem3 = mem2;
  gettimeofday(&start_time,NULL);
	for(int i=0;i<(blockSize/memsize);i++)
	{
		memset(mem2,'#',memsize);
    mem2 = mem2+memsize;
	}
  //end = clock();
  mem2 = mem3;
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
      double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
      dataTime+=(data2-data1);
	free(mem2);
}
void randomaccess(void *arg)
{
	struct thread_args *params = arg;
	long int memsize = params->memsize;
	int thread_count = params->thread_count;
	long int blockSize=(long int)(1024*1024*1024)/(thread_count);
	char *mem2;
	mem2 = (char*)malloc(blockSize*sizeof(char));
	long int random_no;
  /*start = clock();
  if(start_min > start)
  {
    start_min = start;
  }
  */
  char *mem3 = mem2;
  gettimeofday(&start_time,NULL);
	for(int i=0;i<(blockSize/memsize);i++)
	{
		random_no = rand()%(blockSize/memsize);
    random_no = mem2 + (random_no*memsize);
		memset(random_no,'#',memsize);
	}
  //end = clock();
  mem2 = mem3;
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
      double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
      dataTime+=(data2-data1);
	free(mem2);
}

void readwriteops(void *arg)
{
	struct thread_args *params = arg;
	long int memsize = params->memsize;
	int thread_count = params->thread_count;
	int blockSize=(1024*1024*1024)/(thread_count);
	char *mem1;
	mem1 = (char*)malloc(blockSize*sizeof(char));
	char *mem2;
  char *mem3 = mem1;
  char *mem4 = mem2;
	mem2 = (char*)malloc(blockSize*sizeof(char));
  /*start = clock();
  if(start_min > start)
  {
    start_min = start;
  }*/
  gettimeofday(&start_time,NULL);
  for(int i=0;i<(blockSize/memsize);i++)
  {
  	memcpy(mem2,mem1,memsize);
    mem2 = mem2+memsize;
    mem1 = mem1+memsize;
  }
  //end = clock();
  gettimeofday(&end_time,NULL);
  double data1=(double)start_time.tv_sec+((double)start_time.tv_usec/1000000);
      double data2=(double)end_time.tv_sec+((double)end_time.tv_usec/1000000);
      dataTime+=(data2-data1);
  mem1 = mem3;
  mem2 = mem4;

	free(mem1);
	free(mem2);
}

int main(int argc,char *argv[])
{
  float totaltime;
	int ops,thread_count;
  long block_size,memsize;
  float throughput,latency;
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
	printf("%d %d %d\n", ops,thread_count,memsize);
	struct thread_args readParams;
	readParams.memsize = memsize;
	readParams.thread_count = thread_count;
	pthread_t thread[thread_count];
	for(int i=0;i<thread_count;i++)
	{
		if(ops==1){
			pthread_create(&thread[i],NULL,seqaccess,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
		if(ops==2){
			pthread_create(&thread[i],NULL,randomaccess,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
		else if(ops==3){
			pthread_create(&thread[i],NULL,readwriteops,(void *)&readParams);
      pthread_join(thread[i],NULL);
    }
	}
	//totaltime = ((float) (end - start_min)) / CLOCKS_PER_SEC;

  totaltime = dataTime;

  	printf("Time_used for %d and %d operations:%f \n", thread_count,block_size,totaltime);
    throughput=(float)(1024*1024*1024)/(totaltime);  //(no of loops*size*2/time taken)
    latency=(float)(totaltime)/(1024*1024*1024);
    if(memsize==8)
    {
      printf("Latency for the 8B operations is %lf\n", latency*memsize*1000);
    }
    else{
      printf("Throughput for the %ld operations is %lf \n",memsize,  throughput/(1024*1024));
    }
    FILE *fp2 = fopen("memoutlat.txt","a");
    FILE *fp3 = fopen("memoutthvssize.txt","a");
    FILE *fp4 = fopen("memoutthvsthread.txt","a");
    char *c = (char *)malloc(sizeof(char)*10000);
    char *s = (char *)malloc(sizeof(char)*100);
    			c[0] = '\0';
          if(memsize==8)
          {

            sprintf (s,"%d",(int)thread_count);
            strcat(c,s);
            strcat(c,"  ");

            sprintf (s,"%f",(float)latency*1000*memsize);
            strcat(c,s);
            strcat(c,"\r\n");

            fwrite(c,sizeof(char)*10000,1,fp2);
            fclose(fp2);
          }
          else{
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

