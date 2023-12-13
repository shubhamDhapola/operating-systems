#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

struct process
{
    int pid, arrival_time, burst_time, start_time, completion_time, turnaround_time, waiting_time;
};

int queue[MAX_SIZE], front = -1, rear = -1;

void initializeQueue() { front = rear = -1; }
bool isFull() { return rear == MAX_SIZE - 1; }
bool isEmpty() { return front == -1; }
void push(int value)
{
    if (!isFull())
    {
        if (isEmpty())
            front = 0;
        queue[++rear] = value;
    }
}
void pop()
{
    if (!isEmpty())
        front == rear ? initializeQueue() : ++front;
}
int getFront() { return isEmpty() ? -1 : queue[front]; }

void bubbleSort(struct process p[], int n, int field)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ((field == 0 ? p[j].arrival_time > p[j + 1].arrival_time : p[j].pid > p[j + 1].pid))
                p[j] = p[j + 1], p[j + 1] = p[j];
}

int main()
{
    int n, tq, burst_remaining[100], idx, current_time = 0, completed = 0, total_turnaround_time = 0,
                                          total_waiting_time = 0, total_idle_time = 0;
    float avg_turnaround_time, avg_waiting_time, cpu_utilisation, throughput;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("time quantum: ");
    scanf("%d", &tq);

    struct process p[100];
    for (int i = 0; i < n; i++)
    {
        printf("Enter at and bt of process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        printf("\n");
    }
    bubbleSort(p, n, 0);

    initializeQueue();
    push(0);

    int mark[100] = {0};
    mark[0] = 1;

    while (completed != n)
    {
        idx = getFront();
        pop();

        if (burst_remaining[idx] == p[idx].burst_time)
        {
            p[idx].start_time = current_time > p[idx].arrival_time ? current_time : p[idx].arrival_time;
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        current_time += (burst_remaining[idx] -= tq) > 0 ? tq : (completed++, burst_remaining[idx] = 0, p[idx].completion_time = current_time, p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time, p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time, total_turnaround_time += p[idx].turnaround_time, total_waiting_time += p[idx].waiting_time, tq);

        for (int i = 1; i < n; i++)
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && !mark[i])
                push(i), mark[i] = 1;

        if (isEmpty())
            for (int i = 1; i < n; i++)
                if (burst_remaining[i] > 0)
                    push(i), mark[i] = 1;
        break;
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;
    throughput = (float)n / (p[n - 1].completion_time - p[0].arrival_time);

    bubbleSort(p, n, 1);

    printf("\nid\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].start_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

    printf("Avg TAT = %.2f, Avg WT = %.2f, CPU Utilization = %.2f%%, Throughput = %.2f processes/unit time\n",
           avg_turnaround_time, avg_waiting_time, cpu_utilisation, throughput);
}
