#include<stdio.h>

struct process
{
int pid;
int at;
int bt;
int st;
int ct;
int tat;
int wt;
};

int main()
{
    int n;
    struct process p[100];
    float avg_tat;
    float avg_wt;
    float cpu_utiz;
    int total_tat=0;
    int total_wt=0;
    int total_idle=0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];

    for(int i=0;i<100;i++)
    {
        is_completed[i]=0;
    }
    printf("enter the no. of process :");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("enter bt and at for process %d: ",i+1);
        scanf("%f %f",&p[i].at,&p[i].bt);
        p[i].pid=i+1;
        burst_remaining[i]+=p[i].bt;
    }
    int current_time=0;
    int prev=0;
    int completed=0;
    while(completed!=n){
        int index=-1;
        int mn=1000000;
        //finding min index value
     for(int i=0;i<n;i++)
     {
        if(p[i].at<=current_time && is_completed[i]==0)
        {
            if(p[i].bt<mn)
            {
                mn=p[i].bt;
                index=i;
            }
            if(burst_remaining[i]==mn)
            {
                if(p[i].at < p[index].at)
                mn=p[i].bt;
                index=i;
            }
        }
     }
     if(index!= -1)
     {
        if(burst_remaining[index]==p[index].bt)
        {
          p[index].st=current_time;
          total_idle+= p[index].st-prev;
        }
        burst_remaining[index]-=1;
        current_time++;
        prev=current_time;
        if(burst_remaining[index]==0)
        {
            p[index].ct=current_time;
            p[index].tat=p[index].ct - p[index].at;
            p[index].wt=p[index].tat- p[index].at;
            total_tat+=p[index].tat;
            total_wt+=p[index].wt;
            is_completed[index]=1;
            completed++;
        }

     }
     else
     {
        current_time++;
     }

       
    }
}

