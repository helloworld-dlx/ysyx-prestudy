# E1 C语言程序设计（五）

## 第25章 C标准库

### 25.1 字符串操作函数

```c
#include <string.h>
```

1. 初始化字符串

   `memset`函数把`s`所指的内存地址开始的`n`个字节都填充为`c`的值。通常`c`的值为0，把一块内存区清零。

   ```c
   void *memset(void *s, int c, size_t n);
   ```

2. 取字符串的长度

   `strlen`函数返回`s`所指的字符串的长度。该函数从`s`所指的第一个字符开始找`'\0'`字符

   ```c
   size_t strlen(const char *s);
   ```

3. 拷贝字符串

   **以`str`开头的函数处理以`'\0'`结尾的字符串，而以`mem`开头的函数则不关心`'\0'`字符**

   `memcpy`函数从`src`所指的内存地址拷贝`n`个字节到`dest`所指的内存地址，不是遇到`'\0'`就结束，而是一定会拷贝完`n`个字节

   **致命弱点：** 它不能处理**源内存和目标内存重叠**的情况

   > **什么是“内存重叠”？**
   >  假设你有一个数组 `[1, 2, 3, 4, 5]`，你想把前 3 个数字整体往后挪一格，变成 `[1, 1, 2, 3, 5]`。
   >  如果用 `memcpy` 从前往后搬：
   >
   > 1. 把 `1` 搬到第二个位置，数组变成 `[1, 1, 3, 4, 5]`。
   > 2. 下一步要搬第二个位置的数（原来是 `2`），但此时它**已经被刚刚搬过来的 `1` 覆盖掉了！**
   >     结果数据全乱套了。

   `memmove`也是从`src`所指的内存地址拷贝`n`个字节到`dest`所指的内存地址

   `memcpy`的两个参数`src`和`dest`所指的内存区间如果重叠则无法保证正确拷贝，而`memmove`却可以正确拷贝

   ```c
   void *memcpy(void *dest, const void *src, size_t n);
   void *memmove(void *dest, const void *src, size_t n);
   ```

   | 函数          | 操作对象 | 遇到 `\0` 会停吗？                 | 需要指定长度 `n` 吗？ | 能处理内存重叠吗？  | 推荐使用场景                                  |
   | ------------- | -------- | ---------------------------------- | --------------------- | ------------------- | --------------------------------------------- |
   | **`strcpy`**  | 字符串   | **会**，且连 `\0` 一起拷           | 否 (极不安全)         | 否                  | 几乎不推荐，太容易溢出                        |
   | **`strncpy`** | 字符串   | **会** (但不够 `n` 时用 `\0` 填充) | 是 (但坑多)           | 否                  | 拷贝短字符串，但**用完务必手动在末尾加 `\0`** |
   | **`memcpy`**  | 任意内存 | **不会**，闭眼拷 `n` 个            | 是                    | **否** (重叠会乱码) | 高效拷贝数组、结构体等独立数据块              |
   | **`memmove`** | 任意内存 | **不会**，闭眼拷 `n` 个            | 是                    | **能** (安全退避)   | 数组元素移位、同一块内存内的数据挪动          |

4. 连接字符串

   `strcat`把`src`所指的字符串连接到`dest`所指的字符串后面

   ```c
   char *strcat(char *dest, const char *src);
   char *strncat(char *dest, const char *src, size_t n);
   ```

5. 比较字符串

   **等于 0**：两者完全一样。

   **大于 0**：第一个不匹配的字节中，左边 > 右边（比较的是 ASCII 码值）。

   **小于 0**：第一个不匹配的字节中，左边 < 右边。

   | 函数          | 操作对象 | 遇到 `\0` 会停吗？     | 需要指定比较长度 `n` 吗？ | 核心应用场景                         |
   | ------------- | -------- | ---------------------- | ------------------------- | ------------------------------------ |
   | **`strcmp`**  | 字符串   | **会**，立刻停止       | 否 (危险，依赖 `\0`)      | 判断两个完整的字符串是否相等         |
   | **`strncmp`** | 字符串   | **会**，立刻停止       | 是 (最多比较 `n` 个)      | 安全比较字符串，或**判断字符串前缀** |
   | **`memcmp`**  | 任意内存 | **绝对不会**，视而不见 | 是 (强制必须提供)         | 比较数组、结构体、二进制文件数据     |

   C 语言的标准它只规定了“返回正数、负数或 0”，没有规定具体是哪个数字

   在绝大多数编译器（比如 GCC）的底层实现里，这个具体的返回值其实就是**第一个不相等字符的 ASCII 码的“数学差值”**

