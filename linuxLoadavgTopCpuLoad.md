> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.cnblogs.com](https://www.cnblogs.com/qqmomery/p/6267429.html)<table><tbody><tr><td><h2 id="sr-toc-0">目录<button title="显示目录导航" aria-expanded="false"></button></h2>&nbsp;[<a>隐藏</a>]<ul><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Loadavg.E5.88.86.E6.9E.90" rel="noopener nofollow">1&nbsp;Loadavg 分析</a></li><li><ul><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Loadavg.E6.B5.85.E8.BF.B0" rel="noopener nofollow">1.1&nbsp;Loadavg 浅述</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Loadavg.E8.AF.BB.E5.8F.96" rel="noopener nofollow">1.2&nbsp;Loadavg 读取</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Loadavg.E5.92.8C.E8.BF.9B.E7.A8.8B.E4.B9.8B.E9.97.B4.E7.9A.84.E5.85.B3.E7.B3.BB" rel="noopener nofollow">1.3&nbsp;Loadavg 和进程之间的关系</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Loadavg.E9.87.87.E6.A0.B7" rel="noopener nofollow">1.4&nbsp;Loadavg 采样</a></li></ul></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#18.E5.86.85.E6.A0.B8.E8.AE.A1.E7.AE.97loadavg.E5.AD.98.E5.9C.A8.E7.9A.84.E9.97.AE.E9.A2.98" rel="noopener nofollow">2&nbsp;18 内核计算 loadavg 存在的问题</a></li><li><ul><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#xtime_lock.E8.A7.A3.E6.9E.90" rel="noopener nofollow">2.1&nbsp;xtime_lock 解析</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E5.85.A8.E5.B1.80load.E8.AF.BB.E5.86.99.E5.88.86.E7.A6.BB.E8.A7.A3xtime_lock.E9.97.AE.E9.A2.98" rel="noopener nofollow">2.2&nbsp;全局 load 读写分离解 xtime_lock 问题</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E5.87.A0.E4.B8.AA.E5.85.B3.E9.94.AE.E7.82.B9.EF.BC.9A" rel="noopener nofollow">2.3&nbsp;几个关键点：</a></li><li><ul><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E4.B8.8D.E5.8A.A0xtime_lock.E7.9A.84per_cpu_load.E8.AE.A1.E7.AE.97" rel="noopener nofollow">2.3.1&nbsp;不加 xtime_lock 的 per cpu load 计算</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#Thomas.E7.9A.84.E8.A7.A3.E5.86.B3.E6.96.B9.E6.A1.88" rel="noopener nofollow">2.3.2&nbsp;Thomas 的解决方案</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#sched_tick.E7.9A.84.E6.97.B6.E6.9C.BA" rel="noopener nofollow">2.3.3&nbsp;sched_tick 的时机</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E4.BA.A4.E9.94.99.E7.9A.84.E6.97.B6.E9.97.B4.E5.B7.AE" rel="noopener nofollow">2.3.4&nbsp;交错的时间差</a></li></ul></li></ul></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#32.E5.86.85.E6.A0.B8Load.E8.AE.A1.E6.95.B0nohz.E9.97.AE.E9.A2.98" rel="noopener nofollow">3&nbsp;32 内核 Load 计数 nohz 问题</a></li><li><ul><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E8.A7.A3.E5.86.B3.E6.96.B9.E6.A1.88" rel="noopener nofollow">3.1&nbsp;解决方案</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E6.9B.B4.E7.BB.86.E7.B2.92.E5.BA.A6.E7.9A.84.E6.97.B6.E9.97.B4.E9.97.AE.E9.A2.98" rel="noopener nofollow">3.2&nbsp;更细粒度的时间问题</a></li><li><a href="http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&amp;diff=514&amp;oldid=293#.E5.86.8D.E6.AC.A1.E5.9B.9E.E5.BD.92.E5.88.B0.E5.85.AC.E5.B9.B3.E6.80.A7.E9.97.AE.E9.A2.98" rel="noopener nofollow">3.3&nbsp;再次回归到公平性问题</a></li></ul></li></ul></td></tr></tbody></table>

Loadavg 分析
----------

### Loadavg 浅述

cat /proc/loadavg 可以看到当前系统的 load   
$ cat /proc/loadavg   
0.01 0.02 0.05 2/317 26207   
前面三个值分别对应系统当前 1 分钟、5 分钟、15 分钟内的平均 load。load 用于反映当前系统的负载情况，对于 16 核的系统，如果每个核上 cpu 利用率为 30%，则在不存在 uninterruptible 进程的情况下，系统 load 应该维持在 4.8 左右。对 16 核系统，如果 load 维持在 16 左右，在不存在 uninterrptible 进程的情况下，意味着系统 CPU 几乎不存在空闲状态，利用率接近于 100%。结合 iowait、vmstat 和 loadavg 可以分析出系统当前的整体负载，各部分负载分布情况。

### Loadavg 读取

在内核中 / proc/loadavg 是通过 load_read_proc 来读取相应数据，下面首先来看一下 load_read_proc 的实现：

[![][img-0]; "复制代码")

```
fs/proc/proc_misc.c
static int loadavg_read_proc(char *page, char **start, off_t off, 
                                 int count, int *eof, void *data) 
{ 
        int a, b, c; 
        int len; 

        a = avenrun[0] + (FIXED_1/200); 
        b = avenrun[1] + (FIXED_1/200); 
        c = avenrun[2] + (FIXED_1/200); 
        len = sprintf(page,"%d.%02d %d.%02d %d.%02d %ld/%d %d\n", 
                LOAD_INT(a), LOAD_FRAC(a), 
                LOAD_INT(b), LOAD_FRAC(b), 
                LOAD_INT(c), LOAD_FRAC(c), 
                nr_running(), nr_threads, last_pid); 
        return proc_calc_metrics(page, start, off, count, eof, len); 
}

```

[![][img-1]; "复制代码")

几个宏定义如下：

```
#define FSHIFT          11              /* nr of bits of precision */ 
#define FIXED_1         (1<<FSHIFT)     /* 1.0 as fixed-point */ 
#define LOAD_INT(x) ((x) >> FSHIFT) 
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)

```

根据输出格式，LOAD_INT 对应计算的是 load 的整数部分，LOAD_FRAC 计算的是 load 的小数部分。   
将 a=avenrun[0] + (FIXED_1/200）带入整数部分和小数部分计算可得：

```
LOAD_INT(a) = avenrun[0]/(2^11) + 1/200
LOAD_FRAC(a) = ((avenrun[0]%(2^11) + 2^11/200) * 100) / (2^11)
             = (((avenrun[0]%(2^11)) * 100 + 2^10) / (2^11)
             = ((avenrun[0]%(2^11) * 100) / (2^11) + ½

```

由上述计算结果可以看出，FIXED_1/200 在这里是用于小数部分第三位的四舍五入，由于小数部分只取前两位，第三位如果大于 5，则进一位，否则直接舍去。

临时变量 a/b/c 的低 11 位存放的为 load 的小数部分值，第 11 位开始的高位存放的为 load 整数部分。因此可以得到 a=load(1min) * 2^11   
因此有: load(1min) * 2^11 = avenrun[0] + 2^11 / 200   
进而推导出： load(1min)=avenrun[0]/(2^11) + 1/200   
忽略用于小数部分第 3 位四舍五入的 1/200，可以得到 load(1min)=avenrun[0] / 2^11，即：   
avenrun[0] = load(1min) * 2^11

avenrun 是个陌生的量，这个变量是如何计算的，和系统运行进程、cpu 之间的关系如何，在第二阶段进行分析。

### Loadavg 和进程之间的关系

内核将 load 的计算和 load 的查看进行了分离，avenrun 就是用于连接 load 计算和 load 查看的桥梁。   
下面开始分析通过 avenrun 进一步分析系统 load 的计算。   
avenrun 数组是在 calc_load 中进行更新

[![][img-2]; "复制代码")

```
kernel/timer.c
/* 
* calc_load - given tick count, update the avenrun load estimates. 
* This is called while holding a write_lock on xtime_lock. 
*/ 
static inline void calc_load(unsigned long ticks) 
{ 
        unsigned long active_tasks; /* fixed-point */ 
        static int count = LOAD_FREQ;  
        count -= ticks; 
        if (count < 0) { 
                count += LOAD_FREQ; 
                active_tasks = count_active_tasks(); 
                CALC_LOAD(avenrun[0], EXP_1, active_tasks); 
                CALC_LOAD(avenrun[1], EXP_5, active_tasks); 
                CALC_LOAD(avenrun[2], EXP_15, active_tasks); 
        } 
}
static unsigned long count_active_tasks(void) 
{ 
        return nr_active() * FIXED_1; 
}
#define LOAD_FREQ       (5*HZ)          /* 5 sec intervals */ 
#define EXP_1           1884            /* 1/exp(5sec/1min) as fixed-point */ 
#define EXP_5           2014            /* 1/exp(5sec/5min) */ 
#define EXP_15          2037            /* 1/exp(5sec/15min) */

```

[![][img-3]; "复制代码")

calc_load 在每个 tick 都会执行一次，每个 LOAD_FREQ（5s）周期执行一次 avenrun 的更新。   
active_tasks 为系统中当前贡献 load 的 task 数 nr_active 乘于 FIXED_1，用于计算 avenrun。宏 CALC_LOAD 定义如下：

```
#define CALC_LOAD(load,exp,n) \ 
       load *= exp; \ 
       load += n*(FIXED_1-exp); \ 
       load >>= FSHIFT;

```

用 avenrun(t-1) 和 avenrun(t) 分别表示上一次计算的 avenrun 和本次计算的 avenrun，则根据 CALC_LOAD 宏可以得到如下计算：

```
avenrun(t)=(avenrun(t-1) * EXP_N + nr_active * FIXED_1*(FIXED_1 – EXP_N)) / FIXED_1
          = avenrun(t-1) + (nr_active*FIXED_1 – avenrun(t-1)) * (FIXED_1 -EXP_N) / FIXED_1

```

推导出：

```
avenrun(t) – avenrun(t-1) = (nr_active*FIXED_1 – avenrun(t-1)) * (FIXED_1 – EXP_N) / FIXED_1


```

将第一阶段推导的结果代入上式，可得：

```
(load(t) – load(t-1)) * FIXED_1 = (nr_active – load(t-1)) * (FIXED_1 – EXP_N)


```

进一步得到 nr_active 变化和 load 变化之间的关系式：

**load(t) – load(t-1) = (nr_active – load(t-1)) * (FIXED_1 – EXP_N) / FIXED_1**

这个式子可以反映的内容包含如下两点：   
1）当 nr_active 为常数时，load 会不断的趋近于 nr_active，趋近速率由快逐渐变缓   
2）nr_active 的变化反映在 load 的变化上是被降级了的，系统突然间增加 10 个进程，   
1 分钟 load 的变化每次只能够有不到 1 的增加（这个也就是权重的的分配）。

另外也可以通过将式子简化为：

**load(t)= load(t-1) * EXP_N / FIXED_1 + nr_active * (1 - EXP_N/FIXED_1)**

这样可以更加直观的看出 nr_active 和历史 load 在当前 load 中的权重关系 （多谢任震宇大师的指出）

```
#define EXP_1           1884            /* 1/exp(5sec/1min) as fixed-point */ 
#define EXP_5           2014            /* 1/exp(5sec/5min) */ 
#define EXP_15          2037            /* 1/exp(5sec/15min) */

```

1 分钟、5 分钟、15 分钟对应的 EXP_N 值如上，随着 EXP_N 的增大，(FIXED_1 – EXP_N)/FIXED_1 值就越小，   
这样 nr_active 的变化对整体 load 带来的影响就越小。对于一个 nr_active 波动较小的系统，load 会   
不断的趋近于 nr_active，最开始趋近比较快，随着相差值变小，趋近慢慢变缓，越接近时越缓慢，并最   
终达到 nr_active。如下图所示：   
[文件: load 1515.jpg](http://kernel.taobao.org/index.php?title=%E7%89%B9%E6%AE%8A:%E4%B8%8A%E4%BC%A0%E6%96%87%E4%BB%B6&wpDestFile=load_1515.jpg "文件:load 1515.jpg")(无图）

  
也因此得到一个结论，load 直接反应的是系统中的 nr_active。 那么 nr_active 又包含哪些？ 如何去计算   
当前系统中的 nr_active？ 这些就涉及到了 nr_active 的采样。

### Loadavg 采样

nr_active 直接反映的是为系统贡献 load 的进程总数，这个总数在 nr_active 函数中计算：

[![][img-4]; "复制代码")

```
kernel/sched.c
unsigned long nr_active(void) 
{ 
        unsigned long i, running = 0, uninterruptible = 0; 

        for_each_online_cpu(i) { 
                running += cpu_rq(i)->nr_running; 
                uninterruptible += cpu_rq(i)->nr_uninterruptible; 
        } 

        if (unlikely((long)uninterruptible < 0)) 
                uninterruptible = 0; 

        return running + uninterruptible; 
}

#define TASK_RUNNING            0 
#define TASK_INTERRUPTIBLE      1 
#define TASK_UNINTERRUPTIBLE    2 
#define TASK_STOPPED            4 
#define TASK_TRACED             8 
/* in tsk->exit_state */ 
#define EXIT_ZOMBIE             16 
#define EXIT_DEAD               32 
/* in tsk->state again */ 
#define TASK_NONINTERACTIVE     64

```

[![][img-5]; "复制代码")

该函数反映，为系统贡献 load 的进程主要包括两类，一类是 TASK_RUNNING，一类是 TASK_UNINTERRUPTIBLE。  
当 5s 采样周期到达时，对各个 online-cpu 的运行队列进行遍历，取得当前时刻该队列上 running 和 uninterruptible 的  
进程数作为当前 cpu 的 load，各个 cpu load 的和即为本次采样得到的 nr_active。

下面的示例说明了在 2.6.18 内核情况下 loadavg 的计算方法：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>18 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load</td></tr><tr><td>0HZ+10</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>4</td></tr><tr><td>5HZ+1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>5HZ+9</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td></tr><tr><td>5HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></tbody></table>

18 内核计算 loadavg 存在的问题
---------------------

### xtime_lock 解析

内核在 5s 周期执行一次全局 load 的更新，这些都是在 calc_load 函数中执行。追寻 calc_load 的调用：

[![][img-6]; "复制代码")

```
kernel/timer.c
static inline void update_times(void) 
{  
        unsigned long ticks; 

        ticks = jiffies - wall_jiffies; 
        wall_jiffies += ticks; 
        update_wall_time(); 
        calc_load(ticks); 
}

```

[![][img-7]; "复制代码")

update_times 中更新系统 wall time，然后执行全局 load 的更新。

[![][img-8]; "复制代码")

```
kernel/timer.c
void do_timer(struct pt_regs *regs) 
{  
        jiffies_64++; 
        /* prevent loading jiffies before storing new jiffies_64 value. */ 
        barrier(); 
        update_times(); 
}

```

[![][img-9]; "复制代码")

do_timer 中首先执行全局时钟 jiffies 的更新，然后是 update_times。

[![][img-10]; "复制代码")

```
void main_timer_handler(struct pt_regs *regs) 
{ 
...
        write_seqlock(&xtime_lock);
...
        do_timer(regs); 
#ifndef CONFIG_SMP 
        update_process_times(user_mode(regs)); 
#endif 
...
        write_sequnlock(&xtime_lock); 
}

```

[![][img-11]; "复制代码")

对 wall_time 和全局 jiffies 的更新都是在加串行锁（sequence lock）xtime_lock 之后执行的。

[![][img-12]; "复制代码")

```
include/linux/seqlock.h
static inline void write_seqlock(seqlock_t *sl) 
{ 
        spin_lock(&sl->lock);
        ++sl->sequence; 
        smp_wmb(); 
} 

static inline void write_sequnlock(seqlock_t *sl) 
{ 
        smp_wmb(); 
        sl->sequence++; 
        spin_unlock(&sl->lock); 
} 
 
typedef struct { 
        unsigned sequence; 
        spinlock_t lock; 
} seqlock_t;

```

[![][img-13]; "复制代码")

sequence lock 内部保护一个用于计数的 sequence。Sequence lock 的写锁是通过 spin_lock 实现的，   
在 spin_lock 后对 sequence 计数器执行一次自增操作，然后在锁解除之前再次执行 sequence 的自增操作。   
sequence 初始化时为 0。这样，当锁内部的 sequence 为奇数时，说明当前该 sequence lock 的写锁正被拿，   
读和写可能不安全。如果在写的过程中，读是不安全的，那么就需要在读的时候等待写锁完成。对应读锁使用如下：

[![][img-14]; "复制代码")

```
#if (BITS_PER_LONG < 64) 
u64 get_jiffies_64(void) 
{ 
        unsigned long seq; 
        u64 ret;  

        do { 
                seq = read_seqbegin(&xtime_lock); 
                ret = jiffies_64; 
        } while (read_seqretry(&xtime_lock, seq)); 
        return ret; 
} 

EXPORT_SYMBOL(get_jiffies_64); 
#endif 

```

[![][img-15]; "复制代码")

读锁实现如下：

[![][img-16]; "复制代码")

```
static __always_inline unsigned read_seqbegin(const seqlock_t *sl) 
{ 
        unsigned ret = sl->sequence; 
        smp_rmb(); 
        return ret; 
} 

static __always_inline int read_seqretry(const seqlock_t *sl, unsigned iv) 
{ 
        smp_rmb(); 
        /*iv为读之前的锁计数器
        * 当iv为基数时，说明读的过程中写锁被拿，可能读到错误值
        * 当iv为偶数，但是读完之后锁的计数值和读之前不一致，则说明读的过程中写锁被拿，
        * 也可能读到错误值。
        */
        return (iv & 1) | (sl->sequence ^ iv);  
}

```

[![][img-17]; "复制代码")

至此 xtime_lock 的实现解析完毕，由于对应写锁基于 spin_lock 实现，多个程序竞争写锁时等待者会一直循环等待，   
当锁里面处理时间过长，会导致整个系统的延时增长。另外，如果系统存在很多 xtime_lock 的读锁，在某个程   
序获取该写锁后，读锁就会进入类似 spin_lock 的循环查询状态，直到保证可以读取到正确值。因此需要尽可能   
短的减少在 xtime_lock 写锁之间执行的处理流程。

### 全局 load 读写分离解 xtime_lock 问题

在计算全局 load 函数 calc_load 中，每 5s 需要遍历一次所有 cpu 的运行队列，获取对应 cpu 上的 load。1）由于 cpu 个数是不固   
定的，造成 calc_load 的执行时间不固定，在核数特别多的情况下会造成 xtime_lock 获取的时间过长。2）calc_load 是   
每 5s 一次的采样程序，本身并不能够精度特别高，对全局 avenrun 的读和写之间也不需要专门的锁保护，可以将全局 load 的   
更新和读进行分离。   
Dimitri Sivanich 提出在他们的 large SMP 系统上，由于 calc_load 需要遍历所有 online CPU，造成系统延迟较大。   
基于上述原因 Thomas Gleixnert 提交了下述 patch 对该 bug 进行修复：

```
[Patch 1/2] sched, timers: move calc_load() to scheduler
[Patch 2/2] sched, timers: cleanup avenrun users


```

[文件: rw isolate.jpg](http://kernel.taobao.org/index.php?title=%E7%89%B9%E6%AE%8A:%E4%B8%8A%E4%BC%A0%E6%96%87%E4%BB%B6&wpDestFile=rw_isolate.jpg "文件:rw isolate.jpg")

Thomas 的两个 patch，主要思想如上图所示。首先将全局 load 的计算分离到 per-cpu 上，各个 cpu 上计算 load 时不加 xtime_lock   
的锁，计算的 load 更新到全局 calc_load_tasks 中，所有 cpu 上 load 计算完后 calc_load_tasks 即为整体的 load。在 5s 定   
时器到达时执行 calc_global_load，读取全局 cacl_load_tasks，更新 avenrun。由于只是简单的读取 calc_load_tasks，   
执行时间和 cpu 个数没有关系。

### 几个关键点：

#### 不加 xtime_lock 的 per cpu load 计算

在不加 xtime_lock 的情况下，如何保证每次更新 avenrun 时候读取的 calc_load_tasks 为所有 cpu 已经更新之后的 load？

#### Thomas 的解决方案

Thomas 的做法是将定时器放到 sched_tick 中，每个 cpu 都设置一个 LOAD_FREQ 定时器。   
定时周期到达时执行当前处理器上 load 的计算。sched_tick 在每个 tick 到达时执行   
一次，tick 到达是由硬件进行控制的，客观上不受系统运行状况的影响。

#### sched_tick 的时机

将 per-cpu load 的计算放至 sched_tick 中执行，第一反应这不是又回到了时间处理中断之间，是否依旧   
存在 xtime_lock 问题？ 下面对 sched_tick 进行分析（以下分析基于 linux-2.6.32-220.17.1.el5 源码）

[![][img-18]; "复制代码")

```
static void update_cpu_load_active(struct rq *this_rq) 
{ 
        update_cpu_load(this_rq); 

        calc_load_account_active(this_rq); 
}
 
void scheduler_tick(void) 
{ 
        int cpu = smp_processor_id(); 
        struct rq *rq = cpu_rq(cpu); 
...
        spin_lock(&rq->lock); 
...
        update_cpu_load_active(rq); 
...
        spin_unlock(&rq->lock); 

...
} 
 
void update_process_times(int user_tick) 
{ 
...
        scheduler_tick(); 
...
}
 
static void tick_periodic(int cpu) 
{ 
        if (tick_do_timer_cpu == cpu) { 
                write_seqlock(&xtime_lock); 

                /* Keep track of the next tick event */ 
                tick_next_period = ktime_add(tick_next_period, tick_period); 
           
                do_timer(1);  // calc_global_load在do_timer中被调用
                write_sequnlock(&xtime_lock); 
        } 
 
        update_process_times(user_mode(get_irq_regs())); 
...
}
 
void tick_handle_periodic(struct clock_event_device *dev) 
{ 
        int cpu = smp_processor_id(); 
...
        tick_periodic(cpu); 
...
}

```

[![][img-19]; "复制代码")

#### 交错的时间差

将 per-cpu load 的计算放到 sched_tick 中后，还存在一个问题就是何时执行 per-cpu 上的 load 计算，如何保证更新全   
局 avenrun 时读取的全局 load 为所有 cpu 都计算之后的？ 当前的方法是给所有 cpu 设定同样的步进时间 LOAD_FREQ，   
过了这个周期点当有 tick 到达则执行该 cpu 上 load 的计算，更新至全局的 calc_load_tasks。calc_global_load   
的执行点为 LOAD_FREQ+10，即在所有 cpu load 计算执行完 10 ticks 之后，读取全局的 calc_load_tasks 更新 avenrun。

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td></tr><tr><td>0HZ+10</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>5HZ</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>0</td></tr><tr><td>5HZ+1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>+1</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>1+1+1=3</td></tr><tr><td>5HZ+11</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>3</td></tr></tbody></table>

通过将 calc_global_load 和 per-cpu load 计算的时间进行交错，可以避免 calc_global_load 在各个 cpu load 计算之间执行，   
导致 load 采样不准确问题。

32 内核 Load 计数 nohz 问题
---------------------

一个问题的解决，往往伴随着无数其他问题的诞生！Per-cpu load 的计算能够很好的分离全局 load 的更新和读取，避免大型系统中 cpu   
核数过多导致的 xtime_lock 问题。但是也同时带来了很多其他需要解决的问题。这其中最主要的问题就是 nohz 问题。

为避免 cpu 空闲状态时大量无意义的时钟中断，引入了 nohz 技术。在这种技术下，cpu 进入空闲状态之后会关闭该 cpu 对应的时钟中断，等   
到下一个定时器到达，或者该 cpu 需要执行重新调度时再重新开启时钟中断。

cpu 进入 nohz 状态后该 cpu 上的时钟 tick 停止，导致 sched_tick 并非每个 tick 都会执行一次。这使得将 per-cpu 的 load 计算放在   
sched_tick 中并不能保证每个 LOAD_FREQ 都执行一次。如果在执行 per-cpu load 计算时，当前 cpu 处于 nohz 状态，那么当   
前 cpu 上的 sched_tick 就会错过，进而错过这次 load 的更新，最终全局的 load 计算不准确。   
基于 Thomas 第一个 patch 的思想，可以在 cpu 调度 idle 时对 nohz 情况进行处理。采用的方式是在当前 cpu 进入 idle 前进行一次该 cpu   
上 load 的更新，这样即便进入了 nohz 状态，该 cpu 上的 load 也已经更新至最新状态，不会出现不更新的情况。如下图所示：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td></tr><tr><td>0HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td><td>2</td><td>1</td><td>3</td><td>0</td></tr><tr><td>&nbsp;</td><td>-1</td><td>-1</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3-3=0</td></tr><tr><td>5HZ+1</td><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>+1</td><td>+1</td><td>+1</td><td>+1</td><td>+1</td><td>+1</td><td>0+1+...+1=7</td></tr><tr><td>5HZ+11</td><td>0</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>7</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>7</td></tr></tbody></table>

理论上，该方案很好的解决了 nohz 状态导致全局 load 计数可能不准确的问题，事实上这却是一个苦果的开始。大量线上应用反馈   
最新内核的 load 计数存在问题，在 16 核机器 cpu 利用率平均为 20%~30% 的情况下，整体 load 却始终低于 1。

### 解决方案

接到我们线上报告 load 计数偏低的问题之后，进行了研究。最初怀疑对全局 load 计数更新存在竞争。对 16 核的系统，如果都没有进入   
nohz 状态，那么这 16 个核都将在 LOAD_FREQ 周期到达的那个 tick 内执行 per-cpu load 的计算，并更新到全局的 load 中，这   
之间如果存在竞争，整体计算的 load 就会出错。当前每个 cpu 对应 rq 都维护着该 cpu 上一次计算的 load 值，如果发现本次计算 load   
和上一次维护的 load 值之间差值为 0，则不用更新全局 load，否则将差值更新到全局 load 中。正是由于这个机制，全局 load 如果被   
篡改，那么在各个 cpu 维护着自己 load 的情况下，全局 load 最终将可能出现负值。而负值通过各种观察，并没有在线上出现，最终竞   
争条件被排除。

通过 / proc/sched_debug 对线上调度信息进行分析，发现每个时刻在 cpu 上运行的进程基本维持在 2~3 个，每个时刻运行有进程的 cpu 都   
不一样。进一步分析，每个 cpu 上平均每秒出现 sched_goidle 的情况大概为 1000 次左右。因此得到线上每次进入 idle 的间隔为 1ms / 次。   
结合 1HZ=1s=1000ticks，可以得到 1tick =1ms。所以可以得到线上应用基本每一个 tick 就会进入一次 idle！！！ 这个发现就好比   
原来一直用肉眼看一滴水，看着那么完美那么纯净，突然间给你眼前架了一个放大镜，一下出现各种凌乱的杂碎物。 在原有的世界里，   
10ticks 是那么的短暂，一个进程都可能没有运行完成，如今发现 10ticks 内调度 idle 的次数就会有近 10 次。接着用例子对应用场景进行分析：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td></tr><tr><td>0HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>-1</td><td>-1</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3-3=0</td></tr><tr><td>5HZ+1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>+1</td><td>0+1+1+1=3</td></tr><tr><td>5HZ+3</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td></tr><tr><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>-1</td><td>3-1-1-1=0</td></tr><tr><td>5HZ+5</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td></tr><tr><td>5HZ+11</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>0</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>0</td></tr></tbody></table>

(说明：可能你注意到了在 5HZ+5 到 5HZ+11 过程中也有 CPU 从非 idle 进入了 idle，但是为什么没有 - 1，这里是由于每个 cpu 都保留   
了一份该 CPU 上一次计算时的 load，如果 load 没有变化则不进行计算，这几个 cpu 上一次计算 load 为 0，并没有变化)

Orz！load 为 3 的情况直接算成了 0，难怪系统整体 load 会偏低。这里面的一个关键点是：对已经计算过 load 的 cpu，我们对 idle 进   
行了计算，却从未考虑过这给从 idle 进入非 idle 的情况带来的不公平性。这个是当前线上 2.6.32 系统存在的问题。在定位到问题   
之后，跟进到 upstream 中发现 Peter Z 针对该 load 计数问题先后提交了三个 patch，最新的一个 patch 是在 4 月份提交。这三个   
patch 如下：

```
[Patch] sched: Cure load average vs NO_HZ woes
[Patch] sched: Cure more NO_HZ load average woes
[Patch] sched: Fix nohz load accounting – again!


```

这是目前我们 backport 的 patch，基本思想是将进入 idle 造成的 load 变化暂时记录起来，不是每次进入 idle 都导致全局 load 的更新。   
这里面的难点是什么时候将 idle 更新至全局的 load 中？在最开始计算 per-cpu load 的时候需要将之前所有的 idle 都计算进来，   
由于目前各个 CPU 执行 load 计算的先后顺序暂时没有定，所以将这个计算放在每个 cpu 里面都计算一遍是一种方法。接着用示例进行说明：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td><td>tasks_idle</td></tr><tr><td>0HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td><td>0</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>-1</td><td>-1</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3</td><td>-3</td></tr><tr><td>5HZ+1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>3</td></tr><tr><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>+1</td><td>3-3+1+1+1=3</td><td>0</td></tr><tr><td>5HZ+3</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td></tr><tr><td>5HZ+3</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>-1</td><td>3</td><td>-1-1-1=-3</td></tr><tr><td>5HZ+5</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>3</td></tr><tr><td>5HZ+11</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>3</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>3</td><td>-3</td></tr></tbody></table>

  
至此这三个 patch 能够很好的处理我们的之前碰到的进入 idle 的问题。   
将上述三个 patch 整理完后，在淘客前端线上机器中进行测试，测试结果表明 load 得到了明显改善。

### 更细粒度的时间问题

将上述三个 patch 整理完后，似乎一切都完美了，idle 进行了很好的处理，全局 load 的读写分离也很好实现。然而在业务线上的测试结果却出乎意料，虽然添加 patch 之后 load 计数较之前有明显改善，但是依旧偏低。下面是一个抓取的 trace 数据（粗体为 pick_next_idle）：

```
<...>-9195 [000] 11994.232382: calc_global_load: calc_load_task = 0
<...>-9198 [000] 11999.213365: calc_load_account_active: cpu 0 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 1
<...>-9199 [001] 11999.213379: calc_load_account_active: cpu 1 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 2
<...>-9194 [002] 11999.213394: calc_load_account_active: cpu 2 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 3 
<...>-9198 [000] 11999.213406: calc_load_account_active: cpu 0 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 2
<...>-9201 [003] 11999.213409: calc_load_account_active: cpu 3 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 3
<...>-9190 [004] 11999.213424: calc_load_account_active: cpu 4 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 4
<...>-9197 [005] 11999.213440: calc_load_account_active: cpu 5 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 5
<...>-9194 [002] 11999.213448: calc_load_account_active: cpu 2 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 4
<...>-9203 [006] 11999.213455: calc_load_account_active: cpu 6 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 5
<...>-9202 [007] 11999.213471: calc_load_account_active: cpu 7 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 6
<...>-9195 [008] 11999.213487: calc_load_account_active: cpu 8 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 7
<...>-9204 [009] 11999.213502: calc_load_account_active: cpu 9 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 8
<...>-9190 [004] 11999.213517: calc_load_account_active: cpu 4 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 7
<...>-9192 [010] 11999.213519: calc_load_account_active: cpu 10 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 8
<...>-9200 [011] 11999.213533: calc_load_account_active: cpu 11 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 9
<...>-9189 [012] 11999.213548: calc_load_account_active: cpu 12 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 10
<...>-9196 [013] 11999.213564: calc_load_account_active: cpu 13 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 11
<...>-9193 [014] 11999.213580: calc_load_account_active: cpu 14 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 12
<...>-9191 [015] 11999.213596: calc_load_account_active: cpu 15 nr_run 1 nr_uni 0 nr_act 1 delta 1 calc 13
<...>-9204 [009] 11999.213610: calc_load_account_active: cpu 9 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 12<...>-9195 [008] 11999.213645: calc_load_account_active: cpu 8 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 11<...>-9203 [006] 11999.213782: calc_load_account_active: cpu 6 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 10<...>-9197 [005] 11999.213809: calc_load_account_active: cpu 5 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 9<...>-9196 [013] 11999.213930: calc_load_account_active: cpu 13 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 8<...>-9193 [014] 11999.213971: calc_load_account_active: cpu 14 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 7<...>-9189 [012] 11999.214004: calc_load_account_active: cpu 12 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 6<...>-9199 [001] 11999.214032: calc_load_account_active: cpu 1 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 5<...>-9191 [015] 11999.214164: calc_load_account_active: cpu 15 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 4<...>-9202 [007] 11999.214201: calc_load_account_active: cpu 7 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 3<...>-9201 [003] 11999.214353: calc_load_account_active: cpu 3 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 2<...>-9192 [010] 11999.214998: calc_load_account_active: cpu 10 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 1<...>-9200 [011] 11999.215115: calc_load_account_active: cpu 11 nr_run 0 nr_uni 0 nr_act 0 delta -1 calc 0
<...>-9198 [000] 11999.223342: calc_global_load: calc_load_task = 0


```

虽然这个是未加三个 patch 之前的 trace 数据，但是我们依旧能够发现一些问题：原来的 10tick 对我们来说从一个微不足道的小时间片被提升为一个大时间片，相对此低了一个数量级的 1 tick 却一直未真正被我们所重视。trace 数据中，cpu0、2、4 在计算完自己的 load 之后，其他 cpu 计算完自己的 load 之前，进入了 idle，由于默认情况下每个 cpu 都会去将 idle 计算入全局的 load 中，这部分进入 idle 造成的 cpu load 发生的变化会被计算到全局 load 中。依旧出现了之前 10ticks 的不公平问题。示例如下：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td><td>tasks_idle</td></tr><tr><td>0HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td><td>0</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>-1</td><td>-1</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3</td><td>-3</td></tr><tr><td>5HZ+1.3</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3-3+1=1</td><td>0</td></tr><tr><td>5HZ+1.5</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td></tr><tr><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>1+1-1=1</td><td>0</td></tr><tr><td>5HZ+1.7</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>1-1+1=3</td><td>0</td></tr><tr><td>5HZ+3</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>0</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>1</td><td>-1</td></tr><tr><td>5HZ+5</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>&nbsp;</td></tr><tr><td>5HZ+11</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>-1</td><td>&nbsp;</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>1</td><td>-1</td></tr></tbody></table>

线上业务平均每个任务运行时间为 0.3ms，任务运行周期为 0.5ms，因此每个周期 idle 执行时间为 0.2ms。在 1 个 tick 内，cpu 执行完自己 load 的计算之后，很大的概率会在其他 cpu 执行自己 load 计算之前进入 idle，致使整体 load 计算对 idle 和非 idle 不公平，load 计数不准确。 针对该问题，一个简单的方案是检测第一个开始执行 load 计算的 CPU，只在该 CPU 上将之前所有进入 idle 计算的 load 更新至全局的 load，之后的 CPU 不在将 idle 更新至全局的 load 中。这个方案中检测第一个开始执行 load 计算的 CPU 是难点。另外一个解决方案是将 LOAD_FREQ 周期点和全局 load 更新至 avenren 的 LOAD_FREQ+10 时间点作为分界点。对上一次 LOAD_FREQ+10 到本次周期点之间的 idle load，可以在本次 CPU 执行 load 计算时更新至全局的 load；对周期点之后到 LOAD_FREQ+10 时间点之间的 idle load 可以在全局 load 更新至 avenrun 之后更新至全局 load。   
Peter Z 采用的是上述第二个解决，使用 idx 翻转的技术实现。通过 LOAD_FREQ 和 LOAD_FREQ+10 两个时间点，可以将 idle 导致的 load 分为两部分，一部分为 LOAD_FREQ 至 LOAD_FREQ+10 这部分，这部分 load 由于在各个 cpu 计算 load 之后到全局 avenrun 更新之间，不应该直接更新至全局 load 中；另一部分为 LOAD_FREQ+10 至下一个周期点 LOAD_FREQ，这部分 idle 导致的 load 可以随时更新至全局的 load 中。实现中使用了一个含 2 个元素的数组，用于对这两部分 load 进行存储，但这两部分并不是分别存储在数组的不同元素中，而是每个 LOAD_FREQ 周期存储一个元素。如下图所示，在 0~5 周期中，这两部分 idle 都存储在数组下标为 1 的元素中。5~10 周期内，这两个部分都存储在数组下标为 0 的元素中。在 5~10 周期中，各个 cpu 计算 load 时读取的 idle 为 0~5 周期存储的；在计算完 avenrun 之后，更新 idle 至全局 load 时读取的为 5~10 周期中前 10 个 ticks 的 idle 导致的 load。这样在 10~15 周期中，各个 cpu 计算 load 时读取的 idle 即为更新 avenrun 之后产生的 idle load。具体实现方案如下：

```
      0             5             10            15          --->HZ
        +10           +10           +10           +10       ---> ticks
      |-|-----------|-|-----------|-|-----------|-|
idx:0   1     1       0     0       1      1      0   
  w:0 1 1         1 0 0         0 1 1         1 0 0
  r:0 0 1         1 1 0         0 0 1         1 1 0


```

```
说明：1）0 5 10 15代表的为0HZ、5HZ、10HZ、15HZ，这个就是各个cpu执行load计算的周期点
     2）+10表示周期点之后10ticks（即为计算avenrun的时间点）
     3）idx表示当前的idx值（每次只取最后一位的值，因此变化范围为0~1）
     4）w后面3列值，第一列表示周期点之前idle计算值写入的数组idx；第二列表示周期点到+10之间idle导致的load变化写入的数
       组idx；第三列表示计算万avenrun之后到下一个周期点之间idle写入的数组idx；


```

用如下示例进行说明（假定 0HZ+11 之后 idx 为 0）：

<table border="1" cellspacing="1" cellpadding="1" align="center"><caption>32 内核 loadavg 计算</caption><tbody><tr><td>&nbsp;</td><td>cpu0</td><td>cpu1</td><td>cpu2</td><td>cpu3</td><td>cpu4</td><td>cpu5</td><td>cpu6</td><td>cpu7</td><td>calc_load_tasks</td><td>idle[0]</td><td>idle[1]</td><td>idx</td></tr><tr><td>0HZ+11</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>3</td><td>0</td><td>0</td><td>0</td></tr><tr><td>5HZ</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>-1</td><td>-1</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3</td><td>-3</td><td>0</td><td>0</td></tr><tr><td>5HZ+1.3</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3-3+1=1</td><td>0</td><td>0</td><td>0</td></tr><tr><td>5HZ+1.5</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td></tr><tr><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>1+1=2</td><td>0</td><td>-1</td><td>0</td></tr><tr><td>5HZ+1.7</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>&nbsp;</td><td>+1</td><td>&nbsp;</td><td>2+1=3</td><td>0</td><td>-2</td><td>0</td></tr><tr><td>5HZ+3</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr><tr><td>5HZ+3</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3</td><td>0</td><td>-2</td><td>0</td></tr><tr><td>5HZ+5</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td></tr><tr><td>5HZ+11</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>1</td><td>&nbsp;</td></tr><tr><td>calc_global_load</td><td>&lt;--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>--</td><td>3</td><td>0</td><td>-2</td><td>0</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>3-2=1</td><td>0</td><td>0</td><td>1</td></tr><tr><td>5HZ+15</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>1</td><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td><td>-1</td><td>&nbsp;</td><td>1</td><td>0</td><td>-1</td><td>1</td></tr></tbody></table>

### 再次回归到公平性问题

经过对细粒度 idle 调度问题进行解决，在线上业务整体 load 得到了很好的改善。原来平均运行进程数在 16 的情况下，load 一直徘徊在 1 左右，改善之后 load 回升到了 15 左右。   
然而这个 patch 发布到社区，经过相关报告 load 计数有问题的社区人员进行测试之后，发现系统的 load 整体偏高，而且很多时候都是趋近于系统总运行进程数。为了验证这个 patch 的效果，升级了一台添加该 patch 的机器，进行观察，确实发现升级之后机器的 load 比原有 18 还高出 1 左右。   
又是一次深度的思考，是否当前这个 patch 中存在 BUG? 是否从第一个 CPU 到最后一个 CPU 之间的 idle 就应该直接计算在整体 load 中？ 对于高频度调度 idle 的情况，这部分 idle 是不应该加入到全局 load 中，否则无论系统运行多少进程，最终 load 都会始终徘徊在 0 左右。因此这部分 idle 必须不能够加入到全局 load 中。通过 trace 数据进行分析，也证明了 patch 运行的行为符合预期，并不存在异常。   
如果假设之前所有的 patch 都没有问题，是否存在其他情况会导致系统 load 偏高？导致 load 偏高，一个很可能的原因就是在该计算为 idle 时，计算为非 idle 情况。为此先后提出了负载均衡的假设、计算 load 时有进程 wakeup 到当前运行队列的假设，最终都被一一排除。   
进一步观察 trace 数据，发现几乎每次都是在做完该 CPU 上 load 计算之后，该 CPU 立即就进入 idle。16 个 CPU，每个 CPU 都是在非 idle 的时候执行 load 计算，执行完 load 计算之后又都是立即进入 idle。而且这种情况是在每一次做 load 计算时都是如此，并非偶然。按照采样逻辑，由于采样时间点不受系统运行状况影响，对于频繁进出 idle 的情况，采样时 idle 和非 idle 都应该会出现。如今只有非 idle 情况，意味着采样时间点选取存在问题。   
进一步分析，如果采样点处于 idle 内部，由于 nohz 导致进入 idle 之后并不会周期执行 sched_tick，也就无法执行 load 计算，看起来似乎会导致 idle load 计算丢失。事实并不是，之前计算 idle load 就是为了避免进入 nohz 导致 load 计算丢失的问题，在进入 idle 调度前会将当前 cpu 上的 load 计算入 idle load 中，这样其他 cpu 执行 load 计算时会将这部分 load 一同计算入内。   
但是基于上述逻辑，也可以得到一个结论：如果采样点在 idle 内部，默认应该是将进入 idle 时的 load 作为该 cpu 上采样 load。事实是否如此？继续分析，该 CPU 如果从 nohz 重新进入调度，这个时候由于采样时间点还存在，而且间隔上一次采样已经超过一个 LOAD_FREQ 周期，会再次执行 load 计算。再次执行 load 计算会覆盖原有进入 idle 时计算的 load，这直接的一个结果是，该 CPU 上的采样点从 idle 内部变成了非 idle！ 问题已经变得清晰，对采样点在 idle 内部的情况，实际计算 load 应该为进入 idle 时该 cpu 上的 load，然而由于该 cpu 上采样时间点没有更新，导致退出 nohz 状态之后会再次执行 load 计算，最终将退出 nohz 状态之后的 load 作为采样的 load。  问题已经清楚，解决方案也比较简单：在退出 nohz 状态时检测采样时间点在当前时间点之前，如果是，则意味着这次采样时间点在 idle 内部，这 个周期内不需要再次计算该 CPU 上的 load。     转自：[http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&diff=514&oldid=293](http://kernel.taobao.org/index.php?title=Loadavg%E9%97%AE%E9%A2%98%E5%88%86%E6%9E%90&diff=514&oldid=293)

[img-0]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-1]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-2]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-3]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-4]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-5]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-6]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-7]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-8]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-9]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-10]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-11]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-12]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-13]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-14]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-15]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-16]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-17]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-18]:http://assets.cnblogs.com/images/copycode.gifjavascript:void0

