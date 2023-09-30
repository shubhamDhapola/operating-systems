#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
    int ct; // Completion Time
    int wt; // Waiting Time
    int tat; // Turnaround Time
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n) {
    int rt[n];
    for (int i = 0; i < n; i++) {
        rt[i] = proc[i].bt;
        proc[i].ct = -1; // Initialize completion time to -1 (not completed)
        proc[i].wt = 0;
    }

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int total_idle_time = 0; // Track idle time
    int total_cpu_time = 0;  // Track CPU time

    // Process until all processes are completed
    while (complete != n) {
        minm = INT_MAX;
        shortest = -1;

        for (int j = 0; j < n; j++) {
            if (proc[j].art <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
            }
        }

        if (shortest == -1) {
            t++;
            total_idle_time++; // Increment idle time
            continue;
        }

        rt[shortest]--;
        t++;
        total_cpu_time++; // Increment CPU time
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t;
            proc[shortest].ct = finish_time;
            proc[shortest].tat = proc[shortest].ct - proc[shortest].art;
            proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
        }
    }

    // Calculate CPU utilization (corrected)
    float total_time = (float)t; // Total time elapsed
    float cpu_time = (float)total_cpu_time; // Effective CPU time
    float cpu_utilization = (cpu_time / total_time) * 100;
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);

    // Calculate and display throughput
    float throughput = (float)n / total_time;
    printf("Throughput: %.2f processes per time unit\n", throughput);

    // Display total idle time
    printf("Total Idle Time: %d time units\n", total_idle_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process data from the user
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].art);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        proc[i].pid = i + 1;
    }

    // Find waiting time for all processes
    findWaitingTime(proc, n);

    // Calculate total turnaround time and total waiting time
    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += proc[i].tat;
        total_wt += proc[i].wt;
    }

    // Calculate and display average turnaround time and average waiting time
    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    // Display completion times
    printf("Completion Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: %d\n", proc[i].pid, proc[i].ct);
    }

    return 0;
}
