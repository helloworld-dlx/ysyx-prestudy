#include <stdio.h>

#define LEN 8
int a[LEN] = {5, 2, 4, 7, 1, 3, 2, 6};

// merge two sorted subarrays a[start..mid] and a[mid+1..end]
void merge(int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int left[n1], right[n2];
    for (int i = 0; i < n1; i++)
        left[i] = a[start + i];
    for (int i = 0; i < n2; i++) // 修复 #1: 使用 n2 作为循环条件
        right[i] = a[mid + 1 + i];
    int i = 0, j = 0;
    int k = start;
    while (i < n1 && j < n2)
    {
        if (left[i] < right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++]; // 修复 #2: 当 right[j] 更小时，使用 j++
    }

    // copy remaining elements of left[] if any
    while (i < n1)
        a[k++] = left[i++];
    // copy remaining elements of right[] if any
    while (j < n2)
        a[k++] = right[j++];
}

// merge sort
void sort(int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        sort(start, mid);
        sort(mid + 1, end);
        merge(start, mid, end);
    }
}

int main(void)
{
    sort(0, LEN - 1);
    for (int i = 0; i < LEN; i++)
        printf("%d ", a[i]);
    return 0;
}