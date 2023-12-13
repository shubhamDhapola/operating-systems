#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define low 0
#define high 199
int main()
{
    int n;
    printf("enter the no. of values ");
scanf("%d",&n);
int arr[n];
printf("enter the values \n");
for(int i=0;i<n;i++)
{
    scanf("%d",&arr[i]);
}
    int head;
printf("enter the values of head ");
scanf("%d",&head);
int headCopy=head;
    int new[n+2];
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    int k = 0;
    int flag = 0, seektime = 0;
    int i = 0, j = 0;
    for (i = 0; i < n; i++)
    {
        if (arr[i] >= head)
        {
            if (flag == 0)
                j = i - 1;

            flag = 1;
            new[k++] = arr[i];
             seektime+= abs(head- arr[i] );
             head=arr[i];
        }
    }
   
    new[k++] = high;
    new[k++] = low;
    seektime+= abs(head-high);
    seektime+= abs(high-low);

    head=low;
    for (int i = 0; i < j+1 ; i++)
    {
        new[k++] = arr[i];
         seektime+=abs(head-arr[i]);
         head=arr[i];
    }

     int ans= high-headCopy + high-low+ arr[j]-low;
    printf("ans is %d\n ",ans);
    
     printf("seek time is %d \n", seektime);
    printf("seq is ");
   
   
    for (int i = 0; i < n+2; i++)
    {
        printf("%d ", new[i]);
    }
    return 0;
}