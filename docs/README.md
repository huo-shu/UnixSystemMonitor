# 简易系统监视器程序详解

## 1. 程序概述

本程序是一个基于 Linux `/proc` 文件系统的简易系统监视器，模拟了类似 `top` 命令的功能。它通过读取 `/proc` 伪文件系统中的各种文件来获取系统信息，并在终端中以格式化的方式展示。

快速开始：请查阅第10节[编译和运行](#10-编译和运行)。

## 2. 头文件包含

```c
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // 目录操作库
#include <unistd.h> // 操作系统 API
#include <termios.h> // 终端 I/O 库
```

## 3. 清屏函数

采用ANSI 转义序列。
- `\033[2J`:清屏
- `\033[H`: 光标移动
- `fflush(stdout)`: 刷新输出缓冲区


## 4. 键盘输入函数

- `struct termios`: 保存终端属性
- `tcgetattr(STDIN_FILENO, &oldt)`: 获取终端属性
- `tcsetattr(STDIN_FILENO, TCSANOW, &newt)`: 应用新的终端属性
- `tcsetattr(STDIN_FILENO, TCSANOW, &oldt)`: 恢复原始终端属性
- `newt.c_lflag &= ~(ICANON | ECHO)`: 关闭规范模式（ICANON）和回显（ECHO）

## 5. CPU使用率读取函数

### 实现逻辑
- 读取 `/proc/stat` 文件
- 获取CPU时间统计
- 计算使用率百分比

计算公式：$CPU使用率 = (当前时间 - 上次时间) / 总时间差值 × 100%$

### 关键变量
- `user, system, nice, idle, ioWait, highIrq, softIrq, steal`: 当前CPU时间统计
- `prev*`: 上次统计值，用于计算差值
- `firstRun`: 标记是否为首次运行

## 6. 内存信息读取函数

### 实现逻辑
- 读取 `/proc/meminfo` 文件获取内存详细信息
- 计算物理内存和交换空间使用情况

计算公式：
$$
buff/cache = Buffers + Cached + SReclaimable
used = MemTotal - MemFree - buff/cache
SwapUsed = SwapTotal - SwapFree
$$

### 关键变量
- `MemTotal, MemFree, Buffers, Cached, SReclaimable, MemAvailable`: 物理内存
- `SwapTotal, SwapFree`: 交换空间

## 7. 系统负载读取函数

### 功能说明
- 读取 `/proc/loadavg` 文件
- 显示1分钟、5分钟、15分钟的平均负载

## 8. 进程列表函数

### 实现逻辑
- 使用 `opendir()` 和 `readdir()` 遍历 `/proc` 目录
- 枚举所有进程，通过 `atoi()` 判断目录名是否为有效PID
- 读取 `/proc/[PID]/comm` 文件，获取每个进程的PID和程序名，按表格形式输出进程信息

## 9. 主函数

### 功能流程
1. 清屏并显示程序标题
2. 按顺序调用各监控函数
3. 显示操作提示
4. 等待用户输入
5. 根据输入决定退出或刷新

### 用户交互
- 按 `q` 或 `Q` 退出程序
- 按 `r` 或 `R` 立即刷新
- 其他键等待1秒后自动刷新

## 10. 编译和运行

请下载程序源代码`/src`。

### 编译命令
```bash
gcc -o monitor main.c
```

### 运行要求
- Linux系统
- `/proc` 文件系统读取权限

### 运行效果
程序启动后会显示类似 `top` 命令的实时系统监控界面，包含CPU使用率、内存使用情况、系统负载和进程列表。示例如下。

```bash
Simple System Monitor
====================
%Cpu(s): 5.2 us, 2.1 sy, 0.0 ni, 92.3 id, 0.1 wa, 0.0 hi, 0.3 si, 0.0 st
MiB Mem : 7982.3 total, 1234.5 free, 2345.6 used, 4402.2 buff/cache
MiB Swap: 2048.0 total, 1987.6 free, 60.4 used
Avail Mem: 5432.1 MiB
Load Average: 0.15 (1min), 0.23 (5min), 0.31 (15min)

Processes:
PID        comm
----------------------------------------
1          systemd
224        kthreadd
1234       bash
5678       monitor

Press 'q' to quit, 'r' to refresh
```