[img-19]:data:application/xml;base64,PD94bWwgdmVyc2lvbj0nMS4wJyBlbmNvZGluZz0ndXRmLTgnID8+CjxFcnJvcj4KCTxDb2RlPk5vU3VjaEtleTwvQ29kZT4KCTxNZXNzYWdlPlRoZSBzcGVjaWZpZWQga2V5IGRvZXMgbm90IGV4aXN0LjwvTWVzc2FnZT4KCTxSZXNvdXJjZT4vaW1hZ2VzL2NvcHljb2RlLmdpZmphdmFzY3JpcHQ6dm9pZDA8L1Jlc291cmNlPgoJPFJlcXVlc3RJZD5OamxpTUdaaU16ZGZNMkV5T1RZNE1EbGZNVEl4Wm1aZk16WTRaVFprTVE9PTwvUmVxdWVzdElkPgoJPFRyYWNlSWQ+T0dWbVl6WmlNbVF6WWpBMk9XTmhPRGswTlRSa01UQmlPV1ZtTURBeE9EYzBPV1JrWmprMFpETTFObUkxTTJFMk1UUmxZMk16WkRobU5tSTVNV0kxT1dSbFpEazVZemd5T1RnMFpUZzJPREExT0RGak9HWTBNV0ZoWVdGaE9UZG1OV0UyTkRrNE9XRXdNVEZrWWpGaVlqQTJNVEl5TmpBM05HTmhOemxoWVRjPTwvVHJhY2VJZD4KPC9FcnJvcj4KCg==