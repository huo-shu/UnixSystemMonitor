> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.man7.org](https://www.man7.org/linux/man-pages/man5/proc_stat.5.html)

<table><tbody><tr><td><p data-imt-p="1" data-imt_insert_failed_reason="same_text"><a href="../../../index.html">man7.org</a> &gt; Linux &gt; <a href="../index.html">man-pages</a></p></td><td><p><a href="http://man7.org/training/" data-imt-p="1">Linux/UNIX system programming training</a></p></td></tr></tbody></table>

proc_stat(5) — Linux manual page
================================

<table><tbody><tr><td><p data-imt-p="1"><a href="#NAME">NAME</a> | <a href="#DESCRIPTION">DESCRIPTION</a> | <a href="#SEE_ALSO">SEE&nbsp;ALSO</a> | <a href="#COLOPHON">COLOPHON</a></p></td></tr><tr><td><form method="get" action="https://www.google.com/search"><fieldset><input type="text"> <input type="hidden"> <input type="submit"></fieldset></form></td><td></td></tr></tbody></table>

```
proc_stat(5)               File Formats Manual               proc_stat(5)


```

[](#NAME)NAME        
-----------------------------------------

```
       /proc/stat - kernel system statistics


```

[](#DESCRIPTION)DESCRIPTION     
-------------------------------------------------------

```markdown
       /proc/stat
              kernel/system statistics.  Varies with architecture.
              Common entries include:

              cpu 10132153 290696 3084719 46828483 16683 0 25195 0 175628
              0
              cpu0 1393280 32966 572056 13343292 6130 0 17875 0 23933 0
                     The amount of time, measured in units of USER_HZ
                     (1/100ths of a second on most architectures, use
                     sysconf(_SC_CLK_TCK) to obtain the right value),
                     that the system ("cpu" line) or the specific CPU
                     ("cpuN" line) spent in various states:

                     user   (1) Time spent in user mode.

                     nice   (2) Time spent in user mode with low priority
                            (nice).

                     system (3) Time spent in system mode.

                     idle   (4) Time spent in the idle task.  This value
                            should be USER_HZ times the second entry in
                            the /proc/uptime pseudo-file.

                     iowait (since Linux 2.5.41)
                            (5) Time waiting for I/O to complete.  This
                            value is not reliable, for the following
                            reasons:

                            •  The CPU will not wait for I/O to complete;
                               iowait is the time that a task is waiting
                               for I/O to complete.  When a CPU goes into
                               idle state for outstanding task I/O,
                               another task will be scheduled on this
                               CPU.

                            •  On a multi-core CPU, the task waiting for
                               I/O to complete is not running on any CPU,
                               so the iowait of each CPU is difficult to
                               calculate.

                            •  The value in this field may decrease in
                               certain conditions.

                     irq (since Linux 2.6.0)
                            (6) Time servicing interrupts.

                     softirq (since Linux 2.6.0)
                            (7) Time servicing softirqs.

                     steal (since Linux 2.6.11)
                            (8) Stolen time, which is the time spent in
                            other operating systems when running in a
                            virtualized environment

                     guest (since Linux 2.6.24)
                            (9) Time spent running a virtual CPU for
                            guest operating systems under the control of
                            the Linux kernel.

                     guest_nice (since Linux 2.6.33)
                            (10) Time spent running a niced guest
                            (virtual CPU for guest operating systems
                            under the control of the Linux kernel).

              page 5741 1808
                     The number of pages the system paged in and the
                     number that were paged out (from disk).

              swap 1 0
                     The number of swap pages that have been brought in
                     and out.

              intr 1462898
                     This line shows counts of interrupts serviced since
                     boot time, for each of the possible system
                     interrupts.  The first column is the total of all
                     interrupts serviced including unnumbered
                     architecture specific interrupts; each subsequent
                     column is the total for that particular numbered
                     interrupt.  Unnumbered interrupts are not shown,
                     only summed into the total.

              disk_io: (2,0):(31,30,5764,1,2) (3,0):...
                     (major,disk_idx):(noinfo, read_io_ops, blks_read,
                     write_io_ops, blks_written)
                     (Linux 2.4 only)

              ctxt 115315
                     The number of context switches that the system
                     underwent.

              btime 769041601
                     boot time, in seconds since the Epoch, 1970-01-01
                     00:00:00 +0000 (UTC).

              processes 86031
                     Number of forks since boot.

              procs_running 6
                     Number of processes in runnable state.  (Linux
                     2.5.45 onward.)

              procs_blocked 2
                     Number of processes blocked waiting for I/O to
                     complete.  (Linux 2.5.45 onward.)

              softirq 229245889 94 60001584 13619 5175704 2471304 28
              51212741 59130143 0 51240672
                     This line shows the number of softirq for all CPUs.
                     The first column is the total of all softirqs and
                     each subsequent column is the total for particular
                     softirq.  (Linux 2.6.31 onward.)


```

AI翻译：

/proc/stat：内核/系统统计信息，内容因体系结构而异。
常见项包括：

```
cpu 10132153 290696 3084719 46828483 16683 0 25195 0 175628 0
cpu0 1393280 32966 572056 13343292 6130 0 17875 0 23933 0
```

表示系统（`cpu` 行）或某个具体 CPU 核心（`cpuN` 行）在**各种状态下花费的时间**，单位为 **USER_HZ**（大多数架构为 1/100 秒，可通过 `sysconf(_SC_CLK_TCK)` 获取准确值）。

各字段含义：
1. **user**：用户态时间
2. **nice**：低优先级（已调整 nice 值）用户态时间
3. **system**：内核态时间
4. **idle**：空闲任务时间。该值应等于 `USER_HZ` 乘以 `/proc/uptime` 中的第二个数值。
5. **iowait**（Linux 2.5.41 起）：等待 I/O 完成的时间。
   该值并不可靠，原因如下：
   - CPU 本身不会等待 I/O，iowait 是任务等待 I/O 的时间；CPU 空闲时会调度其他任务。
   - 多核场景下，等待 I/O 的任务不占用任何 CPU，单个 CPU 的 iowait 难以准确计算。
   - 某些情况下该值可能会减少。
6. **irq**（Linux 2.6.0 起）：处理硬件中断的时间
7. **softirq**（Linux 2.6.0 起）：处理软中断的时间
8. **steal**（Linux 2.6.11 起）：虚拟化环境中被其他操作系统“窃取”的时间
9. **guest**（Linux 2.6.24 起）：为虚拟机运行虚拟 CPU 的时间
10. **guest_nice**（Linux 2.6.33 起）：运行已调整 nice 值的虚拟机的时间

...

[](#SEE_ALSO)SEE ALSO        
-------------------------------------------------

```
       proc(5)


```

[](#COLOPHON)COLOPHON       
-------------------------------------------------

```
       This page is part of the man-pages (Linux kernel and C library
       user-space interface documentation) project.  Information about
       the project can be found at 
       ⟨https://www.kernel.org/doc/man-pages/⟩.  If you have a bug report
       for this manual page, see
       ⟨https://git.kernel.org/pub/scm/docs/man-pages/man-pages.git/tree/CONTRIBUTING⟩.
       This page was obtained from the tarball man-pages-6.16.tar.gz
       fetched from
       ⟨https://mirrors.edge.kernel.org/pub/linux/docs/man-pages/⟩ on
       2026-01-16.  If you discover any rendering problems in this HTML
       version of the page, or you believe there is a better or more up-
       to-date source for the page, or you have corrections or
       improvements to the information in this COLOPHON (which is not
       part of the original manual page), send a mail to
       man-pages@man7.org

Linux man-pages 6.16            2025-05-17                   proc_stat(5)


```

<table><tbody><tr><td><p data-imt-p="1">HTML rendering created 2026-01-16 by <a href="https://man7.org/mtk/index.html">Michael Kerrisk</a>, author of <a href="https://man7.org/tlpi/"><em>The Linux Programming Interface</em></a>.</p><p data-imt-p="1">For details of in-depth <strong>Linux/UNIX system programming training courses</strong> that I teach, look <a href="https://man7.org/training/">here</a>.</p><p data-imt-p="1">Hosting by <a href="https://www.jambit.com/index_en.html">jambit GmbH</a>.</p></td><td></td><td><a href="https://man7.org/tlpi/"><img class="" src="https://man7.org/tlpi/cover/TLPI-front-cover-vsmall.png"></a></td></tr></tbody></table>

Default Statcounter code for man7.org/linux/man-pages http://www.man7.org/linux/man-pages

[![Web Analytics Made Easy -
StatCounter](https://c.statcounter.com/7422636/0/9b6714ff/1/)](https://statcounter.com/ "Web Analytics
Made Easy - StatCounter")