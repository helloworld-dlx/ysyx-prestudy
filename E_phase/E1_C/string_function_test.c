#include <stdio.h>
#include <string.h>
int main()
{
    char str1[20] = "Hello";
    char str2[20] = "World";
    int ans;
    ans = memcmp(str1, str2, 5);
    printf("The result of strcmp is: %d\n", ans);
    return 0;
}