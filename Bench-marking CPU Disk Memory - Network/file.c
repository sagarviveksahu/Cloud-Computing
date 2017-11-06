#include<stdio.h>
#include<stdlib.h>
void main()
{
    FILE *fp = fopen("read.txt","w+");
    FILE *fp1= fopen("read1.txt","w+");
    for(int i=0;i<10E8;i++)
    {
      fprintf(fp,"%s","C");
    }
    fclose(fp);
}

