### 选题2：简易系统监视器（The "Top" Clone）

**核心逻辑**：Linux 的哲学是“一切皆文件”。不需要写内核驱动，只需要读取 `/proc` 文件系统就能知道系统的所有秘密。

- **题目描述**：“编写一个 RISC-V 版的简易 htop”
- **具体要求**：
  1.  **数据采集**：编写一个 C 程序，定时（如每 1 秒）读取 `/proc/stat`（计算 CPU 使用率）、`/proc/meminfo`（内存使用）和 `/proc/loadavg`（负载）。
  2.  **进程遍历**：遍历 `/proc/[PID]/` 目录，获取当前运行的所有进程名字和 PID。
  3.  **界面展示**：不要求图形界面，使用 ANSI Escape Code（控制台转义序列）在终端里清屏并打印格式化的表格。
  4.  **交互**：支持按 `q` 退出，按 `r` 刷新。

- **考察点**：
  - **文件 I/O 与字符串解析**：从复杂的文本中提取数字。
  - **Linux `/proc` 伪文件系统**：理解内核如何通过文件向用户态暴露信息。
  - **C 语言基本功**：结构体、循环、定时器。
- **难度系数**：⭐⭐（逻辑清晰，容易上手，成就感强）

---
## 分析top指令显示内容

官方ManPage:[text](unixManPage_TOP.1)
格式化文档：[text](ubuntuFormatDoc_TOP.md)
![text](bashTop-1.png)
参考官方说明文档，可以理解其显示内容、结构、意义。

> top - 18:07:58 up 1:05, 1 user, load average: 0.48, 0.17, 0.06

时间、运行时间、用户数、负载（1min、5min、15min）

> Tasks: 344 total, 1 running, 343 sleeping, 0 stopped, 0 zombie

总进程、运行、睡眠、停止、僵尸

> %Cpu(s): 8.3 us, 8.3 sy, 0.0 ni, 83.3 id, 0.0 wa, 0.0 hi, 0.0 si, 0.0 st

CPU使用率 
- us(user)：用户程序
- sy(system)：系统内核
- ni(nice)：低优先级的程序
- id(idle)：空闲 CPU
- wa(IO wait)：硬待磁盘和网络IO的时间百分比
- hi(hard IRQ)：处理硬件中断的占用比
- si(soft IRQ)：软件中断...
- st：被虚拟机、云服务器偷走的时间(宿主机临时借用、分给其他虚拟机的时间百分比)

该部分内容涉及Linux中的CPU机制，参考官方文档可以理解:[text](cpuDisplayExplain.md)

> MiB Mem : 7893.9 total, 3999.9 free, 1562.0 used, 2640.5 buff/cache
> MiB Swap: 3730.0 total, 3730.0 free, 0.0 used. 6331.9 avail Mem

内存部分
物理：总内存,完全空闲..,实际占用..,缓冲（写入buffer）/缓存(读取cache)..
交换分区/虚拟内存：分区总大小,空闲,实际占用,实际总可用内存

该部分涉及Linux中的内存机制，参考官方文档可以理解:[text](linuxMemoryEx.md)

> 进程号 USER      PR  NI    VIRT    RES    SHR    %CPU  %MEM     TIME+ COMMAND                                                                                                          
>     1 root      20   0   23228  14660   9888 S   0.0   0.2   0:06.19 systemd                                                                                                          
>     2 root      20   0       0      0      0 S   0.0   0.0   0:00.12 kthreadd 

进程号 processID
USER：实际运行用户
PR：进程优先级(priority)
NI：调整优先级值(nice)
状态:Sleep/Running/Zombie
[text](cpuDisplayExplain.md)

VIRT：占用虚拟内存大小/申请内存(virtual)
RES：实际占用../物理..(resident)
SHR：和其他程序共享..(shared)
[text](linuxMemoryEx.md)

%CPU：CPU占用
%MEM：内存占用(memory)
TIME+：运行时间
COMMAND：进程名

