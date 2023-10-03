#include <stdio.h>

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

int main()
{
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct process p[n];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_idle_time = 0;
    int total_execution_time = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);

        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);

        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        total_execution_time += p[i].burst_time;
    }

    int time = 0;
    int completed = 0;

    while (completed < n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time)
            {
                flag = 1;
                if (p[i].remaining_time <= time_quantum)
                {
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completion_time = time;
                    completed++;
                }
                else
                {
                    time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                }
            }
        }
        if (flag == 0)
        {
            total_idle_time++;
            time++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;
    float cpu_utilization = ((float)(total_execution_time - total_idle_time) / total_execution_time) * 100;
    float cpu_idle_percentage = ((float)total_idle_time / total_execution_time) * 100;
    float throughput = (float)n / total_execution_time;

    printf("\nPid\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("CPU Utilization = %.2f%%\n", cpu_utilization);
    printf("CPU Idle Percentage = %.2f%%\n", cpu_idle_percentage);
    printf("Throughput = %.2f processes/unit time\n", throughput);

    return 0;
}