#include <stdio.h>

void fifo(int string[20], int n, int size)
{
    int frames[n];
    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
    }
    int index = -1, page_miss = 0, page_hits = 0;
    for (int i = 0; i < size; i++)
    {
        int symbol = string[i];
        int flag = 0;
        for (int j = 0; j < n; j++)
        {
            if (symbol == frames[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            printf("\nSymbol : %d  in Frame : ", symbol);
            for (int j = 0; j < n; j++)
            {
                printf("%d ", frames[j]);
            }
            page_hits += 1;
        }
        else
        {
            index = (index + 1) % n;
            frames[index] = symbol;
            page_miss += 1;
            printf("\nSymbol : %d  in Frame : ", symbol);
            for (int j = 0; j < n; j++)
            {
                printf("%d ", frames[j]);
            }
        }
    }
    printf("\nPage hits: %d", page_hits);
    printf("\nPage misses: %d\n", page_miss);
}

int main()
{
    int n, no_frames;

    printf("Enter the number of symbols you want to enter : ");
    scanf("%d", &n);

    int page[n];
    printf("Enter %d Symbols : ", n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &page[i]);
    printf("Enter the number of frames : ");
    scanf("%d", &no_frames);
    fifo(page, no_frames, n);
    return 0;}