所有字段详细解释:[text](processDisplayExplain.md) 由于全文复杂深入而晦涩，参考豆包、[黑马程序员](https://www.bilibili.com/video/BV1n84y1i7td)S4EP11、本地Ubuntu界面选择了解。

### 按键操作：
- 按 CPU 排序：P
- 内存：M
- 进程名：N
- PID ：N+N
- 退出：Q / Ctrl+C
- 刷新：Enter / Space（每隔一段时间自动刷新）

参考：
>    3b. MANAGING Fields
>    ......

## 分析top指令实现原理

### 采集

- CPU 信息 ：读取 /proc/stat 文件 --> CPU 时间分配
- 内存信息 ：/proc/meminfo -->内存使用
- 进程信息 ：/proc/[PID] 目录 --> 进程详细信息
- 系统负载 ：/proc/loadavg 文件 --> 系统负载情况（1、5、15min）

为了理解top指令读取的内容，首先需要了解/proc文件系统。
官方文档：[text](procLinuxManualPage.md)
由于链接文档过多，暂时放弃更深入理解，用到哪些再详细查阅。
> Pages that refer to this page: ......
还需要理解Linux内核proc相关内容。官方文档有极为详细、复杂、晦涩的解释。[text](https://www.kernel.org/doc/html/latest/filesystems/proc.html) 毫无疑问无法直接通读理解，我选择先理解文件目录结构，然后在linux本地查看文件内容，最后寻找编写本程序所需内容。

![text](procContent-1.png)

```bash
test@test-VMware-Virtual-Platform:/$ cd /proc && ls
1     105   1135  13    1661  198  217   2242  23    236   244   251   258   2617  267   28    29    3036  3189  3390  3504  44   52   63  734  80   89   96          cmdline        fs           kpageflags     pagetypeinfo   sysvipc
10    106   116   131   1663  199  218   225   230   237   2444  252   2587  262   268   2804  2905  3052  32    34    3508  441  54   64  738  81   9    968         consoles       interrupts   latency_stats  partitions     thread-self
100   107   117   132   1667  2    219   2252  2307  238   245   253   2588  2620  2688  2816  2910  3053  3235  3406  36    45   55   65  739  82   90   97          cpuinfo        iomem        loadavg        pressure       timer_list
1001  108   118   135   1668  20   2191  2255  231   239   2452  2534  259   2621  269   282   2919  306   3242  347   37    455  56   66  74   83   91   98          crypto         ioports      locks          schedstat      tty
1004  1086  119   14    17    200  22    226   2311  24    246   254   2592  2625  27    2826  292   3065  3250  348   38    456  57   67  747  84   92   984         devices        irq          mdstat         scsi           uptime
1005  109   12    143   170   203  220   2262  2318  240   247   2547  2593  2626  270   2837  293   311   3251  3485  397   46   578  68  75   85   927  99          diskstats      kallsyms     meminfo        self           version
101   1093  120   15    1711  206  221   2265  232   241   2479  255   2595  263   272   2864  2950  3117  3270  3499  4     47   579  69  757  855  93   acpi        dma            kcore        misc           slabinfo       version_signature
102   1097  1219  16    18    21   2214  2267  233   2419  248   256   260   2632  273   2871  2979  3137  3296  35    42    48   58   7   76   856  932  asound      driver         keys         modules        softirqs       vmallocinfo
1027  110   122   1630  1825  213  222   227   234   242   2481  2561  2608  264   2739  2874  2980  3151  33    3500  420   49   59   70  77   857  94   bootconfig  dynamic_debug  key-users    mounts         stat           vmstat
103   1105  123   1633  1894  214  223   2273  2340  2420  249   257   261   265   2763  2885  3     3162  3314  3501  43    5    6    71  78   86   940  buddyinfo   execdomains    kmsg         mpt            swaps          zoneinfo
1035  111   125   1647  19    215  2237  228   2346  243   2493  2573  2612  266   2773  2891  30    3166  3338  3502  437   50   60   72  79   87   95   bus         fb             kpagecgroup  mtrr           sys
104   112   128   166   196   216  224   229   235   2438  250   2575  2615  2662  2798  2895  3015  3180  3349  3503  438   516  62   73  8    88   959  cgroups     filesystems    kpagecount   net            sysrq-trigger
```

#### CPU

```bash
test@test-VMware-Virtual-Platform:~$ cat /proc/stat | tr '\000' '\n'
cpu  1229 71 3171 47066 297 0 37 0 0 0
cpu0 319 5 854 11708 72 0 5 0 0 0
cpu1 286 1 928 11520 127 0 18 0 0 0
cpu2 302 63 672 11920 61 0 7 0 0 0
cpu3 320 1 716 11917 36 0 6 0 0 0
intr 178796 35 252 0 0 0 0 2 0 1 0 0 0 2655 0 0 0 1391 12768 41 258 0 ...
ctxt 263819
btime 1773059564
processes 3591
procs_running 1
procs_blocked 0
softirq 103296 15 11220 7 509 18796 0 307 15427 0 57015
```

参考内核文档、命令行输出，可得知/proc/stat文件结构。[proc_stat 官方文档](procStatLMP.md)
注意需要严格按照顺序录入：
- **user**：用户态时间
- **nice**：低优先级用户态时间
- **system**：内核态时间
- **idle**：空闲时间
- **iowait**：等待 I/O 时间
- **irq**：硬中断时间
- **softirq**：软中断时间
- **steal**：虚拟化被窃取的时间
- **guest**：虚拟机运行时间
- **guest_nice**：低优先级虚拟机运行时间

#### 内存

/proc/meminfo文件内容：
```bash
test@test-VMware-Virtual-Platform:~$ cat /proc/meminfo
MemTotal:        8083272 kB
MemFree:         4514944 kB
MemAvailable:    6539972 kB
Buffers:           49836 kB
Cached:          2221744 kB
SwapCached:            0 kB
Active:          2514020 kB
Inactive:         381488 kB
Active(anon):     681824 kB
Inactive(anon):        0 kB
Active(file):    1832196 kB
Inactive(file):   381488 kB
Unevictable:          16 kB
Mlocked:              16 kB
SwapTotal:       3819516 kB
SwapFree:        3819516 kB
Zswap:                 0 kB
Zswapped:              0 kB
Dirty:              8360 kB
Writeback:             0 kB
AnonPages:        624028 kB
Mapped:           385252 kB
Shmem:             57896 kB
KReclaimable:      64396 kB
Slab:             245976 kB
SReclaimable:      64396 kB
SUnreclaim:       181580 kB
KernelStack:       14624 kB
PageTables:        20120 kB
SecPageTables:         0 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     7861152 kB
Committed_AS:    4801104 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       35036 kB
VmallocChunk:          0 kB
Percpu:            95232 kB
HardwareCorrupted:     0 kB
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB
FileHugePages:      2048 kB
FilePmdMapped:         0 kB
CmaTotal:              0 kB
CmaFree:               0 kB
Unaccepted:            0 kB
Balloon:               0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:               0 kB
DirectMap4k:      145216 kB
DirectMap2M:     5097472 kB
DirectMap1G:     5242880 kB
```

各字段含义依旧参考官方文档理解：[text](procMeminfoLMP.md)
此外，在baeldung上我找到一篇理解起来容易一些的文章:[text](https://www.baeldung.com/linux/proc-meminfo) AI翻译文本已贴在文档中：[text](procMeminfoFileInLinux_BaeldungOnLinux.md)

依旧在top中寻找有用信息：
MemTotal       系统总内存
MemFree        完全空闲内存
Buffers        buffer缓存
Cached         page cache
SReclaimable   可回收slab缓存
MemAvailable   可立即使用内存

#### 负载

```bash
test@test-VMware-Virtual-Platform:~$ cat /proc/loadavg
0.38 0.12 0.04 2/786 3503
```
参考博客园文章理解该文件内容。[text](linuxLoadavgTopCpuLoad.md)
> Loadavg浅述
> cat /proc/loadavg可以看到当前系统的load 
> $ cat /proc/loadavg 
> 0.01 0.02 0.05 2/317 26207 
> 前面三个值分别对应系统当前1分钟、5分钟、15分钟内的平均load。load用于反映当前系统的负载情况，对于16核的系统，如果每个核上cpu利用率为30%，则在不存在uninterruptible进程的情况下，系统load应该维持在4.8左右。对16核系统，如果load维持在16左右，在不存在uninterrptible进程的情况下，意味着系统CPU几乎不存在空闲状态，利用率接近于100%。结合iowait、vmstat和loadavg可以分析出系统当前的整体负载，各部分负载分布情况。

### 计算

- CPU 使用率：根据 /proc/stat 中不同状态的时间差，计算用户 系统 空闲态占比

Linux 内核在 /proc/stat 第一行提供 CPU 时间累计值:`cpu  user nice system idle iowait irq softirq steal`。
每个值表示 CPU 在该状态下累计消耗的时间,从系统启动开始累计，单位为jiffies。
官方解释：
类比top指令，需要保存上一次数值；读取本次的数值；计算差值；计算百分比。


- 内存：

借助AI工具，查阅官方文档，得知计算公式：
buff/cache = Buffers + Cached + *SReclaimable*
used = MemTotal - MemFree - buff/cache

单位：/proc/meminfo 使用 KB，输出转换为 MiB (KB / 1024)

- 计算进程占用资源：/proc/[PID]/stat : 占用的 CPU 时间、内存大小


### 展示

- 顶部系统信息
- 底部进程列表

更新机制：ANSI 转义序列
参考:[text](https://zhuanlan.zhihu.com/p/570148970)

## Unix库

键盘输入需要修改终端属性，因此需要学习termios库。
termios库文档：

基本操作示例
```c
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
int main() {
   struct termios oldt, newt;
   // 获取当前终端属性
   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;
   // 设置非规范模式，关闭回显
   newt.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   printf("请输入一个字符：");
   char ch = getchar();
   printf("\n你输入的字符是：%c\n", ch);
   // 恢复原始终端属性
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
   return 0;
}
```

高级功能与应用
- 非规范模式：允许逐字符读取输入，而无需等待换行符。适用于实时交互场景，如游戏或命令行工具。
- 信号处理：通过捕获信号（如 SIGINT）实现自定义行为，例如忽略中断信号或执行特定任务。
- 嵌入式系统优化：在资源受限的环境中，termios 可通过配置缓冲区大小、波特率等参数，优化输入输出性能。

sleep需要用到unistd库，库文档：

系统调用函数：
```c
// 文件操作
ssize_t read(int fd, void *buf, size_t count); // 从文件描述符读取数据
ssize_t write(int fd, const void *buf, size_t count); // 向文件描述符写入数据
int close(int fd); // 关闭文件描述符
// 进程管理
pid_t getpid(void); // 获取当前进程ID
pid_t fork(void); // 创建子进程
void _exit(int status); // 退出当前进程
// 文件权限与路径
int access(const char *pathname, int mode); // 检查文件权限
int chdir(const char *path); // 改变当前工作目录
char *getcwd(char *buf, size_t size); // 获取当前工作目录
// 休眠与定时
unsigned sleep(unsigned seconds); // 进程休眠（秒）
int usleep(useconds_t usec); // 进程休眠（微秒）
unsigned alarm(unsigned seconds); // 设置定时器
```

操作目录流需要用到dirent库，文档：

```c
#include <stdio.h>
#include <dirent.h>
int main() {
   DIR *dir;
   struct dirent *entry;
   // 打开当前目录
   dir = opendir(".");
   if (dir == NULL) {
       perror("opendir");
       return 1;
   }
   // 遍历目录内容
   while ((entry = readdir(dir)) != NULL) {
       printf("%s\n", entry->d_name); // 打印目录项名称
   }
   // 关闭目录流
   closedir(dir);
   return 0;
}
```