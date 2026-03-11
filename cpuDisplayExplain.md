```markdown
   2b. TASK and CPU States
       This  portion  consists  of  a minimum of two lines.  In an SMP environment, additional lines can reflect
       individual CPU state percentages.

       Line 1 shows total tasks or threads, depending on the state of the Threads-mode toggle.   That  total  is
       further classified as:
           running; sleeping; stopped; zombie

       Line 2 shows CPU state percentages based on the interval since the last refresh.

       As  a  default,  percentages  for  these individual categories are displayed.  Where two labels are shown
       below, those for more recent kernel versions are shown first.
           us, user    : time running un-niced user processes
           sy, system  : time running kernel processes
           ni, nice    : time running niced user processes
           id, idle    : time spent in the kernel idle handler
           wa, IO-wait : time waiting for I/O completion
           hi : time spent servicing hardware interrupts
           si : time spent servicing software interrupts
           st : time stolen from this vm by the hypervisor
```

AI翻译：

## 2b. 任务与CPU状态

这一部分至少包含两行。在**对称多处理器（SMP）**环境中，还会出现额外行，用于展示**每个CPU核心**的状态占比。

**第一行**显示总任务数或线程数，具体取决于线程模式开关的状态。
该总数会进一步划分为：
- 运行中（running）
- 睡眠中（sleeping）
- 已停止（stopped）
- 僵死（zombie）

**第二行**显示自上次刷新以来，各CPU状态所占的时间百分比。

默认情况下，会显示以下各个类别的百分比。
下方若出现两个标签，**较新内核版本使用的标签排在前面**：

- **us, user**：运行**未调整优先级（un-niced）**的用户进程时间
- **sy, system**：运行内核进程的时间
- **ni, nice**：运行**已调整优先级（niced）**的用户进程时间
- **id, idle**：内核空闲处理程序的时间
- **wa, IO-wait**：等待I/O完成的时间
- **hi**：处理硬件中断的时间
- **si**：处理软件中断的时间
- **st**：虚拟化管理程序（hypervisor）从当前虚拟机**窃取**的时间

