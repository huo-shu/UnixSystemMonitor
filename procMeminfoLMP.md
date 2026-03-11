> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [www.man7.org](https://www.man7.org/linux/man-pages/man5/proc_meminfo.5.html)

<table><tbody><tr><td><p data-imt-p="1"><a href="../../../index.html">man7.org</a> &gt; Linux &gt; <a href="../index.html">man-pages</a></p></td><td><p><a href="http://man7.org/training/" data-imt-p="1">Linux/UNIX system programming training</a></p></td></tr></tbody></table>

proc_meminfo(5) — Linux manual page
===================================

<table><tbody><tr><td><p data-imt-p="1"><a href="#NAME">NAME</a> | <a href="#DESCRIPTION">DESCRIPTION</a> | <a href="#SEE_ALSO">SEE&nbsp;ALSO</a> | <a href="#COLOPHON">COLOPHON</a></p></td></tr><tr><td><form method="get" action="https://www.google.com/search"><fieldset><input type="text"> <input type="hidden"> <input type="submit"></fieldset></form></td><td></td></tr></tbody></table>

```
proc_meminfo(5)            File Formats Manual            proc_meminfo(5)


```

[](#NAME)NAME         [top](#top_of_page)
-----------------------------------------

```
       /proc/meminfo - memory usage


```

[](#DESCRIPTION)DESCRIPTION         [top](#top_of_page)
-------------------------------------------------------

```
       /proc/meminfo
              This file reports statistics about memory usage on the
              system.  It is used by free(1) to report the amount of free
              and used memory (both physical and swap) on the system as
              well as the shared memory and buffers used by the kernel.
              Each line of the file consists of a parameter name,
              followed by a colon, the value of the parameter, and an
              option unit of measurement (e.g., "kB").  The list below
              describes the parameter names and the format specifier
              required to read the field value.  Except as noted below,
              all of the fields have been present since at least Linux
              2.6.0.  Some fields are displayed only if the kernel was
              configured with various options; those dependencies are
              noted in the list.

              MemTotal %lu
                     Total usable RAM (i.e., physical RAM minus a few
                     reserved bits and the kernel binary code).

              MemFree %lu
                     The sum of LowFree+HighFree.

              MemAvailable %lu (since Linux 3.14)
                     An estimate of how much memory is available for
                     starting new applications, without swapping.

              Buffers %lu
                     Relatively temporary storage for raw disk blocks
                     that shouldn't get tremendously large (20 MB or so).

              Cached %lu
                     In-memory cache for files read from the disk (the
                     page cache).  Doesn't include SwapCached.

              SwapCached %lu
                     Memory that once was swapped out, is swapped back in
                     but still also is in the swap file.  (If memory
                     pressure is high, these pages don't need to be
                     swapped out again because they are already in the
                     swap file.  This saves I/O.)

              Active %lu
                     Memory that has been used more recently and usually
                     not reclaimed unless absolutely necessary.

              Inactive %lu
                     Memory which has been less recently used.  It is
                     more eligible to be reclaimed for other purposes.

              Active(anon) %lu (since Linux 2.6.28)
                     [To be documented.]

              Inactive(anon) %lu (since Linux 2.6.28)
                     [To be documented.]

              Active(file) %lu (since Linux 2.6.28)
                     [To be documented.]

              Inactive(file) %lu (since Linux 2.6.28)
                     [To be documented.]

              Unevictable %lu (since Linux 2.6.28)
                     (From Linux 2.6.28 to Linux 2.6.30,
                     CONFIG_UNEVICTABLE_LRU was required.)  [To be
                     documented.]

              Mlocked %lu (since Linux 2.6.28)
                     (From Linux 2.6.28 to Linux 2.6.30,
                     CONFIG_UNEVICTABLE_LRU was required.)  [To be
                     documented.]

              HighTotal %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Total amount of highmem.  Highmem is all
                     memory above ~860 MB of physical memory.  Highmem
                     areas are for use by user-space programs, or for the
                     page cache.  The kernel must use tricks to access
                     this memory, making it slower to access than lowmem.

              HighFree %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Amount of free highmem.

              LowTotal %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Total amount of lowmem.  Lowmem is
                     memory which can be used for everything that highmem
                     can be used for, but it is also available for the
                     kernel's use for its own data structures.  Among
                     many other things, it is where everything from Slab
                     is allocated.  Bad things happen when you're out of
                     lowmem.

              LowFree %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Amount of free lowmem.

              MmapCopy %lu (since Linux 2.6.29)
                     (CONFIG_MMU is required.)  [To be documented.]

              SwapTotal %lu
                     Total amount of swap space available.

              SwapFree %lu
                     Amount of swap space that is currently unused.

              Dirty %lu
                     Memory which is waiting to get written back to the
                     disk.

              Writeback %lu
                     Memory which is actively being written back to the
                     disk.

              AnonPages %lu (since Linux 2.6.18)
                     Non-file backed pages mapped into user-space page
                     tables.

              Mapped %lu
                     Files which have been mapped into memory (with
                     mmap(2)), such as libraries.

              Shmem %lu (since Linux 2.6.32)
                     Amount of memory consumed in tmpfs(5) filesystems,
                     System V, and POSIX shared memory, as well as shared
                     anonymous mappings (MAP_SHARED|MAP_ANONYMOUS).

              KReclaimable %lu (since Linux 4.20)
                     Kernel allocations that the kernel will attempt to
                     reclaim under memory pressure.  Includes
                     SReclaimable (below), and other direct allocations
                     with a shrinker.

              Slab %lu
                     In-kernel data structures cache.  (See slabinfo(5).)

              SReclaimable %lu (since Linux 2.6.19)
                     Part of Slab, that might be reclaimed, such as
                     caches.

              SUnreclaim %lu (since Linux 2.6.19)
                     Part of Slab, that cannot be reclaimed on memory
                     pressure.

              KernelStack %lu (since Linux 2.6.32)
                     Amount of memory allocated to kernel stacks.

              PageTables %lu (since Linux 2.6.18)
                     Amount of memory dedicated to the lowest level of
                     page tables.

              Quicklists %lu (since Linux 2.6.27)
                     (CONFIG_QUICKLIST is required.)  [To be documented.]

              NFS_Unstable %lu (since Linux 2.6.18)
                     NFS pages sent to the server, but not yet committed
                     to stable storage.

              Bounce %lu (since Linux 2.6.18)
                     Memory used for block device "bounce buffers".

              WritebackTmp %lu (since Linux 2.6.26)
                     Memory used by FUSE for temporary writeback buffers.

              CommitLimit %lu (since Linux 2.6.10)
                     This is the total amount of memory currently
                     available to be allocated on the system, expressed
                     in kilobytes.  This limit is adhered to only if
                     strict overcommit accounting is enabled (mode 2 in
                     /proc/sys/vm/overcommit_memory).  The limit is
                     calculated according to the formula described under
                     /proc/sys/vm/overcommit_memory.  For further
                     details, see the kernel source file
                     Documentation/vm/overcommit-accounting.rst.

              Committed_AS %lu
                     The amount of memory presently allocated on the
                     system.  The committed memory is a sum of all of the
                     memory which has been allocated by processes, even
                     if it has not been "used" by them as of yet.  A
                     process which allocates 1 GB of memory (using
                     malloc(3) or similar), but touches only 300 MB of
                     that memory will show up as using only 300 MB of
                     memory even if it has the address space allocated
                     for the entire 1 GB.

                     This 1 GB is memory which has been "committed" to by
                     the VM and can be used at any time by the allocating
                     application.  With strict overcommit enabled on the
                     system (mode 2 in /proc/sys/vm/overcommit_memory),
                     allocations which would exceed the CommitLimit will
                     not be permitted.  This is useful if one needs to
                     guarantee that processes will not fail due to lack
                     of memory once that memory has been successfully
                     allocated.

              VmallocTotal %lu
                     Total size of vmalloc memory area.

              VmallocUsed %lu
                     Amount of vmalloc area which is used.  Since Linux
                     4.4, this field is no longer calculated, and is hard
                     coded as 0.  See /proc/vmallocinfo.

              VmallocChunk %lu
                     Largest contiguous block of vmalloc area which is
                     free.  Since Linux 4.4, this field is no longer
                     calculated and is hard coded as 0.  See
                     /proc/vmallocinfo.

              HardwareCorrupted %lu (since Linux 2.6.32)
                     (CONFIG_MEMORY_FAILURE is required.)  [To be
                     documented.]

              LazyFree %lu (since Linux 4.12)
                     Shows the amount of memory marked by madvise(2)
                     MADV_FREE.

              AnonHugePages %lu (since Linux 2.6.38)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Non-file
                     backed huge pages mapped into user-space page
                     tables.

              ShmemHugePages %lu (since Linux 4.8)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Memory
                     used by shared memory (shmem) and tmpfs(5) allocated
                     with huge pages.

              ShmemPmdMapped %lu (since Linux 4.8)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Shared
                     memory mapped into user space with huge pages.

              CmaTotal %lu (since Linux 3.1)
                     Total CMA (Contiguous Memory Allocator) pages.
                     (CONFIG_CMA is required.)

              CmaFree %lu (since Linux 3.1)
                     Free CMA (Contiguous Memory Allocator) pages.
                     (CONFIG_CMA is required.)

              HugePages_Total %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The size of the
                     pool of huge pages.

              HugePages_Free %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The number of
                     huge pages in the pool that are not yet allocated.

              HugePages_Rsvd %lu (since Linux 2.6.17)
                     (CONFIG_HUGETLB_PAGE is required.)  This is the
                     number of huge pages for which a commitment to
                     allocate from the pool has been made, but no
                     allocation has yet been made.  These reserved huge
                     pages guarantee that an application will be able to
                     allocate a huge page from the pool of huge pages at
                     fault time.

              HugePages_Surp %lu (since Linux 2.6.24)
                     (CONFIG_HUGETLB_PAGE is required.)  This is the
                     number of huge pages in the pool above the value in
                     /proc/sys/vm/nr_hugepages.  The maximum number of
                     surplus huge pages is controlled by
                     /proc/sys/vm/nr_overcommit_hugepages.

              Hugepagesize %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The size of huge
                     pages.

              DirectMap4k %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     4 kB pages.  (x86.)

              DirectMap4M %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     4 MB pages.  (x86 with CONFIG_X86_64 or
                     CONFIG_X86_PAE enabled.)

              DirectMap2M %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     2 MB pages.  (x86 with neither CONFIG_X86_64 nor
                     CONFIG_X86_PAE enabled.)

              DirectMap1G %lu (since Linux 2.6.27)
                     (x86 with CONFIG_X86_64 and
                     CONFIG_X86_DIRECT_GBPAGES enabled.)


```

[](#SEE_ALSO)SEE ALSO         [top](#top_of_page)
-------------------------------------------------

```
       proc(5)


```

[](#COLOPHON)COLOPHON         [top](#top_of_page)
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

Linux man-pages 6.16            2025-09-21                proc_meminfo(5)


```

<table><tbody><tr><td><p>HTML rendering created 2026-01-16 by <a href="https://man7.org/mtk/index.html">Michael Kerrisk</a>, author of <a href="https://man7.org/tlpi/"><em>The Linux Programming Interface</em></a>.</p><p>For details of in-depth <strong>Linux/UNIX system programming training courses</strong> that I teach, look <a href="https://man7.org/training/">here</a>.</p><p>Hosting by <a href="https://www.jambit.com/index_en.html">jambit GmbH</a>.</p></td><td></td><td><a href="https://man7.org/tlpi/"><img class="" src="https://man7.org/tlpi/cover/TLPI-front-cover-vsmall.png"></a></td></tr></tbody></table>

Default Statcounter code for man7.org/linux/man-pages http://www.man7.org/linux/man-pages

[![Web Analytics Made Easy -
StatCounter](https://c.statcounter.com/7422636/0/9b6714ff/1/)](https://statcounter.com/ "Web Analytics
Made Easy - StatCounter")