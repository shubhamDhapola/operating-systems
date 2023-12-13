#include<stdio.h>

struct Process 
{
    int pid;
    int wt;
    int tat;
    int at;
    int bt;
    int st;
    int ct;
};

int main()
{
    int totalTAT=0,totalWT=0,totalIdle=0;
    float avgTAT=0, avgWt=0,throughput=0,cpuUti=0;
    int n;
    printf("enter the no. of processes ");
    scanf("%d",&n);
    int burst_remaining[100],is_completed[100];
    for(int i;i<100;i++)
    {
        burst_remaining[i]=0;
        is_completed[i]=0;
    }
    struct Process p[10];
    for(int i=0;i<n;i++)
    {
        printf("enter the at and bt of process %d",i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].pid=i+1;
        burst_remaining[i]=p[i].bt;
    }

    int completed=0, prev=0, current_time=0;
    while (n!=completed)
    {
        int min=10000;
        int index=-1;
        //finding minimum burst time
        for(int i=0;i<n;i++)
        {
            if(p[i].at <= current_time && is_completed[i]==0)
            {
                if(burst_remaining[i]<min)
                {
                    min=burst_remaining[i];
                    index=i;
                }
                if(burst_remaining[i]==min)
                {
                    if(p[i].at<p[index].at)
                    index= i;
                }
            }
            
        }

      if(index!= -1)
      {
        if(burst_remaining[index]==p[index].bt)
        {
            p[index].st=current_time;
            totalIdle+= p[index].st- prev;
        }
        burst_remaining[index]-=1;
        current_time++;
        prev=current_time;

        if(burst_remaining[index]==0)
        {
            p[index].ct= current_time;
            p[index].tat= p[index].ct- p[index].at;
            p[index].wt= p[index].tat - p[index].bt;

            totalTAT+=p[index].tat;
            totalWT+= p[index].wt;

            is_completed[index]=1;
            completed++;
        }

      }  
      else
      current_time++;
    }
    

}
