#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
#define n 5             /* maximum number of processes  */               
#define m 3            /* maximum number of resource types */
int ProcCurr[5][3];     /* 3 threads(processes), 3 resources*/
int available[10]={3,3,2};        /* Available[m] =resources unallocated */
int max[5][3] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} }; /* Max[n][m] = max demand of processes n for resource m*/
int alloc[5][3] = { {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} }; /* Alloc[n][m] =resources m allocated to processes n*/
int need[5][3];       /* Need[n][m] = resources m needed by processes n         */
pthread_mutex_t a;
int i,j,count,temp[10],w=0,x=0,temp1[10][10],h[10],temp[10];
void *fun(void *f);
void display()
{
printf("proces  allocaton max need \n ");
for(i=0;i<3;i++)
{
printf("\t");
for(j=0;j<m;j++)
{
printf(" r%d ",j+1);
}
}
printf("\n");
for(i=0;i<n;i++)
{
printf("p%d\t",i+1);
for(j=0;j<m;j++)
{
printf("%d ",alloc[i][j]);
}
printf("\t");
for(j=0;j<m;j++)
{
printf("%d ",max[i][j]);
}
printf("\t");
for(j=0;j<m;j++)
{
need[i][j]=max[i][j]-alloc[i][j];
printf("%d ",need[i][j]);
}
printf("\n");
}
}

int main()
{
int q;
pthread_t p[10];
display();
if(pthread_mutex_init(&a,NULL)<0)
{
printf("something is worng try again");
}
else{
printf("enter no of threads requeired :");
scanf("%d",&q);
for(i=0;i<q;i++)
{
pthread_create(&p[i],NULL,fun,(void *)i);
}
}
for(i=0;i<q;i++)
{
pthread_join(p[i],NULL);
}
}

void *fun(void *f)
{
pthread_mutex_lock(&a);
int b=(int)a;
int q;
printf("thread id  id %d",b);
printf("enter the process id to request grant :");
scanf("%d",&q);
for(i=0;i<m;i++)
{
printf("enter instances of resources is r%d is add ;",i+1);
scanf("%d",&temp1[q][i]);
}
for(i=0;i<m;i++)
{
if(temp1[q][i]<=need[q][i])
{
if(temp1[q][i]<=available[i])
{
available[i]-=temp1[q][i];
alloc[q][i]+=temp1[q][i];
need[q][i]-=temp1[q][i];
}
else
{
printf("resources are not available for grant resources :");
break;
}
}
else
{
printf("error due to   max claim");
break;
}
x=0;
for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{ count=0;
for(int k=0;k<m;k++)
{
if(temp[j]==0&&need[j][k]<=available[k])
{
available[k]+=alloc[j][k];
count++;
if(count==m)
{
temp[j]=1;
printf("allocation  of resources to process %d has done\n",j);
h[w]=j;
w++;
}
continue;
}
break;
}
}
}
for(i=0;i<n;i++)
{
if(temp[i]==0)
{
printf("system is unsafe state\n");
x=1;
break;
}
}
if(x==0)
{
printf("\n     SAFE STATE\n");
for(i=0;i<n;i++)
{
printf("p[%d]->",h[i]);
}
}
printf("\n");
pthread_mutex_unlock(&a);
}
}
