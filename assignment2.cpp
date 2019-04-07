#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/types.h>
//int alloc[10][10],max[10][10],available[10],need[10][10];
int alloc[5][3]={ {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} };
int max[5][3]={ {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };
int need[5][3];
int available[10]={3,3,2};
int temp[10],h[10],ans[5];
int s,i,j,count,w=0,x=0,temp1[10][10];
int n=5;  //no of processes
int m=3; //no of resources
void *fun(void *f);
void test();
pthread_mutex_t a;
/*int res_alloc()
{
printf("enter the no of process :");
scanf("%d",&n);
printf("enter the no of type of resources :");
scanf("%d",&m);
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
printf("enter allocation of resource %d to process %d :",i,j);
scanf("%d",&alloc[i][j]);
printf("enter the max  to process %d  of resources  %d :",i,j);
scanf("%d",&max[i][j]);
need[i][j]=max[i][j]-alloc[i][j];
}
//printf("enter the available resources of Type R%d",j-1);
//scanf("%d",&available[j-1]);
}
for(i=0;i<m;i++)
{
printf("enter the available resources of type R%d",i+1);
scanf("%d",&available[i]);
}
}*/

void display()
{
printf("proces  allocation max need \n ");
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

void check()
{
pthread_mutex_lock(&a);
for(i=0;i<m;i++)
{
if(temp1[s][i]<=need[s][i])
{
if(temp1[s][i]<=available[i])
{
available[i]-=temp1[s][i];
alloc[s][i]+=temp1[s][i];
need[s][i]-=temp1[s][i];
}
else
{
printf("resources are not available for grant resources :");
break;
}
}
else
{
printf("error due to max claim");
}
}
test();
pthread_mutex_unlock(&a);
}

void test()
{
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
printf("\nSAFE STATE\n");
printf("The processes that are in safe state are:\n");
for(i=0;i<n;i++)
{
printf("p[%d]->",h[i]);
}
}
printf("\n");
}

int main()
{
pthread_t p[10];
int b;
//res_alloc();
display();
test();
printf("enter no of threads need the request :");
scanf("%d",&b);
pthread_mutex_init(&a,NULL);
for(i=0;i<b;i++)
{
pthread_create(&p[i],NULL,fun,&i);
}
for(i=0;i<b;i++)
{
pthread_join(p[i],NULL);
}
}

void *fun(void *f)
{
int q=*(int* )f;
printf("thread is requseting\n",q);
pthread_mutex_lock(&a);
printf("enter the process any from 1,2,3 for requset :");
scanf("%d",&s);
for(i=0;i<m;i++)
{
printf("enter no of instance resources for type r%d :",i+1);
scanf("%d",&temp1[s][i]);
}
pthread_mutex_unlock(&a);
check();
if(x=0)
{
printf("process are safe so requset granted :");
}
else{
for(i=0;i<m;i++)
{
available[i]+=temp1[s][i];
alloc[s][i]-=temp1[s][i];
need[s][i]+=temp1[s][i];
}
}
} 
