#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int alloc[n][m];
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    int max[n][m];
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    int avail[m];
    printf("Enter the Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
        f[k] = 0;
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
    int flag = 1;
    for (i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            printf("The system is not safe.\n");
            break;
        }
    }
    if (flag == 1)
    {
        printf("Following is the SAFE Sequence:\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d\n", ans[n - 1]);
    }
    return 0;
}

// #include <stdio.h>

// #define MAX_PROCESSES 3
// #define MAX_RESOURCES 3

// int available[MAX_RESOURCES];
// int maximum[MAX_PROCESSES][MAX_RESOURCES];
// int allocation[MAX_PROCESSES][MAX_RESOURCES];
// int need[MAX_PROCESSES][MAX_RESOURCES];

// void initialize() {
//     // Initialize available resources
//     printf("Enter the available resources:\n");
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         scanf("%d", &available[i]);
//     }

//     // Initialize maximum matrix
//     printf("Enter the maximum demand of each process:\n");
//     for (int i = 0; i < MAX_PROCESSES; i++) {
//         for (int j = 0; j < MAX_RESOURCES; j++) {
//             scanf("%d", &maximum[i][j]);
//         }
//     }

//     // Initialize allocation matrix
//     printf("Enter the resources currently allocated to each process:\n");
//     for (int i = 0; i < MAX_PROCESSES; i++) {
//         for (int j = 0; j < MAX_RESOURCES; j++) {
//             scanf("%d", &allocation[i][j]);
//             // Calculate need matrix
//             need[i][j] = maximum[i][j] - allocation[i][j];
//         }
//     }
// }

// int isSafe(int process, int request[]) {
//     // Check if request is within the available resources
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         if (request[i] > available[i]) {
//             return 0;  // Unsafe
//         }
//     }

//     // Simulate resource allocation
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         available[i] -= request[i];
//         allocation[process][i] += request[i];
//         need[process][i] -= request[i];
//     }

//     // Check if the system is still in a safe state
//     int work[MAX_RESOURCES];
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         work[i] = available[i];
//     }

//     int finish[MAX_PROCESSES] = {0};
//     int count = 0;
//     while (count < MAX_PROCESSES) {
//         int found = 0;
//         for (int i = 0; i < MAX_PROCESSES; i++) {
//             if (!finish[i]) {
//                 int j;
//                 for (j = 0; j < MAX_RESOURCES; j++) {
//                     if (need[i][j] > work[j]) {
//                         break;
//                     }
//                 }
//                 if (j == MAX_RESOURCES) {
//                     // Process can finish
//                     for (int k = 0; k < MAX_RESOURCES; k++) {
//                         work[k] += allocation[i][k];
//                     }
//                     finish[i] = 1;
//                     found = 1;
//                     count++;
//                 }
//             }
//         }
//         if (!found) {
//             // No process can finish, unsafe state
//             return 0;
//         }
//     }

//     // Restore the state to check other requests
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         available[i] += request[i];
//         allocation[process][i] -= request[i];
//         need[process][i] += request[i];
//     }

//     // The system is in a safe state
//     return 1;
// }

// int main() {
//     initialize();

//     int process;
//     printf("Enter the process number making the request (0 to %d): ", MAX_PROCESSES - 1);
//     scanf("%d", &process);

//     int request[MAX_RESOURCES];
//     printf("Enter the resource request for process %d:\n", process);
//     for (int i = 0; i < MAX_RESOURCES; i++) {
//         scanf("%d", &request[i]);
//     }

//     if (isSafe(process, request)) {
//         printf("Request granted. System is still in a safe state.\n");
//     } else {
//         printf("Request denied. Granting the request would lead to an unsafe state.\n");
//     }

//     return 0;
// }
