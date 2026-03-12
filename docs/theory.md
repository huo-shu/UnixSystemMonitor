# 简易系统监视器程序详解

## 1. 程序概述

本程序是一个基于 Linux `/proc` 文件系统的简易系统监视器，模拟了类似 `top` 命令的功能。它通过读取 `/proc` 伪文件系统中的各种文件来获取系统信息，并在终端中以格式化的方式展示。

## 2. 头文件包含

```c
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
```

- **stdio.h**: 标准输入输出库，用于文件操作和屏幕输出
- **stdlib.h**: 标准库，提供内存分配、随机数生成等功能
- **string.h**: 字符串处理库，用于字符串操作
- **dirent.h**: 目录操作库，用于遍历 `/proc` 目录
- **unistd.h**: 提供 POSIX 操作系统 API，如 `sleep` 函数
- **termios.h**: 终端 I/O 库，用于实现非阻塞键盘输入

## 3. 清屏函数

```c
// 清屏函数
void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}
```

**详细解释**：
- `\033[2J`: ANSI 转义序列，用于清除整个屏幕
- `\033[H`: ANSI 转义序列，将光标移动到屏幕左上角
- `fflush(stdout)`: 刷新输出缓冲区，确保清屏操作立即执行

**Linux 终端原理**：
ANSI 转义序列是一组特殊的字符序列，以 ESC 字符（ASCII 27）开头，用于控制终端的各种行为，如光标移动、颜色设置、清屏等。这些序列被终端模拟器（如 xterm、gnome-terminal 等）解析并执行相应的操作。

## 4. 非阻塞键盘输入函数

```c
// 非阻塞读取键盘输入
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
```

**详细解释**：
- `struct termios`: 终端属性结构体，用于保存终端的配置信息
- `tcgetattr(STDIN_FILENO, &oldt)`: 获取当前终端的属性，保存到 `oldt` 中
- `newt = oldt`: 复制当前属性到 `newt`
- `newt.c_lflag &= ~(ICANON | ECHO)`: 关闭规范模式（ICANON）和回显（ECHO）
- `tcsetattr(STDIN_FILENO, TCSANOW, &newt)`: 立即应用新的终端属性
- `ch = getchar()`: 读取一个字符
- `tcsetattr(STDIN_FILENO, TCSANOW, &oldt)`: 恢复原始终端属性
- `return ch`: 返回读取的字符

**Linux 终端原理**：
- **规范模式（Canonical Mode）**：终端以行为单位进行输入处理，用户输入的字符会被缓冲，直到按下回车键才会被发送到程序。
- **非规范模式（Non-Canonical Mode）**：输入字符立即被发送到程序，不需要等待回车键。
- **回显（Echo）**：输入的字符会在终端上显示出来。

通过关闭规范模式和回显，程序可以实现非阻塞的键盘输入，用户按下按键后立即响应，而不需要按回车键。

## 5. CPU 使用率读取函数

```c
// 读取CPU使用率
void read_cpu_usage() {
    FILE *fp;
    char buffer[256];
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    static unsigned long prev_user, prev_nice, prev_system, prev_idle, prev_iowait, prev_irq, prev_softirq, prev_steal, prev_guest, prev_guest_nice;
    static int first_run = 1;
    
    fp = fopen("/proc/stat", "r");
    if (fp) {
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", 
               &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
        fclose(fp);
        
        if (!first_run) {
            unsigned long total = (user + nice + system + idle + iowait + irq + softirq + steal) - 
                                (prev_user + prev_nice + prev_system + prev_idle + prev_iowait + prev_irq + prev_softirq + prev_steal);
            unsigned long idle_diff = idle - prev_idle;
            float usage = 100.0 * (total - idle_diff) / total;
            printf("CPU Usage: %.2f%%\n", usage);
        }
        
        prev_user = user;
        prev_nice = nice;
        prev_system = system;
        prev_idle = idle;
        prev_iowait = iowait;
        prev_irq = irq;
        prev_softirq = softirq;
        prev_steal = steal;
        first_run = 0;
    } else {
        printf("CPU Usage: N/A\n");
    }
}
```

**详细解释**：
- **变量定义**：
  - `user`: 用户态CPU时间
  - `nice`: 低优先级用户态CPU时间
  - `system`: 系统态CPU时间
  - `idle`: 空闲CPU时间
  - `iowait`: I/O等待时间
  - `irq`: 硬中断处理时间
  - `softirq`: 软中断处理时间
  - `steal`: 虚拟机被其他虚拟机抢占的时间
  - `guest`: 运行虚拟机的时间
  - `guest_nice`: 运行低优先级虚拟机的时间
  - 静态变量用于存储上一次的CPU时间值，以便计算差值

