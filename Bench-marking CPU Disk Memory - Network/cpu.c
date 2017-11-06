#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <immintrin.h>

float th_int();
float th_float();
float th_int_avx();
float th_float_avx();
float ops(int num_th, int ch_op, float tim);
int thread_count,ch_opr;

int main(int arg,char *argv[])
{
  clock_t start, end;
  float cpu_time_used;
  int i;
  printf("Enter 1 for int operation\n2 for int operation with avx instructions\n3 for float operations\n4 for float with avx instructions:\n");
  ch_opr = atoi(argv[1]);
  printf("Enter number of threads:\n");
  thread_count = atoi(argv[2]);
  pthread_t th_ar[thread_count];
  start = clock();
  for(i=0;i<thread_count;i++)
  {
    if(ch_opr==1){
      pthread_create(&th_ar[i],NULL,th_int,NULL);
   }else if(ch_opr==2){
      pthread_create(&th_ar[i],NULL,th_int_avx,NULL);
   }else if(ch_opr==3){
      pthread_create(&th_ar[i],NULL,th_float,NULL);
   }else{
      pthread_create(&th_ar[i],NULL,th_float_avx,NULL);
    }
    }
   for(i=0;i<thread_count;i++)
   {
     pthread_join(th_ar[i],NULL);
   }
   end = clock();
   cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
   printf("time_used for int operations:%f\n",cpu_time_used);
   ops(thread_count,ch_opr,cpu_time_used);
   return 0;
 }

 float th_int()
 {
   int a, b, i;
   int add, sub, mult;
   a = 5;
   b=6;
   for(i=0;i<1000000000/thread_count;i++)
   {
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = sub + mult
   }
   return 0;
 }

 float th_int_avx()
 {
   int i;
   __m256i ymm0, ymm1
    __m256i vec1={1,2,3,4,5,6,7,8};
   __m256i vec2={2,3,4,5,6,7,8,9};

   for (i=0; i<1000000000/thread_count; i++)
   {
     ymm0 = _mm256_add_epi32(vec1, vec2);
     ymm1 = _mm256_mul_epi32(vec1, vec2);
   }
   return 0;

 }

 float th_float()
 {
   int i;
   float a, b;
   float add, sub, mult;
   float divi;
   a = 5.0;
   b = 6.0;
   for(i=0;i<1000000000/thread_count;i++)
   {
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = a + b;
     sub = b - a;
     mult = a * b;
     a = a + a;
     b = b + b;
     add = sub + mult
   }
   return 0;
 }

 float th_float_avx()
 {
   int i;
   __m256 ymm0, ymm1, ymm2, ymm3;
   ymm0={1.1,2.2,3.1,4.1,5.1,6.1,7.1,8.1};
   ymm1={2.2,3.3,4.4,5.2,6.3,7.3,8.2,9.2};

   for(i=0; i<1000000000/thread_count; i++)
   {
     ymm2 = _mm256_mul_ps(yum0,yum1);
     ymm3 = _mm256_add_ps(yum0,yum1);
   }
   return 0;
 }
 float ops(int num_th, int ch_op, float tim)
 {
   float num_ops;
   long int iter = 1000000000;
   int instr = 16;
   num_ops = (float)(iter*instr*num_th)/tim;
   if((ch_op==1) || (ch_op==2)){
     printf("Iops:%fHz\n",(double)num_ops);
     printf("Giga Iops:%fGHz\n",num_ops/1000000000);
  }else{
     printf("Flops:%fHz\n",(double)num_ops);
     printf("Giga Flops:%fGHz\n",num_ops/1000000000);
  }
   return 0;
 }
