#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Process
{
    int pid;
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int completion;
};
void sort_by_arrival(struct Process *arr, int n)
{
    struct Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].arrival > arr[j + 1].arrival)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int findShortestBurst(struct Process *queue, int n, int ct)
{
    int minBurst = 1000;
    int minProcess = 0;
    for (int i = 0; i < n; i++)
    {
        if (minBurst > queue[i].burst)
        {
            minBurst = queue[i].burst;
            minProcess = queue[i].pid;
        }
    }
    queue[minProcess - 1].burst -=1;
    printf("%d\n",queue[minProcess-1].burst);
    for (int i = 0; i < n; i++)
    {
        if (queue[i].burst == 0)
        {
            queue[i].completion = ct;
            queue[i].burst = 1000;
        }
    }
}
bool checkBurst(struct Process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (p[i].burst != 1000)
            return false;
    }
    return true;
}

int main()
{
    int n;
    int total = 0, idle = 0;
    float avg_waiting = 0, avg_turnaround = 0;
    printf("enter the no. of processes: ");
    scanf("%d", &n);
    struct Process *p = (struct Process *)malloc(sizeof(struct Process) * n);

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    sort_by_arrival(p, n);
    struct Process *queue = (struct Process *)malloc(sizeof(struct Process) * n);

    int i = 0, currentTime = 0;
    while (currentTime++)
    {
        if (currentTime == p[i].arrival)
        {
            queue[i] = p[i];
            i++;
        }
        findShortestBurst(queue, n, currentTime);
        if (checkBurst(p, n))
            break;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",p[i].completion);
    }
}