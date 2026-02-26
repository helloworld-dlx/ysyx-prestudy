#include <stdio.h>

int arr[10] = {5, 2, 9, 1, 5, 6, 7, 3, 4, 8};
int n = 10;

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        for (int k = 0; k < n; k++)
        {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

int main(void)
{
    insertion_sort(arr, n);
    return 0;
}