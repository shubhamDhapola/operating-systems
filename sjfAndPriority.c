#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival;
    int priority;  // Priority for Priority Scheduling
    int burst;
    int waiting;
    int turnaround;
    int completion;
};

void sort_by_priority(struct Process *arr, int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].priority > arr[j + 1].priority) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_by_burst_time(struct Process *arr, int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].burst > arr[j + 1].burst) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    int choice;
   int total=0, idle=0;
    float avg_waiting = 0, avg_turnaround = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(sizeof(struct Process) * n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
    }

    printf("Select Scheduling Algorithm:\n");
    printf("1. Priority Scheduling\n");
    printf("2. Shortest Job First (SJF) Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Priority Scheduling
        sort_by_priority(p, n);
    } else if (choice == 2) {
        // SJF Scheduling
        sort_by_burst_time(p, n);
    } else {
        printf("Invalid choice. Exiting...\n");
        free(p);
        return 1;
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

    printf("\nPID\tPriority\tBurst time\tCompletion time\tTurnaround time\tWaiting time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].priority, p[i].burst,
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
