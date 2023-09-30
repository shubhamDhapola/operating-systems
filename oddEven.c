#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n , evenSum = 0, oddSum = 0;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    if (fork())
    {
        // Parent process
        for (int i = 1; i <= n; i += 2)
        {
            oddSum += i;
        }
         wait(NULL); // Wait for the child process to finish        
        printf("Total odd sum: %d\n", oddSum);
    }
    else
    {
        // Child process
        for (int i = 2; i <= n; i += 2)
        {
            evenSum += i;
        }
        printf("Total even sum: %d\n", evenSum);
    }
    return 0;
}
