

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
int max(int a,int b){
    return (a>b)?a:b;
}
void enqueue(int queue[], int *rear, int item) {
    if (*rear == -1) {
        *rear = 0;
        queue[*rear] = item;
    } else {
        *rear = *rear + 1;
        queue[*rear] = item;
    }
}

int dequeue(int queue[], int *front,int* rear) {
    int item = queue[*front];
    if (*front == *rear) {
        *front = -1;
        *rear = -1;
    } else {
        *front = *front + 1;
    }
    return item;
}

int isEmpty(int front, int rear) {
    return (front == -1 && rear == -1);
}

void bubbleSort(struct process p[], int n, int field) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (field == 0 ? p[j].arrival_time > p[j + 1].arrival_time : p[j].pid > p[j + 1].pid) {
                // Swap p[j] and p[j+1]
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    int tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int idx;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++) {
        printf("Enter at and bt of process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        scanf("%d", &p[i].burst_time);
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        printf("\n");
    }
    bubbleSort(p,n,0);


    int queue[100];
    int front = -1, rear = -1;
    int current_time = 0;
    enqueue(queue, &rear, 0);
    int completed = 0;
    int mark[100];
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;

    while (completed != n) {
        idx = dequeue(queue, &front,&rear);

        if (burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time, p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        if (burst_remaining[idx] - tq > 0) {
            burst_remaining[idx] -= tq;
            current_time += tq;
        } else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
        }

        for (int i = 1; i < n; i++) {
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                enqueue(queue, &rear, i);
                mark[i] = 1;
            }
        }
        if (burst_remaining[idx] > 0) {
            enqueue(queue, &rear, idx);
        }

        if (isEmpty(front, rear)) {
            for (int i = 1; i < n; i++) {
                if (burst_remaining[i] > 0) {
                    enqueue(queue, &rear, i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100;
    throughput = (float)n / (p[n - 1].completion_time - p[0].arrival_time);


bubbleSort(p,n,1);
    printf("\n");
    printf("#P\tAT\tBT\tST\tCT\tTAT\tWT\t\n\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("CPU Utilization = %.2f%%\n", cpu_utilisation);
    printf("Throughput = %.2f process/unit time\n", throughput);

    return 0;
}

