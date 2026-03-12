#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h> // 目录流操作
#include <unistd.h> // sleep函数
#include <termios.h> // getch函数，vsc无法使用该库。

/* 清屏函数
v1 由于作业要求采用ANSI 转义序列控制终端行为，放弃使用system clear。
查表得知ASCII27 \033 为esc，[2J：清除整个屏幕，［H：Cursor Position，将光标移动到屏幕左上角。
v2 根据AI建议，增加fflush，强制将 printf 输出在缓冲区里等待的内容立即发送到终端。
*/
void clearScreen() {
    printf("\033[2J\033[H");
    fflush(stdout); // 刷新行缓冲
}

/* 键盘输入:Q退出，R刷新
返回值：用户输入的字符
*/
int getch() {
    struct termios oldt, newt;
    int ch;

    // 保存终端设置
    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt;

    // 设置新的终端模式：关规范和回显
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    
    ch = getchar();

    // 恢复终端设置
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* 读取CPU使用率
v1 封装CPU函数，完成采样、计算、输出。
v2 不仅输出usage，且对各字段单独计算。查询发现实际单位为 jiffies，修复单位错误。
v3 去掉 guest，多 CPU统计，输出模块放进main函数。按照AI建议，增加判断无法打开文件的情况。
v4 第一次运行时没有历史数据，应该只记录数据，不计算。
v5 按照 top 顺序重写，全英文输出。输出重新合并最后一步计算，放弃struct、多CPU统计、在main输出。
v6 保留一位小数。根据官方文档，将变量全部定义为unsigned long类型。原代码过于混乱，过完年忘了，借用AI工具梳理。
*/

void readCpuUsage() {

    FILE *fp;
    char buffer[256];

    // 本次CPU累计时间
    unsigned long user, system, nice, idle;
    unsigned long ioWait, highIrq, softIrq, steal;

    // 上次CPU累计时间 prev:previous
    static unsigned long prevUser, prevNice, prevSystem, prevIdle;
    static unsigned long prevIoWait, prevHighIrq, prevSoftIrq, prevSteal;

    static int firstRun = 1; //若为第一次运行，则没有历史数据

    // 读取/proc/stat
    fp = fopen("/proc/stat", "r");
    if (!fp) { // 若无法打开文件
        printf("CPU Usage: N/A\n");
        return;
    }
    fgets(buffer, sizeof(buffer), fp);
    // 输入顺序: user nice system idle ioWait highIrq softIrq steal *guest* *guestNice*
    sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
        &user, &nice, &system, &idle,&ioWait, &highIrq, &softIrq, &steal);
    fclose(fp);

    if (!firstRun) { // 第一次读取只记录数据,跳过计算和输出

        // 使用率计算公式：*4*(使用率usage)% = *1*（字段差值） / *2*(差值和total) * *3*（100）

        // 各字段时间差值 *1*
        unsigned long userDiff    = user - prevUser;
        unsigned long niceDiff    = nice - prevNice;
        unsigned long systemDiff  = system - prevSystem;
        unsigned long idleDiff    = idle - prevIdle;
        unsigned long ioWaitDiff  = ioWait - prevIoWait;
        unsigned long highIrqDiff = highIrq - prevHighIrq;
        unsigned long softIrqDiff = softIrq - prevSoftIrq;
        unsigned long stealDiff   = steal - prevSteal;

        // CPU总时间差值 *2*
        unsigned long total = userDiff + niceDiff + systemDiff + idleDiff + ioWaitDiff + highIrqDiff + softIrqDiff + stealDiff;

        /*  计算CPU使用率（单位转换为百分比）并输出  *4*
            AI建议增加除数判断，但经过检验，除数永不为0 */
        printf("%%Cpu(s): %.1f us, %.1f sy, %.1f ni, %.1f id, "
            "%.1f wa, %.1f hi, %.1f si, %.1f st\n",
            100.0 * userDiff    / total,
            100.0 * systemDiff  / total,
            100.0 * niceDiff    / total,
            100.0 * idleDiff    / total,
            100.0 * ioWaitDiff  / total,
            100.0 * highIrqDiff / total,
            100.0 * softIrqDiff / total,
            100.0 * stealDiff   / total);
    // 输出格式：%Cpu(s): us sy ni id wa hi si st
    }

    // 保存当前数据
    prevUser = user;
    prevNice = nice;
    prevSystem = system;
    prevIdle = idle;
    prevIoWait = ioWait;
    prevHighIrq = highIrq;
    prevSoftIrq = softIrq;
    prevSteal = steal;

    firstRun = 0; //更新首次运行标记
}

/* 读取内存使用率
变量不使用小驼峰命名，与meminfo文件一致。
/proc/meminfo文件中内存大小单位：KB，输出时转换为MiB。
v1 与CPU函数思路同。注意内存单位为KB，输出时转换为MB，并保留两位小数。
v2 变量定义为lu。
v3 发现重大问题，top所显示的内容不只Memory Usage,且计算公式Used = MemTotal - MemAvailable存在严重偏差。
v4 关闭指针位置错误，后续迭代无法继续读取文件内容。只有匹配成功时才使用 sscanf() 解析数字。
v5 根据b站视频，改用Unix最常用的strncmp安全比较字符串。
v6 增加swap相关字段。未避免提前退出，移除break。
*/

