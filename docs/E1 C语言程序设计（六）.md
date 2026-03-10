# E1 C语言程序设计（六）

## 第 26 章 链表

### 1.单链表

每个链表有一个头指针，通过头指针可以找到第一个节点，每个节点都可以通过指针域找到它的后继，最后一个节点的指针域为`NULL`，表示没有后继

链表是不支持随机访问的，只能通过前一个元素的指针域得知后一个元素的地址

```c
/* linkedlist.h */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node *link;
struct node {
	unsigned char item;
	link next;
};

link make_node(unsigned char item);
void free_node(link p);
link search(unsigned char key);
void insert(link p);
void delete(link p);
void traverse(void (*visit)(link));
void destroy(void);
void push(link p);
link pop(void);

#endif
```

```c
/* linkedlist.c */
#include <stdlib.h>
#include "linkedlist.h"

static link head = NULL;

link make_node(unsigned char item)
{
	link p = malloc(sizeof *p);
	p->item = item;
	p->next = NULL;
	return p;
}

void free_node(link p)
{
	free(p);
}

link search(unsigned char key)
{
	link p;
	for (p = head; p; p = p->next)
		if (p->item == key)
			return p;
	return NULL;
}

void insert(link p)
{
	p->next = head;
	head = p;
}

void delete(link p)
{
	link pre;
	if (p == head) {
		head = p->next;
		return;
	}
	for (pre = head; pre; pre = pre->next)
		if (pre->next == p) {
			pre->next = p->next;
			return;
		}
}

void traverse(void (*visit)(link))
{
	link p;
	for (p = head; p; p = p->next)
		visit(p);
}

void destroy(void)
{
	link q, p = head;
	head = NULL;
	while (p) {
		q = p;
		p = p->next;
		free_node(q);
	}
}

void push(link p)
{
	insert(p);
}

link pop(void)
{
	if (head == NULL)
		return NULL;
	else {
		link p = head;
		head = head->next;
		return p;
	}
}
```

> 在 C 语言的工程里，把代码分成 `.h`（头文件）和 `.c`（源文件）是祖师爷定下的规矩。你可以用**“餐厅点餐”**的现实场景来完美理解它：
>
> - **`linkedlist.h`（头文件） = 餐厅的菜单。**
>    它向其他程序员（或者你写的 `main.c`）展示：“我这里提供链表服务，你可以用 `make_node` 造节点，用 `insert` 插入节点。” 菜单上**只有菜名（函数声明）和食材长什么样（结构体定义）**，绝对不写菜是怎么做的。
> - **`linkedlist.c`（源文件） = 餐厅的后厨。**
>    这里面包含了真正的底层操作（`malloc`、`for` 循环、指针的指来指去）。后厨对外是封闭的，外部文件不需要、也不应该知道 `insert` 底层到底是怎么把指针连起来的。
>
> **这样做有三大核心好处：**
>
> 1. **信息隐藏（封装）**
> 2. **代码复用**
> 3. **编译加速**

#### 1. 打造新车厢 (`make_node`)

- **动作：** 向系统申请一块铁皮，焊成一节**新车厢**（`malloc`）。
- **装载：** 把你的数据（货物）放进去（`p->item = item`）。
- **挂钩：** 新车厢的**尾部挂钩**暂时什么都没挂，必须明确指着空气（`p->next = NULL`），绝不能瞎指。

#### 2. 车厢进站拼装 (`insert` - 代码里用的是“头插法”)

- **动作：** 每次来了新车厢，都强行把它排在**最前面**当老大。
- **勾住老车队：** 让新车厢的挂钩，直接勾住原本的“第一节车厢”（`p->next = head`）。
- **移交车头牌：** 把代表列车开头的“车头标”，插到这节新车厢上（`head = p`）。

#### 3. 摘除特定车厢 (`delete`)

- **动作：** 列车中间有一节车厢坏了（目标 `p`），需要把它脱离列车。
- **找前车：** 调度员不能直接跑到坏车厢那，必须从头顺藤摸瓜，找到坏车厢的**前一节车厢**（`pre`）。
- **绕过坏车：** 解开前一节车厢的挂钩，直接**越过**坏车厢，勾住坏车厢的**后一节车厢**（`pre->next = p->next`）。坏车厢就被成功孤立了！

#### 4. 列车长巡视 (`traverse`)

- **动作：** 列车长（指针）从挂着“车头标”的第一节车厢上车。
- **逐个检查：** 查完这节车厢的货物，就顺着尾部挂钩走到下一节（`p = p->next`）。一直走到连挂钩都没有了（遇到 `NULL`），宣布巡视结束。

#### 5. 整列火车报废 (`destroy`)

- **动作：** 火车要退役，需要一节一节拆下来送去废品站销毁（`free`）。
- **防失联法则：** 拆解时，必须先**看一眼并记住下一节车厢在哪**，然后再把脚下这节车厢炸毁。如果先炸了脚下的车厢，挂钩就跟着灰飞烟灭了，后面那一长串火车就永远找不到了（这就是可怕的**内存泄漏**）！



### 2. 双向链表

如果每个节点再维护一个指向前趋的指针，删除操作就像插入操作一样容易了

在`linkedlist.h`中修改链表节点的结构体定义：

```c
struct node {
	unsigned char item;
	link prev, next;
};
```

在`linkedlist.c`中修改`insert`和`delete`函数：

```c
void insert(link p)
{
	p->next = head;
	if (head)
		head->prev = p;
	head = p;
	p->prev = NULL;
}

void delete(link p)
{
	if (p->prev)
		p->prev->next = p->next;
	else
		head = p->next;
	if (p->next)
		p->next->prev = p->prev;
}
```

### 3. 静态链表

一开始就直接向系统申请一个**巨大的数组**（比如能装 100 节车厢）。以后所有的操作，都只能在这个数组内部进行，绝不用 `malloc` 和 `free`。

**静态链表的节点：**

```c
struct static_node {
    int data;           // 货物
    int next_cursor;    // 挂钩：记录下一节车厢在数组里的【下标号】（游标）
};

// 一次性造出一个能装100个节点的停车场
struct static_node list[100]; 
```