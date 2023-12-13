#include <stdio.h>
#include <stdlib.h>
#define LOW 0
#define HIGH 199

int main()
{
int n, seektime = 0, head, dloc, temp, max;
printf("Enter the number of sequence : ");
scanf("%d", &n);
int seq[n + 1];
printf("Enter the Sequence : ");
for (int i = 0; i < n; i++)
{scanf("%d", &seq[i]);
}
printf("Enter the position of head: ");
scanf("%d", &head);
seq[n] = head; // add RW head into queue
n++;
for (int i = 0; i < n; i++)
{
for (int j = i; j < n; j++)
{
if (seq[i] > seq[j])
{
    temp = seq[i];
    seq[i] = seq[j];
     seq[j] = temp;
}}}
max = seq[n - 1];
// locate head in the queue
for (int i = 0; i < n; i++)
{
     if (head == seq[i])
{
      dloc = i;
       break;}}
printf("The SCAN Sequence is : ");
if (abs(head - LOW) <= abs(head - HIGH))
{
     for (int j = dloc; j >= 0; j--)
{
    printf("%d ", seq[j]);
}
  for (int j = dloc + 1; j < n; j++)
{
     printf("%d ", seq[j]);
}}
else
{
   for (int j = dloc + 1; j < n; j++)
{
    printf("%d ", seq[j]);}
for (int j = dloc; j >= 0; j--){
     printf("%d ", seq[j]);}}
   seektime = head + max;
printf("\nTotal Seek Time is : %d\n", seektime);
return 0;}

