```markdown
   3a. DESCRIPTIONS of Fields
       Listed  below  are top's available process fields (columns).  They are shown in strict ascii alphabetical
       order.  You may customize their position and whether or not they are displayable  with  the  `f'  or  `F'
       (Fields Management) interactive commands.

       Any field is selectable as the sort field, and you control whether they are sorted high-to-low or low-to-
       high.  For additional information on sort provisions see topic 4c. TASK AREA Commands, SORTING.

       The fields related to physical memory or virtual memory reference `(KiB)' which is the unsuffixed display
       mode.   Such fields may, however, be scaled from KiB through PiB.  That scaling is influenced via the `e'
       interactive command or established for startup through a build option.

        1. %CPU  --  CPU Usage
           The task's share of the elapsed CPU time since the last screen update, expressed as a  percentage  of
           total CPU time.

           In  a  true SMP environment, if a process is multi-threaded and top is not operating in Threads mode,
           amounts greater than 100% may be reported.  You toggle Threads mode with the `H' interactive command.

           Also for multi-processor environments, if Irix mode is Off, top will operate in Solaris mode where  a
           task's cpu usage will be divided by the total number of CPUs.  You toggle Irix/Solaris modes with the
           `I' interactive command.

        2. %MEM  --  Memory Usage (RES)
           A task's currently resident share of available physical memory.

           See `OVERVIEW, Linux Memory Types' for additional details.

        3. CGNAME  --  Control Group Name
           The name of the control group to which a process belongs, or `-' if not applicable for that process.

           This  will  typically  be  the  last entry in the full list of control groups as shown under the next
           heading (CGROUPS).  And as is true there, this field is also variable width.

        4. CGROUPS  --  Control Groups
           The names of the control group(s) to which a process belongs, or  `-'  if  not  applicable  for  that
           process.

           Control  Groups  provide  for  allocating  resources  (cpu,  memory,  network  bandwidth, etc.) among
           installation-defined groups of processes.  They enable fine-grained control over allocating, denying,
           prioritizing, managing and monitoring those resources.

           Many different hierarchies of cgroups can exist simultaneously on a  system  and  each  hierarchy  is
           attached to one or more subsystems.  A subsystem represents a single resource.

           Note:  The CGROUPS field, unlike most columns, is not fixed-width.  When displayed, it plus any other
           variable width columns will  be  allocated  all  remaining  screen  width  (up  to  the  maximum  512
           characters).   Even  so,  such  variable  width  fields could still suffer truncation.  See topic 5c.
           SCROLLING a Window for additional information on accessing any truncated data.

        5. CODE  --  Code Size (KiB)
           The amount of physical memory currently devoted to executable code, also known as the  Text  Resident
           Set size or TRS.

           See `OVERVIEW, Linux Memory Types' for additional details.

        6. COMMAND  --  Command Name or Command Line
           Display  the  command  line  used  to start a task or the name of the associated program.  You toggle
           between command line and name with `c', which is  both  a  command-line  option  and  an  interactive
           command.

           When  you've  chosen to display command lines, processes without a command line (like kernel threads)
           will be shown with only the program name in brackets, as in this example:
               [kthreadd]

           This field may also be impacted by the forest view display mode.  See the `V' interactive command for
           additional information regarding that mode.

           Note: The COMMAND field, unlike most columns, is not fixed-width.  When displayed, it plus any  other
           variable  width  columns  will  be  allocated  all  remaining  screen  width  (up  to the maximum 512
           characters).  Even so, such variable width fields could still suffer truncation.  This is  especially
           true  for this field when command lines are being displayed (the `c' interactive command.)  See topic
           5c. SCROLLING a Window for additional information on accessing any truncated data.

        7. DATA  --  Data + Stack Size (KiB)
           The amount of private memory reserved by a process.  It is also known as the  Data  Resident  Set  or
           DRS.   Such  memory may not yet be mapped to physical memory (RES) but will always be included in the
           virtual memory (VIRT) amount.

           See `OVERVIEW, Linux Memory Types' for additional details.

        8. ENVIRON  --  Environment variables
           Display all of the environment variables, if  any,  as  seen  by  the  respective  processes.   These
           variables  will  be  displayed  in their raw native order, not the sorted order you are accustomed to
           seeing with an unqualified `set'.

           Note: The ENVIRON field, unlike most columns, is not fixed-width.  When displayed, it plus any  other
           variable  width  columns  will  be  allocated  all  remaining  screen  width  (up  to the maximum 512
           characters).  Even so, such variable width fields could still suffer truncation.  This is  especially
           true  for  this  field.  See topic 5c. SCROLLING a Window for additional information on accessing any
           truncated data.

        9. Flags  --  Task Flags
           This column represents the task's  current  scheduling  flags  which  are  expressed  in  hexadecimal
           notation and with zeros suppressed.  These flags are officially documented in <linux/sched.h>.

       10. GID  --  Group Id
           The effective group ID.

       11. GROUP  --  Group Name
           The effective group name.

       12. LXC  --  Lxc Container Name
           The  name  of the lxc container within which a task is running.  If a process is not running inside a
           container, a dash (`-') will be shown.

       13. NI  --  Nice Value
           The nice value of the task.  A negative nice value means higher priority,  whereas  a  positive  nice
           value  means  lower  priority.   Zero  in  this  field  simply means priority will not be adjusted in
           determining a task's dispatch-ability.

       14. OOMa  --  Out of Memory Adjustment Factor
           The value, ranging from -1000 to +1000, added to the current out of memory score (OOMs) which is then
           used to determine which task to kill when memory is exhausted.

       15. OOMs  --  Out of Memory Score
           The value, ranging from 0 to +1000, used to select task(s) to kill when memory  is  exhausted.   Zero
           translates to `never kill' whereas 1000 means `always kill'.

       16. P  --  Last used CPU (SMP)
           A  number  representing  the  last used processor.  In a true SMP environment this will likely change
           frequently since the kernel intentionally uses weak affinity.  Also, the very act of running top  may
           break  this  weak  affinity  and cause more processes to change CPUs more often (because of the extra
           demand for cpu time).

       17. PGRP  --  Process Group Id
           Every process is member of a unique process group which is used for distribution of  signals  and  by
           terminals  to  arbitrate requests for their input and output.  When a process is created (forked), it
           becomes a member of the process group of its parent.  By convention, this value equals the process ID
           (see PID) of the first member of a process group, called the process group leader.

       18. PID  --  Process Id
           The task's unique process ID, which periodically wraps, though never restarting at zero.   In  kernel
           terms, it is a dispatchable entity defined by a task_struct.

           This  value  may  also be used as: a process group ID (see PGRP); a session ID for the session leader
           (see SID); a thread group ID for the thread group leader (see TGID); and a TTY process group  ID  for
           the process group leader (see TPGID).

       19. PPID  --  Parent Process Id
           The process ID (pid) of a task's parent.

       20. PR  --  Priority
           The  scheduling  priority  of  the task.  If you see `rt' in this field, it means the task is running
           under real time scheduling priority.

           Under linux, real time priority is somewhat misleading since traditionally the operating  itself  was
           not preemptible.  And while the 2.6 kernel can be made mostly preemptible, it is not always so.

       21. RES  --  Resident Memory Size (KiB)
           A  subset  of the virtual address space (VIRT) representing the non-swapped physical memory a task is
           currently using.  It is also the sum of the RSan, RSfd and RSsh fields.

           It can include private anonymous pages, private pages mapped to files (including program  images  and
           shared  libraries)  plus  shared  anonymous  pages.   All  such  memory  is  backed  by the swap file
           represented separately under SWAP.

           Lastly, this field may also include shared file-backed pages which, when modified, act as a dedicated
           swap file and thus will never impact SWAP.

           See `OVERVIEW, Linux Memory Types' for additional details.

       22. RSan  --  Resident Anonymous Memory Size (KiB)
           A subset of resident memory (RES) representing private pages not mapped to a file.

       23. RSfd  --  Resident File-Backed Memory Size (KiB)
           A subset of resident memory (RES) representing the implicitly shared pages supporting program  images
           and shared libraries.  It also includes explicit file mappings, both private and shared.

       24. RSlk  --  Resident Locked Memory Size (KiB)
           A subset of resident memory (RES) which cannot be swapped out.

       25. RSsh  --  Resident Shared Memory Size (KiB)
           A subset of resident memory (RES) representing the explicitly shared anonymous shm*/mmap pages.

       26. RUID  --  Real User Id
           The real user ID.

       27. RUSER  --  Real User Name
           The real user name.

       28. S  --  Process Status
           The status of the task which can be one of:
               D = uninterruptible sleep
               R = running
               S = sleeping
               T = stopped by job control signal
               t = stopped by debugger during trace
               Z = zombie

           Tasks  shown  as running should be more properly thought of as ready to run  --  their task_struct is
           simply represented on the Linux run-queue.  Even without a true SMP machine,  you  may  see  numerous
           tasks in this state depending on top's delay interval and nice value.

       29. SHR  --  Shared Memory Size (KiB)
           A  subset  of  resident  memory  (RES)  that  may be used by other processes.  It will include shared
           anonymous pages and shared file-backed pages.   It  also  includes  private  pages  mapped  to  files
           representing program images and shared libraries.

           See `OVERVIEW, Linux Memory Types' for additional details.

       30. SID  --  Session Id
           A  session  is  a collection of process groups (see PGRP), usually established by the login shell.  A
           newly forked process joins the session of its creator.  By convention, this value equals the  process
           ID  (see  PID)  of  the  first member of the session, called the session leader, which is usually the
           login shell.

       31. SUID  --  Saved User Id
           The saved user ID.

       32. SUPGIDS  --  Supplementary Group IDs
           The IDs of any supplementary group(s) established at login or inherited from a task's  parent.   They
           are displayed in a comma delimited list.

           Note:  The SUPGIDS field, unlike most columns, is not fixed-width.  When displayed, it plus any other
           variable width columns will  be  allocated  all  remaining  screen  width  (up  to  the  maximum  512
           characters).   Even  so,  such  variable  width  fields could still suffer truncation.  See topic 5c.
           SCROLLING a Window for additional information on accessing any truncated data.

       33. SUPGRPS  --  Supplementary Group Names
           The names of any supplementary group(s) established at login or inherited from a task's parent.  They
           are displayed in a comma delimited list.

           Note: The SUPGRPS field, unlike most columns, is not fixed-width.  When displayed, it plus any  other
           variable  width  columns  will  be  allocated  all  remaining  screen  width  (up  to the maximum 512
           characters).  Even so, such variable width fields could  still  suffer  truncation.   See  topic  5c.
           SCROLLING a Window for additional information on accessing any truncated data.

       34. SUSER  --  Saved User Name
           The saved user name.

       35. SWAP  --  Swapped Size (KiB)
           The formerly resident portion of a task's address space written to the swap file when physical memory
           becomes over committed.

           See `OVERVIEW, Linux Memory Types' for additional details.

       36. TGID  --  Thread Group Id
           The  ID  of  the thread group to which a task belongs.  It is the PID of the thread group leader.  In
           kernel terms, it represents those tasks that share an mm_struct.

       37. TIME  --  CPU Time
           Total CPU time the task has used since it started.  When Cumulative  mode  is  On,  each  process  is
           listed  with  the  cpu time that it and its dead children have used.  You toggle Cumulative mode with
           `S', which is both a command-line option and an interactive command.  See the `S' interactive command
           for additional information regarding this mode.

       38. TIME+  --  CPU Time, hundredths
           The same as TIME, but reflecting more granularity through hundredths of a second.

       39. TPGID  --  Tty Process Group Id
           The process group ID of the foreground process for the connected tty, or  -1  if  a  process  is  not
           connected  to  a  terminal.  By convention, this value equals the process ID (see PID) of the process
           group leader (see PGRP).

       40. TTY  --  Controlling Tty
           The name of the controlling terminal.  This is usually the device (serial port, pty, etc.) from which
           the process was started, and which it uses for  input  or  output.   However,  a  task  need  not  be
           associated with a terminal, in which case you'll see `?' displayed.

       41. UID  --  User Id
           The effective user ID of the task's owner.

       42. USED  --  Memory in Use (KiB)
           This  field  represents  the  non-swapped  physical memory a task is using (RES) plus the swapped out
           portion of its address space (SWAP).

           See `OVERVIEW, Linux Memory Types' for additional details.

       43. USER  --  User Name
           The effective user name of the task's owner.

       44. VIRT  --  Virtual Memory Size (KiB)
           The total amount of virtual memory used by the task.  It includes all code, data and shared libraries
           plus pages that have been swapped out and pages that have been mapped but not used.

           See `OVERVIEW, Linux Memory Types' for additional details.

       45. WCHAN  --  Sleeping in Function
           This field will show the name of the kernel  function  in  which  the  task  is  currently  sleeping.
           Running tasks will display a dash (`-') in this column.

       46. nDRT  --  Dirty Pages Count
           The number of pages that have been modified since they were last written to auxiliary storage.  Dirty
           pages  must  be written to auxiliary storage before the corresponding physical memory location can be
           used for some other virtual page.

       47. nMaj  --  Major Page Fault Count
           The number of major page faults that have occurred for a task.  A page fault occurs  when  a  process
           attempts  to read from or write to a virtual page that is not currently present in its address space.
           A major page fault is when auxiliary storage access is involved in making that page available.

       48. nMin  --  Minor Page Fault count
           The number of minor page faults that have occurred for a task.  A page fault occurs  when  a  process
           attempts  to read from or write to a virtual page that is not currently present in its address space.
           A minor page fault does not involve auxiliary storage access in making that page available.

       48. nTH  --  Number of Threads
           The number of threads associated with a process.

       50. nsIPC  --  IPC namespace
           The Inode of the namespace used to isolate interprocess communication (IPC) resources such as  System
           V IPC objects and POSIX message queues.

       51. nsMNT  --  MNT namespace
           The  Inode  of the namespace used to isolate filesystem mount points thus offering different views of
           the filesystem hierarchy.

       52. nsNET  --  NET namespace
           The Inode of the namespace used to isolate resources  such  as  network  devices,  IP  addresses,  IP
           routing, port numbers, etc.

       53. nsPID  --  PID namespace
           The  Inode  of  the namespace used to isolate process ID numbers meaning they need not remain unique.
           Thus, each such namespace could have its own `init/systemd' (PID #1) to manage various initialization
           tasks and reap orphaned child processes.

       54. nsUSER  --  USER namespace
           The Inode of the namespace used to isolate the user and group ID numbers.  Thus, a process could have
           a normal unprivileged user ID outside a user namespace while having a user ID of 0,  with  full  root
           privileges, inside that namespace.

       55. nsUTS  --  UTS namespace
           The  Inode  of  the  namespace  used to isolate hostname and NIS domain name.  UTS simply means "UNIX
           Time-sharing System".

       56. vMj  --  Major Page Fault Count Delta
           The number of major page faults that have occurred since the last update (see nMaj).

       57. vMn  --  Minor Page Fault Count Delta
           The number of minor page faults that have occurred since the last update (see nMin).
```

AI翻译：

# 3a. 字段说明
下面列出的是 top 命令支持的进程字段（列），严格按照 ASCII 字母顺序排列。
你可以通过 `f` 或 `F`（字段管理）交互命令**自定义字段的显示与否及排列顺序**。

任意字段均可作为排序字段，并可控制升序或降序排列。
有关排序的更多说明，参见主题 4c. 任务区命令·排序。

与物理内存或虚拟内存相关的字段标注为 `(KiB)`，这是无单位后缀的显示模式。
这类字段也可通过 `e` 交互命令，或在编译时指定启动参数，将显示单位从 KiB 逐级放大到 PiB。

---

1. **%CPU — CPU 使用率**
自上次屏幕刷新以来，任务占用的 CPU 时间占总 CPU 时间的百分比。
在真正的 SMP 环境中，如果进程是多线程的，而 top 未工作在线程模式下，可能会显示超过 100% 的值。可通过 `H` 命令切换线程模式。
在多处理器环境中，如果 Irix 模式关闭，top 将工作在 Solaris 模式下，此时任务的 CPU 使用率会除以总 CPU 核心数。可通过 `I` 命令切换 Irix/Solaris 模式。

2. **%MEM — 内存使用率（RES）**
任务当前占用的可用物理内存比例。
详见「概述：Linux 内存类型」。

3. **CGNAME — 控制组名称**
进程所属的控制组（cgroup）名称，不适用则显示 `-`。
通常是下一字段 CGROUPS 完整路径中的最后一项。该字段为可变宽度。

4. **CGROUPS — 控制组**
进程所属的所有控制组名称，不适用则显示 `-`。
控制组用于在用户定义的进程组间分配资源（CPU、内存、网络带宽等），实现对资源的精细分配、限制、优先级调控、管理与监控。
系统中可同时存在多个不同的 cgroup 层级，每个层级关联一个或多个子系统，子系统对应单一资源。
注：CGROUPS 字段非固定宽度，会与其他可变宽度字段共享剩余屏幕宽度（最大 512 字符），仍可能被截断。详见主题 5c. 窗口滚动。

5. **CODE — 代码大小（KiB）**
当前用于可执行代码的物理内存大小，也称为文本常驻集大小（TRS）。
详见「概述：Linux 内存类型」。

6. **COMMAND — 命令名称或命令行**
显示启动任务的命令行或程序名称。可通过 `c`（命令行参数与交互命令通用）在名称与命令行之间切换。
选择显示命令行时，无命令行的进程（如内核线程）将只显示带方括号的程序名，例如：`[kthreadd]`。
该字段也会受树形视图模式影响，详见 `V` 交互命令。
注：COMMAND 字段非固定宽度，显示命令行时极易被截断。

7. **DATA — 数据+栈大小（KiB）**
进程预留的私有内存大小，也称为数据常驻集（DRS）。
该内存可能尚未映射到物理内存（RES），但一定会计入虚拟内存（VIRT）。
详见「概述：Linux 内存类型」。

8. **ENVIRON — 环境变量**
显示对应进程可见的所有环境变量（如有），按原始顺序展示，而非 `set` 命令常见的排序结果。
注：该字段非固定宽度，极易被截断。

9. **Flags — 任务标志**
以十六进制表示的任务当前调度标志，省略前导零。
这些标志的官方文档位于 `<linux/sched.h>`。

10. **GID — 组 ID**
有效组 ID。

11. **GROUP — 组名**
有效组名。

12. **LXC — LXC 容器名称**
任务运行所在的 LXC 容器名称，不在容器内则显示 `-`。

13. **NI — Nice 值**
任务的 Nice 值。
负值 = 更高优先级；正值 = 更低优先级；0 = 不调整优先级。

14. **OOMa — OOM 调整因子**
取值范围 -1000～+1000，会加到当前 OOM 评分（OOMs）上，用于在内存耗尽时决定优先杀死哪些任务。

15. **OOMs — OOM 评分**
取值范围 0～+1000，用于在内存耗尽时选择要杀死的任务。
0 = 永不杀死；1000 = 总是杀死。

16. **P — 最后使用的 CPU（SMP）**
任务上一次运行所在的处理器编号。
在 SMP 环境中，由于内核使用弱亲和性，该值会频繁变化。运行 top 本身也可能打断弱亲和性，导致进程更频繁地切换 CPU。

17. **PGRP — 进程组 ID**
每个进程都属于唯一的进程组，用于信号分发和终端 I/O 仲裁。
进程创建时会继承父进程的进程组。惯例上，该值等于进程组首进程（进程组组长）的 PID。

18. **PID — 进程 ID**
任务的唯一进程 ID，会循环滚动但不会从 0 重新开始。
在内核中，它是由 `task_struct` 定义的可调度实体。

19. **PPID — 父进程 ID**
任务的父进程 PID。

20. **PR — 优先级**
任务的调度优先级。
若该字段显示 `rt`，表示任务运行在**实时调度优先级**下。

21. **RES — 常驻内存大小（KiB）**
虚拟地址空间（VIRT）的子集，代表任务当前使用的**未被换出的物理内存**。
等于 RSan + RSfd + RSsh。
可包含私有匿名页、私有文件映射页（程序镜像、共享库）、共享匿名页。
也可能包含共享文件映射页，这类内存被修改时自身充当交换空间，不会计入 SWAP。
详见「概述：Linux 内存类型」。

22. **RSan — 常驻匿名内存大小（KiB）**
RES 的子集，指未映射到文件的私有页。

23. **RSfd — 常驻文件映射内存大小（KiB）**
RES 的子集，指支撑程序镜像与共享库的隐式共享页，以及显式私有/共享文件映射。

24. **RSlk — 常驻锁定内存大小（KiB）**
RES 的子集，指**无法被换出**的内存。

25. **RSsh — 常驻共享内存大小（KiB）**
RES 的子集，指显式共享的匿名 shm*/mmap 页。

26. **RUID — 真实用户 ID**

27. **RUSER — 真实用户名**

28. **S — 进程状态**
任务状态可取以下值：
- D = 不可中断睡眠
- R = 运行中
- S = 睡眠中
- T = 被作业控制信号停止
- t = 被调试器跟踪时停止
- Z = 僵死
显示为 R（运行中）的任务更准确理解为**就绪可运行**，其 `task_struct` 位于 Linux 运行队列。

29. **SHR — 共享内存大小（KiB）**
RES 的子集，指可能被其他进程使用的内存。
包括共享匿名页、共享文件映射页，以及映射为程序和共享库的私有文件页。
详见「概述：Linux 内存类型」。

30. **SID — 会话 ID**
会话是一组进程组的集合，通常由登录 Shell 创建。
新进程会加入创建者所在会话。惯例上等于会话首进程（通常是登录 Shell）的 PID。

31. **SUID — 保存用户 ID**

32. **SUPGIDS — 附加组 ID**
登录时建立或从父进程继承的附加组 ID，以逗号分隔。
该字段为可变宽度。

33. **SUPGRPS — 附加组名**
附加组名称，以逗号分隔。
该字段为可变宽度。

34. **SUSER — 保存用户名**

35. **SWAP — 交换分区大小（KiB）**
当物理内存超用时，任务地址空间中被写入交换分区的原常驻内存部分。
详见「概述：Linux 内存类型」。

36. **TGID — 线程组 ID**
任务所属线程组的 ID，即线程组组长的 PID。
在内核中代表共享 `mm_struct` 的一组任务。

37. **TIME — CPU 时间**
任务启动以来占用的总 CPU 时间。
累计模式开启时，会包含进程及其已退出子进程的 CPU 时间。可通过 `S` 切换累计模式。

38. **TIME+ — CPU 时间（精确到百分之一秒）**
与 TIME 相同，但精度更高，显示到百分之一秒。

39. **TPGID — TTY 进程组 ID**
关联终端的前台进程组 ID，未关联终端则为 -1。

40. **TTY — 控制终端**
进程的控制终端名称，未关联终端则显示 `?`。

41. **UID — 用户 ID**
任务所有者的有效用户 ID。

42. **USED — 已使用内存（KiB）**
等于常驻内存（RES） + 交换分区内存（SWAP）。
详见「概述：Linux 内存类型」。

43. **USER — 用户名**
任务所有者的有效用户名。

44. **VIRT — 虚拟内存大小（KiB）**
任务使用的虚拟内存总量，包括：所有代码、数据、共享库、已换出页、已映射但未使用页。
详见「概述：Linux 内存类型」。

45. **WCHAN — 睡眠所在内核函数**
显示任务当前睡眠的内核函数名，运行状态显示 `-`。

46. **nDRT — 脏页数量**
自上次写入辅助存储以来被修改的页面数。脏页必须回写后，对应物理内存才能重新分配。

47. **nMaj — 主要缺页异常次数**
任务发生的主要缺页次数。
主要缺页：需要访问磁盘等辅助存储才能将页面载入。

48. **nMin — 次要缺页异常次数**
任务发生的次要缺页次数。
次要缺页：无需访问磁盘即可将页面载入。

49. **nTH — 线程数**
进程关联的线程总数。

50. **nsIPC — IPC 命名空间**
用于隔离 IPC 资源的命名空间索引节点号。

51. **nsMNT — 挂载命名空间**
用于隔离文件系统挂载点的命名空间索引节点号。

52. **nsNET — 网络命名空间**
用于隔离网络设备、IP 地址、路由、端口等资源的命名空间索引节点号。

53. **nsPID — PID 命名空间**
用于隔离进程号的命名空间索引节点号，每个命名空间可拥有独立的 init/systemd（PID 1）。

54. **nsUSER — 用户命名空间**
用于隔离用户/组 ID 的命名空间索引节点号。
进程可在外部为普通用户，在命名空间内为 UID 0（root 权限）。

55. **nsUTS — UTS 命名空间**
用于隔离主机名与 NIS 域名的命名空间索引节点号。
UTS = UNIX Time-sharing System。

56. **vMj — 主要缺页异常增量**
自上次刷新以来新增的主要缺页次数。

57. **vMn — 次要缺页异常增量**
自上次刷新以来新增的次要缺页次数。