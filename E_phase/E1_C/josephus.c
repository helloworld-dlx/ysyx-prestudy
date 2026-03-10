#include <stdio.h>
#include <stdlib.h>

// 1. 定义专属车厢：约瑟夫节点
typedef struct node
{
    int id;            // 乘客编号 (1 到 n)
    struct node *next; // 尾部挂钩
} Node;

// 2. 核心函数原型设计

// 功能：造出一个有 n 个人的圆环，并返回这个圆环的"随便一个入口"（通常是第一个人）
Node *create_circle(int n)
{
    if (n <= 0)
        return NULL;
    Node *head = malloc(sizeof(Node));
    head->id = 1;
    head->next = NULL;

    Node *tail = head;
    for (int i = 2; i <= n; i++)
    {
        Node *new_node = malloc(sizeof(Node));
        new_node->id = i;
        tail->next = new_node;
        tail = new_node;
    }
    tail->next = head;
    return head;
}

// 功能：开始丢手绢游戏！从 head 开始，数到 m 就杀掉，直到只剩最后一个人
void play_josephus(Node *head, int m)
{
    if (head == NULL || m <= 0)
        return;
    Node *curr = head;
    Node *prev = head;
    while (prev->next != head)
    {
        prev = prev->next;
    }
    while (curr->next != curr)
    {
        for (int i = 1; i < m; i++)
        {
            curr = curr->next;
            prev = prev->next;
        }
        printf("%d\n", curr->id);
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
    }
    printf("winner: %d", curr->id);
    free(curr);
}

int main()
{
    int n = 7;
    int m = 3;

    Node *ring = create_circle(n);
    play_josephus(ring, m);

    return 0;
}