- **文件操作**：
  - `fopen("/proc/stat", "r")`: 打开 `/proc/stat` 文件
  - `fgets(buffer, sizeof(buffer), fp)`: 读取第一行（总CPU信息）
  - `sscanf`: 解析读取到的字符串，提取各个CPU时间值
  - `fclose(fp)`: 关闭文件

- **计算CPU使用率**：
  - 第一次运行时，只存储当前值，不计算使用率
  - 后续运行时，计算总CPU时间差和空闲时间差
  - CPU使用率 = (总时间差 - 空闲时间差) / 总时间差 * 100%

**Linux 内核原理 - `/proc/stat` 文件**：
- `/proc/stat` 文件包含了系统CPU使用情况的统计信息
- 第一行 `cpu` 表示所有CPU的总体情况
- 后续行 `cpu0`, `cpu1` 等表示各个CPU核心的情况
- 这些值是从系统启动开始累计的时间（以jiffies为单位，通常为1/100秒）
- 通过计算两次读取之间的差值，可以得到这段时间内的CPU使用率

## 6. 内存使用情况读取函数

```c
// 读取内存使用情况
void read_mem_info() {
    FILE *fp;
    char buffer[256];
    unsigned long total, free, available;
    
    fp = fopen("/proc/meminfo", "r");
    if (fp) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (sscanf(buffer, "MemTotal: %lu", &total) == 1) {
                // 继续读取
            } else if (sscanf(buffer, "MemFree: %lu", &free) == 1) {
                // 继续读取
            } else if (sscanf(buffer, "MemAvailable: %lu", &available) == 1) {
                break;
            }
        }
        fclose(fp);
        
        float used = (float)(total - available);
        float usage = 100.0 * used / total;
        printf("Memory Usage: %.2f%% (%.2f MB / %.2f MB)\n", usage, used/1024, (float)total/1024);
    } else {
        printf("Memory Usage: N/A\n");
    }
}
```

**详细解释**：
- **变量定义**：
  - `total`: 总内存大小（以KB为单位）
  - `free`: 空闲内存大小（以KB为单位）
  - `available`: 可用内存大小（以KB为单位）

- **文件操作**：
  - `fopen("/proc/meminfo", "r")`: 打开 `/proc/meminfo` 文件
  - `while (fgets(buffer, sizeof(buffer), fp))`: 逐行读取文件
  - `sscanf`: 解析每一行，提取所需的内存信息
  - 当找到 `MemAvailable` 后，停止读取
  - `fclose(fp)`: 关闭文件

- **计算内存使用率**：
  - 已使用内存 = 总内存 - 可用内存
  - 内存使用率 = 已使用内存 / 总内存 * 100%
  - 将KB转换为MB（除以1024）进行显示

**Linux 内核原理 - `/proc/meminfo` 文件**：
- `/proc/meminfo` 文件包含了系统内存使用情况的详细信息
- `MemTotal`: 系统总物理内存
- `MemFree`: 完全空闲的内存
- `MemAvailable`: 可用于分配的内存（包括可回收的缓存）
- 内核通过这个文件向用户空间暴露内存管理的信息
- 这些值以KB为单位，表示当前的内存状态

## 7. 系统负载读取函数

```c
// 读取系统负载
void read_load_avg() {
    FILE *fp;
    char buffer[256];
    float load1, load5, load15;
    
    fp = fopen("/proc/loadavg", "r");
    if (fp) {
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer, "%f %f %f", &load1, &load5, &load15);
        fclose(fp);
        printf("Load Average: %.2f (1min), %.2f (5min), %.2f (15min)\n", load1, load5, load15);
    } else {
        printf("Load Average: N/A\n");
    }
}
```

**详细解释**：
- **变量定义**：
  - `load1`: 1分钟平均负载
  - `load5`: 5分钟平均负载
  - `load15`: 15分钟平均负载

- **文件操作**：
  - `fopen("/proc/loadavg", "r")`: 打开 `/proc/loadavg` 文件
  - `fgets(buffer, sizeof(buffer), fp)`: 读取第一行
  - `sscanf`: 解析读取到的字符串，提取三个负载值
  - `fclose(fp)`: 关闭文件

