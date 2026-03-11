> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.baeldung.com](https://www.baeldung.com/linux/proc-meminfo#introduction)

> Learn about the definition of each memory attribute field in the /proc/meminfo file.

1. Introduction[](#introduction)
--------------------------------

The _/proc/meminfo_ file inside the [_/proc_](https://www.baeldung.com/linux/cli-hardware-info#the-proc-pseudo-filesystem) pseudo-filesystem provides a usage report about memory on the system. When we want to find out statistics like used and available memory, swap space, or cache and buffers, we can analyze this file’s contents. However, there are tons more data on top of the basic information.

In this article, we’re going to examine every data field in the _/proc/meminfo_ file.

2. Data Fields in _/proc/meminfo_[](#data-fields-in-procmeminfo)
----------------------------------------------------------------

To see what a file contains, we can use the [_cat_](https://www.baeldung.com/linux/cat-writing-file#the-cat-command) command:

```
$ cat /proc/meminfo
MemTotal:         994548 kB
MemFree:           65228 kB
MemAvailable:     263724 kB
Buffers:           21396 kB
Cached:           304440 kB
SwapCached:        25260 kB
Active:           267424 kB
Inactive:         503720 kB
Active(anon):     110956 kB
Inactive(anon):   351176 kB
...

```

As we can see above, the _/proc/meminfo_ file contains memory statistics in kilobytes. Now, let’s take a look at each of them by category.

3. General Memory[](#general-memory)
------------------------------------

Usually, we only need basic information about memory, such as how much RAM our system has or how much is available at the current moment:

```
$ cat /proc/meminfo | grep "Mem"
MemTotal:         994328 kB
MemFree:           66428 kB
MemAvailable:     207192 kB


```

Basically, we get a simple memory snapshot:

*   _MemTotal_: total usable RAM
*   _MemFree_: free RAM, the memory which is not used for anything at all
*   _MemAvailable_: available RAM, the amount of memory available for allocation to any process

However, these basic values are available in other tools as well.

4. Buffers and Cache[](#buffers-and-cache)
------------------------------------------

Sometimes, we may want to check buffer and cache sizes. Specifically, buffers are temporary storage components for process input and output. They don’t increase the processing speed. On the other hand, cache stores some data to serve future requests faster. As a result, the cache increases the processing speed.

Of course, we can access the memory size information for both:

```
$ cat /proc/meminfo | grep -e "Buffers" -we "Cached" 
Buffers:           12820 kB
Cached:           254592 kB

```

Let’s define these two attributes:

*   _Buffers_: temporary storage element in memory, which doesn’t generally exceed 20 MB
*   _Cached_: page cache size (cache for files read from the disk), which also includes _tmpfs_ and _shmem_ but excludes _SwapCached_

Indeed, distinguishing different caching levels enables better memory management in terms of hierarchy.

5. Swap Space[](#swap-space)
----------------------------

Furthermore, we can learn all about the [swap space](https://www.baeldung.com/linux/swap-space) on the system:

```
$ cat /proc/meminfo | grep "Swap" 
SwapCached:        13936 kB
SwapTotal:        945416 kB
SwapFree:         851064 kB


```

Basically, swap space is a backup space on the disk for RAM. When the physical memory is full, the system uses the swap space:

*   _SwapCached_: recently used swap memory, which increases the speed of I/O
*   _SwapTotal_: the total amount of swap space available in the system
*   _SwapFree_: unused swap space, the memory that has been transferred from RAM to the disk temporarily

Importantly, the _/proc/swap_ file lists the different available swap areas.

6. Memory Activeness[](#memory-activeness)
------------------------------------------

Moreover, the _/proc/meminfo_ file also contains data about memory dynamics:

```
$ cat /proc/meminfo | grep -e "Active" -e "Inactive" 
Active:           194308 kB
Inactive:         553172 kB
Active(anon):      59024 kB
Inactive(anon):   437264 kB
Active(file):     135284 kB
Inactive(file):   115908 kB


```

In this case, there are two categories: _file_ or non-file (_anon_). Here, we are interested in the general result:

*   _Active_: memory that has been used more recently, not very suitable to reclaim for new applications
*   _Inactive_: memory that hasn’t been used recently, more suitable to reclaim for new applications

Knowing the breakdown of active and inactive memory enables better handling of memory-intensive applications such as servers.

7. Writeback Into the Disk[](#writeback-into-the-disk)
------------------------------------------------------

Moreover, we’re able to get information about the amount of memory that’s being or is about to be written back:

```
$ cat /proc/meminfo | grep -e "Dirty" -e "Writeback" 
Dirty:                 0 kB
Writeback:             0 kB
WritebackTmp:          0 kB


```

Following is a summary of the fields:

*   _Dirty_: memory that currently waits to be written back to the disk
*   _Writeback_: memory that is being written back at the moment
*   _WritebackTmp_: temporary buffer for writebacks used by the [_FUSE_](https://www.kernel.org/doc/html/next/filesystems/fuse.html) module

Of course, operations are much slower when they involve secondary memory. Because of this, monitoring how much data is pending enables an administrator to properly balance loads.

8. Mapped Memory[](#mapped-memory)
----------------------------------

In addition, we can look at how much memory is mapped. Essentially, memory-mapped files are part of the virtual memory system, which contains a direct byte-level correlation with other resources. Memory mapping increases the maximum number of I/O operations, especially on large files:

```
$ cat /proc/meminfo | grep -w -e "AnonPages" -e "Mapped" -e "DirectMap4k" -e "DirectMap2M"
AnonPages:        470224 kB
Mapped:           144264 kB
DirectMap4k:      149440 kB
DirectMap2M:      899072 kB


```

To be sure, these mappings provide the following information:

*   _AnonPages_: _anon_ (non-file) pages mapped into the page tables
*   _Mapped_: files that have been mapped into memory with [_mmap_](https://man7.org/linux/man-pages/man2/mmap.2.html)
*   _DirectMap4k_: the total amount of memory mapped by the kernel in 4 kB pages
*   _DirectMap2M_: the total amount of memory mapped by the kernel in 2 MB pages

While memory mapping has its benefits, it also blocks parts of the main memory from being used for actual data.

Moreover, we can learn about the [shared memory](https://www.baeldung.com/cs/inter-process-communication#1-shared-memory) in the system. Shared memory is an additional memory location for processes with separate address spaces. Such processes can share a portion of memory:

```
$ cat /proc/meminfo | grep "Shmem"
Shmem:             16520 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB


```

There are several ways to represent the shared memory:

*   _Shmem_: the amount used by shared memory and the [_tmpfs_](https://man7.org/linux/man-pages/man5/tmpfs.5.html) filesystem
*   _ShmemHugePages_: the amount used by shared memory and the _tmpfs_ filesystem with huge pages
*   _ShmemPmdMapped_: userspace-mapped shared memory with huge pages

While convenient, shared memory presents [challenges](https://www.baeldung.com/cs/concurrency-vs-parallelism#1-potential-pitfalls-in-concurrency-and-parallelism) that may make it problematic.

10. Kernel Memory[](#10-kernel-memory)
--------------------------------------

The Linux kernel has lots of inner low-level operations to take care of memory. Fortunately, the _/__proc/meminfo_ file provides several kernel-level pieces of information as well:

```
$ cat /proc/meminfo | grep -ie "reclaim" -e "slab" -e "kernel"
KReclaimable:      35008 kB
Slab:              88752 kB
SReclaimable:      35008 kB
SUnreclaim:        53744 kB
KernelStack:        5988 kB


```

In fact, the kernel uses memory in different ways:

*   _KReclaimable_: kernel allocated memory, reclaimable under memory pressure (includes _SReclaimable_)
*   _Slab_: kernel-level data structures cache, allocation of contiguous pages for caches by the _slab_ allocator
*   _SReclaimable_: reclaimable parts of _Slab_, e.g., caches
*   _SUnreclaim_: unreclaimable parts of _Slab_
*   _KernelStack_: memory for kernel stacks of entire tasks

For example, the kernel memory holds all open [file descriptors](https://www.baeldung.com/linux/limit-file-descriptors). Running out of kernel memory can cause the [forceful termination of processes](https://www.baeldung.com/linux/memory-overcommitment-oom-killer).

11. Allocation Availability[](#11-allocation-availability)
----------------------------------------------------------

If we want to learn the amount of memory eligible for allocation or already allocated on the system, we can take a look at two data fields:

```
$ cat /proc/meminfo | grep -ie "commit"
CommitLimit:     1442580 kB
Committed_AS:    3035924 kB


```

Markedly, these data points demonstrate the allocation ability of the system:

*   _CommitLimit_: amount currently available for allocation on the system
*   _Committed_AS_: amount already allocated on the system

Note the difference between _Committed_AS_ and the _Inactive_ field we already saw. In fact, there’s a formula for calculating the current allocatable amount of memory.

12. Virtual Memory[](#12-virtual-memory)
----------------------------------------

Besides, _/proc/meminfo_ contains some data about the [virtual memory](https://www.baeldung.com/cs/virtual-memory) system:

```
$ cat /proc/meminfo | grep -e "PageTables" -e "Vmalloc"
PageTables:        11520 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       34780 kB
VmallocChunk:          0 kB


```

Using the output above, let’s define the meaning of each field:

*   _PageTables_: the amount of memory consumed by page tables used by the virtual memory system
*   _VmallocTotal_: total size of [_vmalloc_](https://www.kernel.org/doc/htmldocs/kernel-api/API-vmalloc.html) memory space to allocate virtually contiguous memory
*   _VmallocUsed_: the size of the used _vmalloc_ memory space
*   _VmallocChunk_: largest free contiguous block of _vmalloc_ memory

Critically, these fields differ from the information about swap, as there is a difference between [swap and virtual memory](https://www.baeldung.com/cs/virtual-memory-vs-swap-space).

13. Huge Pages[](#13-huge-pages)
--------------------------------

Since the Linux kernel supports huge (larger than the default) pages, we can see data about them as well:

```
$ cat /proc/meminfo | grep -ie "huge" -e "filepmd" | grep -v "Shmem"
AnonHugePages:         0 kB
FileHugePages:         0 kB
FilePmdMapped:         0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:               0 kB


```

Obviously, we get lots of information to look at:

*   _AnonHugePages_: _anon_ (non-file) huge pages mapped into the page tables
*   _FileHugePages_: memory consumed by page cache allocated with huge pages
*   _FilePmdMapped_: mapped page cache in the userspace allocated with huge pages
*   _HugePages_Total_: total size of the huge pages pool
*   _HugePages_Free_: amount of unallocated huge pages
*   _HugePages_Rsvd_: number of reserved huge pages for allocation from the pool, which guarantees the allocation for processes when undesired behavior occurs
*   _HugePages_Surp_: number of surplus huge pages above a specific base value in _/proc/sys/vm/nr_hugepages_
*   _Hugepagesize_: the default size of huge page_s_
*   _Hugetlb_: the total amount of memory allocated for huge pages of all sizes

Generally, systems that process data in larger chunks can benefit greatly from huge pages. In such cases, controlling and monitoring the current huge page settings is crucial.

14. Others[](#14-others)
------------------------

Finally, we can also get some miscellaneous information along the rest of the categories:

```
$ cat /proc/meminfo | grep -e "Unevictable" -e "Mlocked" -e "NFS" -e "Bounce" -e "Percpu" -e "Hardware"
Unevictable:           0 kB
Mlocked:               0 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
Percpu:             1312 kB
HardwareCorrupted:     0 kB


```

Each field in this set refers to a distinct attribute of memory:

*   _Unevictable_: unreclaimable memory consumed by userspace like [_mlock_](https://man7.org/linux/man-pages/man2/mlock.2.html)-locke, [_ramfs_](https://www.unix.com/man-page/plan9/4/ramfs/) backing, and anonymous [_memfd_](https://man7.org/linux/man-pages/man2/memfd_create.2.html) pages
*   _Mlocked_: amount of memory locked with _mlock_
*   _NFS_Unstable_: [Network File System](https://www.baeldung.com/linux/mount-unmount-filesystems#4-nfs) pages that have been written to the disk but not yet committed to stable storage, always zero
*   _Bounce_: amount of memory for bounce buffers, which are low-level memory areas that enable devices to copy and write data
*   _Percpu_: memory used for the [_percpu_](https://docs.kernel.org/locking/percpu-rw-semaphore.html) interface allocations
*   _HardwareCorrupted_: memory that the kernel spots as corrupted

Of these, _HardwareCorrupted_ is usually very helpful, as it points out potential issues with memory, affecting all other discussed fields.

15. Conclusion[](#15-conclusion)
--------------------------------

In this article, we learned about the structure of data inside _/proc/meminfo_. In fact, we saw that this file contains most of the information we might need about memory. We then inspected every piece of data by splitting them into categories.



---



# /proc/meminfo （Baeldung 原文）
## 1. 简介
`/proc` 伪文件系统下的 `/proc/meminfo` 文件提供系统内存使用报告。我们可以通过分析该文件内容，查看已用/可用内存、交换空间、缓存和缓冲区等统计信息，而其中还包含远多于基础信息的大量数据。

本文将详细解释 `/proc/meminfo` 中的**每一个字段**。

---

## 2. /proc/meminfo 中的数据字段
使用 `cat` 命令可查看文件内容：
```
$ cat /proc/meminfo
MemTotal:         994548 kB
MemFree:           65228 kB
MemAvailable:     263724 kB
Buffers:           21396 kB
Cached:           304440 kB
SwapCached:        25260 kB
Active:           267424 kB
Inactive:         503720 kB
Active(anon):     110956 kB
Inactive(anon):   351176 kB
...
```
如上所示，`/proc/meminfo` 以**千字节（kB）**为单位展示内存统计数据。下面按类别逐一说明。

---

## 3. 常规内存
通常我们只需要内存基础信息，如系统总物理内存、当前可用内存：
```
$ cat /proc/meminfo | grep "Mem"
MemTotal:         994328 kB
MemFree:           66428 kB
MemAvailable:     207192 kB
```

- **MemTotal**：系统可用物理内存总量
- **MemFree**：完全未被任何用途占用的空闲内存
- **MemAvailable**：可直接分配给新进程的可用内存（更贴近实际可用）

这些基础值在其他工具中也可获取。

---

## 4. 缓冲区与缓存
缓冲区（Buffers）是进程 I/O 的临时存储，不提升处理速度；
缓存（Cached）用于缓存数据以加速后续请求，能提升速度。

```
$ cat /proc/meminfo | grep -e "Buffers" -we "Cached" 
Buffers:           12820 kB
Cached:           254592 kB
```

- **Buffers**：内存中的临时存储，通常不超过 20MB
- **Cached**：页缓存大小（磁盘文件读取缓存），包含 tmpfs 和 shmem，但**不包含** SwapCached

---

## 5. 交换空间（Swap）
Swap 是物理内存占满时，磁盘上用于暂存内存数据的备用空间。

```
$ cat /proc/meminfo | grep "Swap" 
SwapCached:        13936 kB
SwapTotal:        945416 kB
SwapFree:         851064 kB
```

- **SwapCached**：最近使用过的交换分区内存，可加速 I/O
- **SwapTotal**：系统交换分区总大小
- **SwapFree**：空闲交换分区大小（从内存暂存到磁盘但未被回收的数据）

`/proc/swap` 文件会列出系统中所有可用的交换分区。

---

## 6. 内存活跃状态
按使用频率与是否可回收划分，分为文件页（file）与匿名页（anon）两类：

```
$ cat /proc/meminfo | grep -e "Active" -e "Inactive" 
Active:           194308 kB
Inactive:         553172 kB
Active(anon):      59024 kB
Inactive(anon):   437264 kB
Active(file):     135284 kB
Inactive(file):   115908 kB
```

- **Active**：最近使用的内存，不适合回收用于新应用
- **Inactive**：近期未使用的内存，可优先回收

---

## 7. 磁盘回写（Writeback）
表示正在/即将写回磁盘的内存量：

```
$ cat /proc/meminfo | grep -e "Dirty" -e "Writeback" 
Dirty:                 0 kB
Writeback:             0 kB
WritebackTmp:          0 kB
```

- **Dirty**：等待写回磁盘的脏页
- **Writeback**：正在写回磁盘的内存
- **WritebackTmp**：FUSE 模块使用的临时回写缓冲区

---

## 8. 映射内存
内存映射文件属于虚拟内存系统，通过 `mmap` 实现资源与内存的字节级关联。

```
$ cat /proc/meminfo | grep -w -e "AnonPages" -e "Mapped" -e "DirectMap4k" -e "DirectMap2M"
AnonPages:        470224 kB
Mapped:           144264 kB
DirectMap4k:      149440 kB
DirectMap2M:      899072 kB
```

- **AnonPages**：映射到页表的匿名（非文件）页
- **Mapped**：通过 `mmap` 映射到内存的文件
- **DirectMap4k**：内核以 4KB 页映射的内存总量
- **DirectMap2M**：内核以 2MB 页映射的内存总量

---

## 9. 共享内存
共享内存是独立地址空间进程间共享的内存区域：

```
$ cat /proc/meminfo | grep "Shmem"
Shmem:             16520 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB
```

- **Shmem**：共享内存与 tmpfs 文件系统占用量
- **ShmemHugePages**：使用巨页的共享内存与 tmpfs 大小
- **ShmemPmdMapped**：用户态映射的巨页共享内存

---

## 10. 内核内存
Linux 内核通过多种机制管理底层内存：

```
$ cat /proc/meminfo | grep -ie "reclaim" -e "slab" -e "kernel"
KReclaimable:      35008 kB
Slab:              88752 kB
SReclaimable:      35008 kB
SUnreclaim:        53744 kB
KernelStack:        5988 kB
```

- **KReclaimable**：内核可回收内存（包含 SReclaimable）
- **Slab**：内核数据结构缓存，由 slab 分配器管理
- **SReclaimable**：Slab 中可回收部分（如各类缓存）
- **SUnreclaim**：Slab 中不可回收部分
- **KernelStack**：所有进程/线程的内核栈占用内存

---

## 11. 内存分配可用性
表示系统已分配与可分配的虚拟内存额度：

```
$ cat /proc/meminfo | grep -ie "commit"
CommitLimit:     1442580 kB
Committed_AS:    3035924 kB
```

- **CommitLimit**：系统当前可分配的虚拟内存上限
- **Committed_AS**：系统已分配的虚拟内存总量

---

## 12. 虚拟内存
```
$ cat /proc/meminfo | grep -e "PageTables" -e "Vmalloc"
PageTables:        11520 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       34780 kB
VmallocChunk:          0 kB
```

- **PageTables**：虚拟内存系统页表占用内存
- **VmallocTotal**：vmalloc 虚拟地址空间总大小
- **VmallocUsed**：已使用的 vmalloc 空间
- **VmallocChunk**：最大的连续空闲 vmalloc 块

---

## 13. 巨页（Huge Pages）
Linux 支持大于默认大小的巨页，适用于大流量、高性能场景：

```
AnonHugePages:         0 kB
FileHugePages:         0 kB
FilePmdMapped:         0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:               0 kB
```

- **AnonHugePages**：匿名巨页
- **FileHugePages**：使用巨页的页缓存
- **HugePages_Total**：巨页池总数量
- **HugePages_Free**：未分配的巨页数量
- **HugePages_Rsvd**：预留巨页数量
- **HugePages_Surp**：超出基线的富余巨页数量
- **Hugepagesize**：单个巨页大小
- **Hugetlb**：所有巨页占用的总内存

---

## 14. 其他字段
```
Unevictable:           0 kB
Mlocked:               0 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
Percpu:             1312 kB
HardwareCorrupted:     0 kB
```

- **Unevictable**：不可回收内存（mlock、ramfs、memfd 等）
- **Mlocked**：通过 mlock 锁定的内存
- **NFS_Unstable**：NFS 已写但未提交到稳定存储的页（通常为 0）
- **Bounce**：底层设备使用的反弹缓冲区
- **Percpu**：per-CPU 接口分配的内存
- **HardwareCorrupted**：内核检测到的硬件损坏内存页

---

## 15. 总结
`/proc/meminfo` 包含了系统内存的**几乎所有关键信息**，本文按类别完整解释了所有字段，是系统调优、性能排查与内存分析的核心参考。