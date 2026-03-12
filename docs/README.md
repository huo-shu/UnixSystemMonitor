# 简易系统监视器程序详解

## 1. 程序概述

本程序是一个基于 Linux `/proc` 文件系统的简易系统监视器，模拟了类似 `top` 命令的功能。它通过读取 `/proc` 伪文件系统中的各种文件来获取系统信息，并在终端中以格式化的方式展示。

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