void readMemoryInfo()
{
    FILE *fp;
    char buffer[256];

    unsigned long MemTotal = 0;
    unsigned long MemFree = 0;
    unsigned long Buffers = 0;
    unsigned long Cached = 0;
    unsigned long SReclaimable = 0;
    unsigned long MemAvailable = 0;
    unsigned long Used;
    unsigned long BuffCache;

    unsigned long SwapTotal = 0;
    unsigned long SwapFree = 0;
    unsigned long SwapUsed;

    fp = fopen("/proc/meminfo", "r");
    if (!fp) { //无法打开
        printf("Memory Usage: N/A\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) { // 根据官方文档，所需字段不一定连续，且一行一个，需要逐行搜索。
        if (strncmp(buffer, "MemTotal:", 9) == 0) {
            sscanf(buffer + 9, "%lu", &MemTotal);
        }
        else if (strncmp(buffer, "MemFree:", 8) == 0) {
            sscanf(buffer + 8, "%lu", &MemFree);
        }
        else if (strncmp(buffer, "Buffers:", 8) == 0) {
            sscanf(buffer + 8, "%lu", &Buffers);
        }
        else if (strncmp(buffer, "Cached:", 7) == 0) {
            sscanf(buffer + 7, "%lu", &Cached);
        }
        else if (strncmp(buffer, "SReclaimable:", 13) == 0) {
            sscanf(buffer + 13, "%lu", &SReclaimable);
        }
        else if (strncmp(buffer, "MemAvailable:", 13) == 0) {
            sscanf(buffer + 13, "%lu", &MemAvailable);
        }
        else if (strncmp(buffer, "SwapTotal:", 10) == 0) {
            sscanf(buffer + 10, "%lu", &SwapTotal);
        }
        else if (strncmp(buffer, "SwapFree:", 9) == 0) {
            sscanf(buffer + 9, "%lu", &SwapFree);
        }
    }

    fclose(fp);

    /* 计算:
    buff/cache = Buffers + Cached + SReclaimable
    used = MemTotal - MemFree - buff/cache
    SwapUsed = SwapTotal - SwapFree
    */
    BuffCache = Buffers + Cached + SReclaimable;
    Used = MemTotal - MemFree - BuffCache;
    SwapUsed = SwapTotal - SwapFree;

    //输出:
    printf("MiB Mem : %.1f total, %.1f free, %.1f used, %.1f buff/cache\n",MemTotal / 1024.0,MemFree / 1024.0,Used / 1024.0,BuffCache / 1024.0);
    printf("MiB Swap: %.1f total, %.1f free, %.1f used\n",SwapTotal / 1024.0,SwapFree / 1024.0,SwapUsed / 1024.0);
    printf("Avail Mem: %.1f MiB\n",MemAvailable / 1024.0);
}

/* 读取系统负载
v1 与其他函数结构同
v2 增加关闭文件指针
v3 移除多余的关闭指针，loadavg 相当健壮*/
void readLoadAvg() {
    FILE *fp;
    char buffer[256];

    float load1, load5, load15; // 1分钟、5分钟、15分钟的负载平均值
    fp = fopen("/proc/loadavg", "r"); 
    if (!fp) {
        printf("Load Average: N/A\n");
        return;
    }

    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "%f %f %f", &load1, &load5, &load15);
    fclose(fp);

    printf("Load Average: %.2f (1min), %.2f (5min), %.2f (15min)\n", load1, load5, load15);
}

/* 遍历进程目录：枚举活跃进程，读取PID和程序名。
v2 调整结构，不采用其他函数的if判断和报错方式，而是正向判断。
v3 修正目录名称，并非command,而是comm。根据官方文档，command文件包含完整命令行，而comm文件只包含程序名，且不包含参数。
*/
void listProcesses() {
    // 进程目录
    DIR *dir;
    struct dirent *entry; //目录项结构指针
    char path[512]; // 根据博客文档，为文件路径创建充足的缓冲区冗余，避免路径过长。
    FILE *fp;
    char comm[256];
    
    // 输出表头，PID10字符，command40字符宽，与下同。
    printf("\nProcesses:\n");
    printf("%-10s %-40s\n", "PID", "comm");
    printf("----------------------------------------\n");
    
    dir = opendir("/proc"); 
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {    // 逐个读取目录项
            if (entry->d_type == DT_DIR) {    // 检查当前项是否为目录，d_type为DT_DIR（数值4）表示目录。
            
                // 将目录名转换为整数，若大于0，就是有效的PID
                int pid = atoi(entry->d_name); 
                if (pid > 0) {

                    // 构建路径 /proc/[PID]/comm，只读打开，读取程序名
                    snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name); 
                    fp = fopen(path, "r");

                    if (fp) { // 采用正向判断，只有成功打开才继续
                        if (fgets(comm, sizeof(comm), fp)) {

                            comm[strcspn(comm, "\n")] = 0; // 移除串尾换行符
                            printf("%-10d %-40s\n", pid, comm);
                        }
                        fclose(fp); // 关闭文件
                    }
                }
            }
        }
        closedir(dir); // 关闭目录流
    } else {
        printf("Failed to open /proc.\n");
    }
}

int main() {
    char key;
    
    while (1) {
        clearScreen();
        
        // 表头
        printf("Simple System Monitor\n");
        printf("====================\n");
        
        // 按top顺序挨个调用
        readCpuUsage();
        readMemoryInfo();
        readLoadAvg();
        listProcesses();
        
        // 表尾
        printf("\nPress 'q' to quit, 'r' to refresh\n");
        
        // 等待用户输入
        key = getch();
        if (key == 'q' || key == 'Q') {
            break;
        } else if (key != 'r' && key != 'R') {
            sleep(1); // 输入R，跳过sleep。未输入R，自动刷新。
        }
    }
    
    return 0;
}