**Linux 内核原理 - `/proc/loadavg` 文件**：
- `/proc/loadavg` 文件包含了系统的平均负载信息
- 前三个值分别表示1分钟、5分钟和15分钟的平均负载
- 平均负载是指系统中处于可运行状态和不可中断状态的进程数的平均值
- 可运行状态：正在使用CPU或等待CPU的进程
- 不可中断状态：正在等待I/O操作完成的进程
- 负载值除以CPU核心数，可以得到每个核心的平均负载

## 8. 进程遍历函数

```c
// 遍历进程
void list_processes() {
    DIR *dir;
    struct dirent *entry;
    char path[512];
    FILE *fp;
    char comm[256];
    
    printf("\nProcesses:\n");
    printf("%-10s %-40s\n", "PID", "Command");
    printf("----------------------------------------\n");
    
    dir = opendir("/proc");
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            // 检查是否为数字目录（PID）
            if (entry->d_type == DT_DIR) {
                int pid = atoi(entry->d_name);
                if (pid > 0) {
                    snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
                    fp = fopen(path, "r");
                    if (fp) {
                        if (fgets(comm, sizeof(comm), fp)) {
                            // 移除换行符
                            comm[strcspn(comm, "\n")] = 0;
                            printf("%-10d %-40s\n", pid, comm);
                        }
                        fclose(fp);
                    }
                }
            }
        }
        closedir(dir);
    } else {
        printf("Failed to open /proc directory\n");
    }
}
```

**详细解释**：
- **变量定义**：
  - `dir`: 目录指针，用于遍历 `/proc` 目录
  - `entry`: 目录项结构体，存储当前遍历到的目录项信息
  - `path`: 存储进程命令文件的路径
  - `comm`: 存储进程命令名称

- **目录操作**：
  - `opendir("/proc")`: 打开 `/proc` 目录
  - `while ((entry = readdir(dir)) != NULL)`: 遍历目录中的所有项
  - `entry->d_type == DT_DIR`: 检查是否为目录
  - `atoi(entry->d_name)`: 将目录名转换为整数，判断是否为进程PID
  - `snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name)`: 构建进程命令文件的路径
  - `fopen(path, "r")`: 打开进程命令文件
  - `fgets(comm, sizeof(comm), fp)`: 读取进程命令名称
  - `comm[strcspn(comm, "\n")] = 0`: 移除字符串末尾的换行符
  - `printf`: 格式化输出PID和命令名称
  - `closedir(dir)`: 关闭目录

**Linux 内核原理 - `/proc` 目录**：
- `/proc` 是一个伪文件系统，由内核动态生成
- 每个运行中的进程在 `/proc` 目录下都有一个以其PID命名的子目录
- `/proc/[PID]/comm` 文件包含了进程的命令名称
- 内核通过这种方式向用户空间暴露进程信息
- 遍历 `/proc` 目录中的数字目录，可以获取当前系统中所有运行的进程

## 9. 主函数

```c
int main() {
    char key;
    
    while (1) {
        clear_screen();
        
        // 打印系统信息
        printf("Simple System Monitor\n");
        printf("====================\n");
        
        read_cpu_usage();
        read_mem_info();
        read_load_avg();
        list_processes();
        
        printf("\nPress 'q' to quit, 'r' to refresh\n");
        
        // 等待用户输入
        key = getch();
        if (key == 'q' || key == 'Q') {
            break;
        } else if (key != 'r' && key != 'R') {
            // 非刷新键，等待1秒
            sleep(1);
        }
    }
    
    return 0;
}
```

**详细解释**：
- **主循环**：
  - `while (1)`: 无限循环，直到用户按 'q' 退出
  - `clear_screen()`: 清屏
  - 打印标题
  - 调用各个信息读取函数
  - 打印操作提示
  - `key = getch()`: 读取用户输入
  - `if (key == 'q' || key == 'Q')`: 按 'q' 退出
  - `else if (key != 'r' && key != 'R')`: 非 'r' 键，等待1秒后自动刷新
  - `sleep(1)`: 暂停1秒

**程序流程**：
1. 清屏
2. 读取并显示CPU使用率
3. 读取并显示内存使用情况
4. 读取并显示系统负载
5. 遍历并显示进程列表
6. 等待用户输入
7. 根据用户输入执行相应操作（退出或刷新）
8. 重复上述步骤

## 10. 重点部分详细解释

### 10.1 `/proc` 文件系统

**原理**：
- `/proc` 是一个特殊的伪文件系统，它不占用实际的磁盘空间，而是由内核在内存中动态生成
- 它提供了一种机制，允许用户空间程序访问内核内部数据结构和系统信息
- 每个文件和目录都对应着内核中的一个数据结构或功能