6. 搜索字符串

   `strchr`在字符串`s`中从前到后查找字符`c`，找到字符`c`第一次出现的位置时就返回，返回值指向这个位置，如果找不到字符`c`就返回`NULL`。

   `strrchr`和`strchr`类似，但是从右向左找字符`c`，找到字符`c`第一次出现的位置就返回，函数名中间多了一个字母r可以理解为Right-to-left。

   ```c
   char *strchr(const char *s, int c);
   char *strrchr(const char *s, int c);
   ```

   `strstr`在一个长字符串中从前到后找一个子串（Substring），找到子串第一次出现的位置就返回，返回值指向子串的开头，如果找不到就返回NULL。

   ```c
   char *strstr(const char *haystack, const char *needle);
   ```

7. 分割字符串

   ```c
   char *strtok(char *str, const char *delim);
   ```

   参数`str`是待分割的字符串，`delim`是分隔符，可以指定一个或多个分隔符，`strtok`遇到其中任何一个分隔符就会分割字符串。

### 25.2 标准I/O库函数

#### 25.2.1 文件的基本概念

源文件是文本文件，而目标文件、可执行文件和库文件是二进制文件

#### 25.2.2 fopen/fclose

```c
FILE *fopen(const char *path, const char *mode);
```

`path`可以是相对路径也可以是绝对路径

相对路径是相对于当前工作目录（Current Working Directory）的路径，每个进程都有自己的当前工作目录，Shell进程的当前工作目录可以用`pwd`命令查看

| 模式 (Mode) | 核心动作         | 如果文件**已存在**   | 如果文件**不存在**  | 备注 (文件指针初始位置)                    |
| ----------- | ---------------- | -------------------- | ------------------- | ------------------------------------------ |
| **`"r"`**   | 只读 (Read)      | 正常打开             | **报错返回 `NULL`** | 指向文件**开头**                           |
| **`"w"`**   | 只写 (Write)     | **直接清空原内容！** | 创建新文件          | 指向文件**开头**                           |
| **`"a"`**   | 追加 (Append)    | 正常打开，保护原内容 | 创建新文件          | 指向文件**末尾**                           |
| **`"r+"`**  | 读/写 (Update)   | 正常打开             | **报错返回 `NULL`** | 指向文件**开头**                           |
| **`"w+"`**  | 读/写 (Update)   | **直接清空原内容！** | 创建新文件          | 指向文件**开头**                           |
| **`"a+"`**  | 读/追加 (Update) | 正常打开，保护原内容 | 创建新文件          | 初始指向文件**开头**，但写入必定在**末尾** |

在打开一个文件时如果出错，`fopen`将返回`NULL`并设置`errno`，在程序中应该做出错处理

```c
if ( (fp = fopen("/tmp/file1", "r")) == NULL) {
	printf("error open file /tmp/file1!\n");
	exit(1);
}
```

```c
int fclose(FILE *fp);
```

#### 25.2.3 stdin/stdout/stderr

`stdin`只用于读操作，称为标准输入（Standard Input），`stdout`只用于写操作，称为标准输出（Standard Output），`stderr`也只用于写操作，称为标准错误输出（Standard Error），通常程序的运行结果打印到标准输出，而错误提示（例如`gcc`报的警告和错误）打印到标准错误输出

#### 25.2.4 errno与perror函数

`errno`在头文件`errno.h`中声明，是一个整型变量，在错误返回时将错误原因记录在全局变量`errno`中

