#include <stdio.h>

#define LEN 8
int a[LEN] = {5, 2, 4, 7, 1, 3, 2, 6};

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

/* 从start到end之间找出第k小的元素 */
int order_statistic(int start, int end, int k)
{
    int i = partition(start, end);
    if (k == i)
        return a[i];
    else if (k > i)
        order_statistic(i + 1, end, k - i);
    else
        order_statistic(start, i, k);
}

int main()
{
    int ans;
    ans = order_statistic(0, LEN - 1, 2);
    printf("%d", ans);
    return 0;
}