#include <stdio.h>

int main()
{
    int m, n;
    printf("enter the no. of processes and resources -");
    scanf("%d %d", &m, &n);
    int maxReq[10][10], alloc[10][10], need[10][10], avail[10];
    for (int i = 0; i < m; i++)
    {
        printf("enter the allocated resources for process %d -", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&alloc[i][j]);
        }
    }
     for (int i = 0; i < m; i++)
    {
        printf("enter the max resources req for process %d -", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&maxReq[i][j]);
            need[i][j]= maxReq[i][j]-alloc[i][j];
        }
    }
    printf("enter the total resources available -");
     for (int i = 0; i < n; i++)
    {
       scanf("%d",&avail[i]);
    }

    int completed=0;
    int seq[10],visited[10], count=0;
    for(int i=0;i<m;i++)
    {
        visited[i]=0;
    }
     
    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            if(visited[i]==0)
            {
                int flag=0;
                for(int j=0;j<n;j++)
                {
                    if(avail[j]<need[i][j])
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    seq[count++]=i;
                    for(int y=0;y<n;y++)
                    {
                        avail[y]+= alloc[i][y];
                    }
                    visited[i]=1;
                }

            }
        }
    }
 int flag=0;
 for(int i=0;i<m;i++)
 {
    if(visited[i]==0)
    {
        flag=1;
        printf("system is not safe ");
        return 0;
    }
 }
 printf("the safe sequence is ");
 for(int i=0;i<m;i++)
 {
    printf("p[%d]->",seq[i]);
 }
 return 0;
   
}