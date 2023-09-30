#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, arrival, burst, completion, turnaround, waiting;
};

int main() {
    int n, total = 0, idle = 0;
    float avg_waiting = 0, avg_turnaround = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process *p = malloc(sizeof(struct Process) * n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].completion = (i == 0) ? p[i].arrival + p[i].burst : p[i - 1].completion + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        avg_waiting += p[i].waiting;
        avg_turnaround += p[i].turnaround;
        if (p[i].arrival > p[i - 1].completion)
            idle += p[i].arrival - p[i - 1].completion;
    }

    printf("\nPID\tArrival time \tBurst time\tCompletion time\tTurnaround time\tWaiting time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    avg_waiting /= n;
    avg_turnaround /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
    printf("Throughput: %.2f\n", (float)n / p[n - 1].completion);
    printf("CPU Utilization: %.2f%%\n", (float)(p[n - 1].completion - idle) / p[n - 1].completion * 100);

    free(p);
    return 0;
}
