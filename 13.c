#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    int n, seektime = 0, completed = 0, diff = 0, head, pos = 0;

    printf("Enter the number of sequence : ");
    scanf("%d", &n);

    int seq[n], ans[n], visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        ans[i] = 0;
    }

    printf("Enter the Sequence : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
    }

    printf("Enter the position of head: ");
    scanf("%d", &head);

    while (completed != n)
    {
        int min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] != 1)
            {
                diff = abs(seq[i] - head);
                if (diff < min)
                {
                    min = diff;
                    pos = i;
                }
            }
        }
        seektime = seektime + min;
        ans[completed++] = seq[pos];
        visited[pos] = 1;
        head = seq[pos];
    }

    printf("The SSTF Sequence is : ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
    }

    printf("\nTotal Seek Time is : %d\n", seektime);

    return 0;
}
