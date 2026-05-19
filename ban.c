#include<stdio.h>
int main()
{
    int n=3,m=2;
    int allocation[3][2]={
        {1,0},
        {0,1},
        {1,1}
    };
    int max[3][2]={
        {1,1},
        {1,1},
        {2,2}
    };
    int available[2]={0,0};
    int need[3][2];
    int finish[3]= {0};
    int work[2];
    int safeseq[3];
    int count = 0;
    for(int i = 0 ; i <n ; i++)
    {
        for(int j = 0 ;j <m;j++)
        {
            need[i][j]=max[i][j]- allocation[i][j];
        }
    }
    for(int i = 0 ; i <m ; i++)
    {
        work[i] = available[i];
    }

    while(count < n)
    {
        int found = 0 ;
        for(int i = 0 ; i < n; i++ )
        {
            if(!finish[i])
            {
                int j;
                for(j = 0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                        break;
                }
                if(j == m)
                {
                    for(int k=0;k<m;k++)
                        work[k] = work[k]+allocation[i][k];
                    safeseq[count++]=i;
                    finish[i] = 1;
                    found = 1;

                }
            }
        }
        if(!found)
            break;
    }

    if(count == n)
    {
        printf("system is safe\n safe seq:");
        for(int i = 0;i<n;i++)
        {
            printf("%d",safeseq[i]);
        }
    }
    else
    {
        printf("system not safe\n deadlocked preocceses");
        for(int i = 0;i<n;i++)
        {
            if(!finish[i])
                printf("%d",i);
        }

    }
}