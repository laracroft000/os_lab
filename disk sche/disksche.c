#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define CYLINDERS 5000


void sort(int a[], int n)
{
    int i,j,temp;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j] > a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}


int sstf(int req[], int n, int head)
{
    int visited[N]={0};
    int total=0;
    int cur=head;

    printf("\nSSTF Path:\n%d",head);

    for(int k=0;k<n;k++)
    {
        int min=100000;
        int index=-1;

        for(int i=0;i<n;i++)
        {
            if(visited[i]==0)
            {
                int dist=abs(cur-req[i]);

                if(dist < min)
                {
                    min=dist;
                    index=i;
                }
            }
        }

        visited[index]=1;
        total=total+min;
        cur=req[index];

        printf(" -> %d",cur);
    }

    printf("\n");
    return total;
}


int look(int req[], int n, int head)
{
    int a[N];
    int total=0;
    int cur=head;

    for(int i=0;i<n;i++)
    {
        a[i]=req[i];
    }

    sort(a,n);

    printf("\nLOOK Path:\n%d",head);

   
    for(int i=0;i<n;i++)
    {
        if(a[i] >= head)
        {
            total += abs(cur-a[i]);
            cur=a[i];
            printf(" -> %d",cur);
        }
    }

   
    for(int i=n-1;i>=0;i--)
    {
        if(a[i] < head)
        {
            total += abs(cur-a[i]);
            cur=a[i];
            printf(" -> %d",cur);
        }
    }

    printf("\n");
    return total;
}


int cscan(int req[], int n, int head)
{
    int a[N];
    int total=0;
    int cur=head;

    for(int i=0;i<n;i++)
    {
        a[i]=req[i];
    }

    sort(a,n);

    printf("\nC-SCAN Path:\n%d",head);

    
    for(int i=0;i<n;i++)
    {
        if(a[i] >= head)
        {
            total += abs(cur-a[i]);
            cur=a[i];
            printf(" -> %d",cur);
        }
    }

    total += abs(cur-(CYLINDERS-1));
    cur = CYLINDERS-1;
    printf(" -> %d",cur);

   
    total += abs(cur-0);
    cur=0;
    printf(" -> %d",cur);

    
    for(int i=0;i<n;i++)
    {
        if(a[i] < head)
        {
            total += abs(cur-a[i]);
            cur=a[i];
            printf(" -> %d",cur);
        }
    }

    printf("\n");
    return total;
}


int main()
{
    int req[N];
    int head;

    srand(time(NULL));

    printf("Enter Initial Head Position (0-4999): ");
    scanf("%d",&head);

    printf("\nGenerated Requests:\n");

    for(int i=0;i<N;i++)
    {
        req[i]=rand()%CYLINDERS;
        printf("%d ",req[i]);
    }

    printf("\n");

    int sstf_move = sstf(req,N,head);
    int look_move = look(req,N,head);
    int cscan_move = cscan(req,N,head);

    
    printf("Algorithm\tTotal Head Movement\n");
   
    printf("SSTF\t\t%d\n",sstf_move);
    printf("LOOK\t\t%d\n",look_move);
    printf("C-SCAN\t\t%d\n",cscan_move);
   

    return 0;
}