**重要文件**：
- `/proc/stat`: 包含CPU使用统计信息
- `/proc/meminfo`: 包含内存使用信息
- `/proc/loadavg`: 包含系统负载信息
- `/proc/[PID]/`: 每个进程的信息目录
- `/proc/[PID]/comm`: 进程的命令名称

**访问方式**：
- 可以像普通文件一样使用标准文件I/O函数（如 `fopen`, `fread`, `fclose`）来访问这些文件
- 读取这些文件会触发内核执行相应的函数来生成内容
- 写入某些文件可以向内核发送命令或修改内核参数

### 10.2 CPU使用率计算

**原理**：
- CPU使用率是指CPU在一段时间内的繁忙程度
- `/proc/stat` 中的值是从系统启动开始累计的时间
- 通过计算两次读取之间的时间差，可以得到这段时间内的CPU使用情况

**计算方法**：
1. 第一次读取 `/proc/stat`，保存各个CPU时间值
2. 第二次读取 `/proc/stat`，再次保存各个CPU时间值
3. 计算总CPU时间差：总时间差 = 当前总时间 - 上次总时间
4. 计算空闲时间差：空闲时间差 = 当前空闲时间 - 上次空闲时间
5. CPU使用率 = (总时间差 - 空闲时间差) / 总时间差 * 100%

**为什么这样计算**：
- 总时间差代表这段时间内CPU的总运行时间
- 空闲时间差代表这段时间内CPU的空闲时间
- 总时间差减去空闲时间差就是CPU的繁忙时间
- 繁忙时间除以总时间就是CPU的使用率

### 10.3 内存使用率计算

**原理**：
- 内存使用率是指已使用内存占总内存的比例
- `/proc/meminfo` 中的 `MemTotal` 表示总内存大小
- `MemAvailable` 表示可用内存大小（包括可回收的缓存）

**计算方法**：
1. 读取 `/proc/meminfo` 文件，获取 `MemTotal` 和 `MemAvailable` 值
2. 计算已使用内存：已使用内存 = 总内存 - 可用内存
3. 计算内存使用率：内存使用率 = 已使用内存 / 总内存 * 100%

**为什么使用 MemAvailable 而不是 MemFree**：
- `MemFree` 是完全空闲的内存，不包括可回收的缓存
- `MemAvailable` 是真正可用于分配的内存，包括可回收的缓存
- 使用 `MemAvailable` 可以更准确地反映系统的内存使用状况

### 10.4 终端控制

**原理**：
- 终端设备有多种工作模式，如规范模式和非规范模式
- 规范模式下，终端以行为单位处理输入，需要按下回车键才会将输入发送给程序
- 非规范模式下，输入字符立即被发送给程序，不需要等待回车键

**实现方法**：
1. 使用 `tcgetattr` 获取当前终端属性
2. 修改属性，关闭规范模式和回显
3. 使用 `tcsetattr` 应用新的属性
4. 读取用户输入
5. 恢复原始终端属性

**为什么需要这样做**：
- 为了实现实时的键盘响应，不需要用户按回车键
- 为了避免用户输入的字符在屏幕上显示，保持界面整洁

## 11. 程序运行流程

1. **初始化**：程序启动，进入主循环
2. **清屏**：使用 ANSI 转义序列清除屏幕
3. **读取系统信息**：
   - 读取并计算CPU使用率
   - 读取并计算内存使用情况
   - 读取系统负载
   - 遍历并显示进程列表
4. **等待用户输入**：
   - 按 'q' 或 'Q'：退出程序
   - 按 'r' 或 'R'：立即刷新
   - 其他键：等待1秒后自动刷新
5. **重复执行**：回到步骤2，继续循环

## 12. 总结

本程序通过读取 Linux `/proc` 文件系统，实现了一个简易的系统监视器，具有以下功能：

- 实时显示CPU使用率
- 显示内存使用情况
- 显示系统负载
- 列出当前运行的进程
- 支持按 'q' 退出，按 'r' 刷新

程序利用了 Linux 内核通过 `/proc` 文件系统向用户空间暴露信息的机制，展示了如何通过文件I/O操作获取系统信息，以及如何使用终端控制实现交互功能。

通过这个程序，我们可以了解到：
- Linux `/proc` 伪文件系统的工作原理
- CPU使用率和内存使用率的计算方法
- 系统负载的含义和获取方法
- 进程信息的获取方法
- 终端控制的基本原理和实现方法

这是一个很好的学习 Linux 系统编程和内核原理的示例程序。