```c
void perror(const char *s);
```

`perror`函数将错误信息打印到标准错误输出，首先打印参数`s`所指的字符串，然后打印:号，然后根据当前`errno`的值打印错误原因

```c
char *strerror(int errnum);
```

`errnum` — 错误编号（通常直接传入全局变量 `errno`）

#### 25.2.5 以字节为单位的I/O函数

```c
int fgetc(FILE *stream);
int getchar(void);
```

`fgetc`函数从指定的文件中读一个字节，`getchar`从标准输入读一个字节，调用`getchar()`相当于调用`fgetc(stdin)`

当调用`getchar()`或`fgetc(stdin)`时，如果用户没有输入字符，`getchar`函数就阻塞（指这个函数调用不返回）等待，也就不能执行后面的代码，只有当用户输入回车或者到达文件末尾时`getchar`才返回

从终端设备输入时有两种方法表示文件结束，一种方法是在一行的开头输入Ctrl-D（如果不在一行的开头则需要连续输入两次Ctrl-D），另一种方法是利用Shell的Heredoc语法

```c
int fputc(int c, FILE *stream);
int putchar(int c);
```

`fputc`函数向指定的文件写一个字节，`putchar`向标准输出写一个字节，调用`putchar(c)`相当于调用`fputc(c, stdout)`

#### 25.2.6 操作读写位置的函数

```c
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
```

`rewind`函数把读写位置移到文件开头

`fseek`可以任意移动读写位置，`ftell`可以返回当前的读写位置

`whence`参数的含义如下：

- `SEEK_SET`

  从文件开头移动`offset`个字节

- `SEEK_CUR`

  从当前位置移动`offset`个字节

- `SEEK_END`

  从文件末尾移动`offset`个字节

`offset`可正可负，负值表示向前（向文件开头的方向）移动，正值表示向后（向文件末尾的方向）移动

#### 25.2.7 以字符串为单位的I/O函数

**Never use gets()**

```c
char *fgets(char *s, int size, FILE *stream);
```

`fgets`函数，参数`s`是缓冲区的首地址，`size`是缓冲区的长度，该函数从`stream`所指的文件中读取以`'\n'`结尾的一行（包括`'\n'`在内）存到缓冲区`s`中，并且在该行末尾添加一个`'\0'`组成完整的字符串。

如果文件中的一行太长，`fgets`从文件中读了`size-1`个字符还没有读到`'\n'`，就把已经读到的`size-1`个字符和一个`'\0'`字符存入缓冲区

```c
int fputs(const char *s, FILE *stream);
int puts(const char *s);
```

`fputs`向指定的文件写入一个字符串，`puts`向标准输出写入一个字符串。

#### 25.2.8 以记录为单位的I/O函数

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

记录是指一串固定长度的字节，比如一个`int`、一个结构体或者一个定长数组。参数`size`指出一条记录的长度，而`nmemb`指出要读或写多少条记录，这些记录在`ptr`所指的内存空间中连续存放，共占`size * nmemb`个字节，`fread`从文件`stream`中读出`size * nmemb`个字节保存到`ptr`中，而`fwrite`把`ptr`中的`size * nmemb`个字节写到文件`stream`中。

**“记录”最常见的化身就是一个结构体（`struct`）。**

#### 25.2.9 格式化I/O函数

```c
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
```

`printf`格式化打印到标准输出，而`fprintf`打印到指定的文件`stream`中。`sprintf`打印到用户提供的缓冲区`str`中并在末尾加`'\0'`，由于格式化后的字符串长度很难预计，所以很可能造成缓冲区溢出，用`snprintf`更好一些，参数`size`指定了缓冲区长度，如果格式化后的字符串长度超过缓冲区长度，`snprintf`就把字符串截断到`size-1`字节，再加上一个`'\0'`写入缓冲区

```c
int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);
```

`scanf`从标准输入读字符。`fscanf`从指定的文件`stream`中读字符，而`sscanf`从指定的字符串`str`中读字符。

