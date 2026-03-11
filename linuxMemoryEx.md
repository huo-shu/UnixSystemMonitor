> ```markdown
> Linux Memory Types
>        For our purposes there are three types of memory, and one is  optional.   First  is  physical  memory,  a
>        limited  resource where code and data must reside when executed or referenced.  Next is the optional swap
>        file, where modified (dirty) memory can be saved and later retrieved if too  many  demands  are  made  on
>        physical memory.  Lastly we have virtual memory, a nearly unlimited resource serving the following goals:
> 
>           1. abstraction, free from physical memory addresses/limits
>           2. isolation, every process in a separate address space
>           3. sharing, a single mapping can serve multiple needs
>           4. flexibility, assign a virtual address to a file
> 
>        Regardless  of  which of these forms memory may take, all are managed as pages (typically 4096 bytes) but
>        expressed by default in top as KiB (kibibyte).  The memory discussed under topic `2c. MEMORY Usage' deals
>        with physical memory and the swap file for the system as a whole.   The  memory  reviewed  in  topic  `3.
>        FIELDS / Columns Display' embraces all three memory types, but for individual processes.
> 
>        For  each  such process, every memory page is restricted to a single quadrant from the table below.  Both
>        physical memory and virtual memory can include any of the four, while the  swap  file  only  includes  #1
>        through #3.  The memory in quadrant #4, when modified, acts as its own dedicated swap file.
> 
>                                      Private | Shared
>                                  1           |          2
>             Anonymous  . stack               |
>                        . malloc()            |
>                        . brk()/sbrk()        | . POSIX shm*
>                        . mmap(PRIVATE, ANON) | . mmap(SHARED, ANON)
>                       -----------------------+----------------------
>                        . mmap(PRIVATE, fd)   | . mmap(SHARED, fd)
>           File-backed  . pgms/shared libs    |
>                                  3           |          4
> 
>        The  following  may  help  in  interpreting process level memory values displayed as scalable columns and
>        discussed under topic `3a. DESCRIPTIONS of Fields'.
> 
>           %MEM - simply RES divided by total physical memory
>           CODE - the `pgms' portion of quadrant 3
>           DATA - the entire quadrant 1 portion of VIRT plus all
>                  explicit mmap file-backed pages of quadrant 3
>           RES  - anything occupying physical memory which, beginning with
>                  Linux-4.5, is the sum of the following three fields:
>                  RSan - quadrant 1 pages, which include any
>                         former quadrant 3 pages if modified
>                  RSfd - quadrant 3 and quadrant 4 pages
>                  RSsh - quadrant 2 pages
>           RSlk - subset of RES which cannot be swapped out (any quadrant)
>           SHR  - subset of RES (excludes 1, includes all 2 & 4, some 3)
>           SWAP - potentially any quadrant except 4
>           USED - simply the sum of RES and SWAP
>           VIRT - everything in-use and/or reserved (all quadrants)
> 
>        Note: Even though program images and shared libraries are considered private to a process, they  will  be
>        accounted for as shared (SHR) by the kernel.
> ```

---

AI翻译:

# Linux 内存类型
出于本文的讲解目的，内存分为三种类型，其中一种为可选类型。
第一种是**物理内存**，这是一种有限资源，代码与数据在执行或被访问时必须驻留其中。
第二种是**交换分区（swap）**，属于可选组件。当物理内存压力过大时，被修改过的（脏）内存可以保存到交换分区，后续需要时再从中取回。
最后一种是**虚拟内存**，它是一种近乎无限的资源，主要实现以下目标：

1. **抽象性**：脱离物理内存地址与容量限制
2. **隔离性**：每个进程拥有独立的地址空间
3. **共享性**：同一份内存映射可被多方使用
4. **灵活性**：可将虚拟地址映射到文件

无论内存以哪种形式存在，均以**页（page）** 为单位进行管理（通常为 4096 字节），但在 top 命令中默认以 **KiB（千字节）** 显示。
主题 **2c. 内存使用情况** 中讨论的内存，是针对整个系统的**物理内存与交换分区**。
主题 **3. 字段/显示列** 中介绍的内存，则涵盖全部三种内存类型，但视角是**单个进程**。

对每个进程而言，每一个内存页都严格归属于下表中的**唯一象限**。
物理内存与虚拟内存可以包含全部四个象限，而交换分区仅包含第 1～3 象限。
第 4 象限的内存在被修改时，会以自身作为专用交换空间。

> ```
>                         私有（Private） | 共享（Shared）
>                     1                 |                 2
>        匿名内存   . 栈（stack）        |
>                   . malloc() 分配内存  |
>                   . brk()/sbrk()      | . POSIX 共享内存（shm*）
>                   . mmap(私有, 匿名)   | . mmap(共享, 匿名)
>                  ----------------------+----------------------
>                   . mmap(私有, 文件)   | . mmap(共享, 文件)
>        文件映射   . 程序/共享库        |
>                     3                 |                 4
> ```

下面内容有助于理解以可缩放列形式展示、并在主题 **3a. 字段说明** 中讲解的**进程级内存指标**：

- **%MEM**：进程常驻内存（RES）除以系统总物理内存
- **CODE**：第 3 象限中“程序代码”部分
- **DATA**：虚拟内存（VIRT）中**整个第 1 象限**，加上第 3 象限中所有显式通过 mmap 映射的文件页
- **RES**：所有占用物理内存的页面。自 Linux-4.5 起，由以下三项之和构成：
  - RSan：第 1 象限页面（若第 3 象限页面被修改，也会归入此类）
  - RSfd：第 3、4 象限页面
  - RSsh：第 2 象限页面
- **RSlk**：RES 的子集，指**无法被换出**的内存（可来自任意象限）
- **SHR**：RES 的子集（不含第 1 象限，包含全部第 2、4 象限及部分第 3 象限）
- **SWAP**：可能来自除第 4 象限外的任意象限
- **USED**：RES 与 SWAP 之和
- **VIRT**：进程所有已使用/已预留的虚拟空间（全部象限）

**注意**：
尽管程序镜像与共享库对进程而言是私有的，但内核会将其统计为**共享内存（SHR）**。

