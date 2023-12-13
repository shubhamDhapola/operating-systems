#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, seektime = 0, head;
    printf("Enter the number of sequence : ");
    scanf("%d", &n);
    int seq[n];
    printf("Enter the Sequence : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
    }
    printf("Enter the position of head: ");
    scanf("%d", &head);
    printf("The FCFS Sequence is :  ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", seq[i]);
        seektime = seektime + abs(head - seq[i]);
        head = seq[i];
    }
    printf("\nTotal Seek Time is : %d\n", seektime);
    return 0;}
