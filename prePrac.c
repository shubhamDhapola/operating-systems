#include<stdio.h>

struct Process
{
    int pid,st,ct,at,bt,tat,wt,pri ;
};

int main()
{
    int n;
    printf("enter the no. of processes ");
    scanf("%d",&n);

    int totalTAT=0,totalWT=0,idleTime=0;
    float avgTAT=0,avgWT=0,throughput=0,cpuUti=0;
   int burst_remaining[20];

  struct Process p[20];

    for(int i=0;i<n;i++)
    {
        printf("enter the at , bt of process %d ",i+1);
        scanf("%d %d %d",&p[i].at,&p[i].bt,&p[i].pri);
        burst_remaining[i]=p[i].bt;
    }

    int completed=0,prev=0, isCompleted[20];
    for(int i=0;i<n;i++)
    {
        isCompleted[i]=0;
    }
    int current_time=0;

     while(completed!=n)
     {
        int highest_priority=10000;
        int idx= -1;
        for(int i=0;i<n;i++)
        {
            if(p[i].at<=current_time && isCompleted[i]==0 && p[i].pri<highest_priority)
            {
                idx= i;
                highest_priority= p[i].pri;
            }
        }
        if(idx != -1)
        {
          if(burst_remaining[idx]==p[idx].bt)
          {
            p[idx].st= current_time;
            idleTime+= p[idx].st- prev;
          }
          burst_remaining[idx]-=1;
          current_time++;
          prev=current_time;
         
         if(burst_remaining[idx]==0)
         {
            p[idx].ct= current_time;
            p[idx].tat= p[idx].ct- p[idx].at;
            p[idx].wt= p[idx].tat- p[idx].bt;

            totalTAT+= p[idx].tat;
            totalWT+=p[idx].wt;

            isCompleted[idx]=1;
            completed++;
         }

        }
        else
        {
            current_time++;
        }
     }

     
}