#### 25.2.10 C标准库的I/O缓冲区

缓冲区（Buffer）就是 C 语言为了**减少和操作系统搭话的次数**而设立的“内存中转站”。全缓冲看“容量”，行缓冲看“回车”，无缓冲“不要命”。

**`fflush(stream)` 的作用：** 强行下达“立刻发车”的死命令！不管仓库满没满，不管有没有换行符，**现在、立刻、马上**把仓库里现有的东西全部运给内核，写进硬盘！

**`fclose` 的附带功能：** 当你调用 `fclose` 关闭文件时，它会自动帮你做一次 Flush 操作，确保所有遗留的货物都安全送到硬盘，然后才把仓库拆除。

### 25.3 数值字符串转换函数

```c
int atoi(const char *nptr);
double atof(const char *nptr);
```

`atoi`把一个字符串开头可以识别成十进制整数的部分转换成`int`型,例如`atoi("123abc")`的返回值是123

`atof`把一个字符串开头可以识别成浮点数的部分转换成`double`型

```c
long int strtol(const char *nptr, char **endptr, int base);
double strtod(const char *nptr, char **endptr);
```

`strtol`是`atoi`的增强版，主要体现在这几方面：

- 不仅可以识别十进制整数，还可以识别其它进制的整数，`strtol("0777~~", NULL, 8)`返回0777的值。
- `endptr`是一个传出参数，函数返回时指向后面未被识别的第一个字符。例如`char *pos; strtol("123abc", &pos, 10);`，`strtol`返回123，`pos`指向字符串中的字母a。如果字符串开头没有可识别的整数，例如`char *pos; strtol("ABCabc", &pos, 10);`，则`strtol`返回0，`pos`指向字符串开头，可以据此判断这种出错的情况，而这是`atoi`处理不了的。
- 如果字符串中的整数值超出`long int`的表示范围（上溢或下溢），则`strtol`返回它所能表示的最大（或最小）整数，并设置`errno`为`ERANGE`

`strtod`是`atof`的增强版，增强的功能和`strtol`类似。

### 25.4 分配内存的函数

```c
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
```

`calloc`分配`nmemb`个元素的内存空间，每个元素占`size`字节，并且`calloc`负责把这块内存空间用字节0填充

#### realloc

##### 场景 A：把仓库“变小”（截断）

- **动作：** 比如原来 100 字节，你现在只要 50 字节。
- **结果：** `realloc` 会保留前 50 个字节的数据原封不动，然后直接把后面的 50 个字节“切掉”回收。

##### 场景 B：把仓库“变大”（扩容 —— 这里有极大的坑！）

比如原来 100 字节，你现在想要 200 字节。这时候搬家公司（系统）会先看一眼周围的地皮：

1. **原地扩建（运气好）：** 如果老仓库后面的内存刚好是空着的，它就直接把后墙打通，给你扩建到 200 字节。**原地址不变，老数据都在，新长出来的 100 字节里面是随机乱码（未初始化）。**
2. **异地搬迁（运气差）：** 如果老仓库后面的内存已经被别人占用了，扩建不了怎么办？`realloc` 会在内存的其他地方找一块完整的 200 字节的新空地。然后，**它会自动把老仓库的 100 字节拷到新地方，并帮你把老仓库 `free` 掉！**

**致命考点：** 因为有可能发生“异地搬迁”，所以 `realloc` 执行完之后，**你的数据可能会换了一个新地址！** 这就是为什么 `realloc` 必须有一个返回值，并且你必须接收这个新地址。

##### 两个特例：把 `realloc` 当别人用

| 你的代码                  | 实际等价于     | 场景含义                                                     |
| ------------------------- | -------------- | ------------------------------------------------------------ |
| **`realloc(NULL, size)`** | `malloc(size)` | 如果你连旧仓库都没有（传了 NULL），那“重新分配”就直接变成了“新分配”。 |
| **`realloc(ptr, 0)`**     | `free(ptr)`    | 如果你要求把旧仓库改成 0 字节，那这就相当于直接退租，释放内存。 |
