#include <stdio.h>

#define LEN 8
int a[LEN] = {5, 2, 4, 7, 1, 3, 2, 6};

// partition the array a[start..end] and return the pivot index
int partition(int start, int end)
{
    int pivot = a[start];
    int left = start;
    int right = end;
    while (left < right)
    {
        while (left < right && a[right] >= pivot)
        {
            right--;
        }
        a[left] = a[right];
        while (left < right && a[left] <= pivot)
        {
            left++;
        }
        a[right] = a[left];
    }
    a[left] = pivot;
    return left;
}

void quicksort(int start, int end)
{
    int mid;
    if (start < end)
    {
        mid = partition(start, end);
        quicksort(start, mid);
        quicksort(mid + 1, end);
    }
}

int main()
{
    quicksort(0, LEN - 1);
    for (int i = 0; i < LEN; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}