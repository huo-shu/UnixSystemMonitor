## NAME    

```markdown
       proc - process information, system information, and sysctl pseudo-filesystem
```

翻译：进程信息、系统信息、 sysctl 伪文件系统

## DESCRIPTION  

### Introduction

```markdown
       The proc filesystem is a pseudo-filesystem which provides an
       interface to kernel data structures.  It is commonly mounted at
       /proc.  Typically, it is mounted automatically by the system, but
       it can also be mounted manually using a command such as:

           mount -t proc proc /proc

       Most of the files in the proc filesystem are read-only, but some
       files are writable, allowing kernel variables to be changed.

```

翻译：

proc 文件系统是一种**伪文件系统**，为内核数据结构提供访问接口。

通常挂载在 `/proc` 目录，系统一般会自动挂载，也可手动挂载。

大部分文件为**只读**，但部分文件可写，允许修改内核变量。

###   Overview

```markdown
   	Underneath /proc, there are the following general groups of files
       and subdirectories:   
   /proc/pid subdirectories
          Each one of these subdirectories contains files and
          subdirectories exposing information about the process with
          the corresponding process ID.

          Underneath each of the /proc/pid directories, a task
          subdirectory contains subdirectories of the form task/tid,
          which contain corresponding information about each of the
          threads in the process, where tid is the kernel thread ID
          of the thread.

          The /proc/pid subdirectories are visible when iterating
          through /proc with getdents(2) (and thus are visible when
          one uses ls(1) to view the contents of /proc).

   /proc/tid subdirectories
          Each one of these subdirectories contains files and
          subdirectories exposing information about the thread with
          the corresponding thread ID.  The contents of these
          directories are the same as the corresponding
          /proc/pid/task/tid directories.

          The /proc/tid subdirectories are not visible when iterating
          through /proc with getdents(2) (and thus are not visible
          when one uses ls(1) to view the contents of /proc).

   /proc/self
          When a process accesses this magic symbolic link, it
          resolves to the process's own /proc/pid directory.

   /proc/thread-self
          When a thread accesses this magic symbolic link, it
          resolves to the process's own /proc/self/task/tid
          directory.

   /proc/[a-z]*
          Various other files and subdirectories under /proc expose
          system-wide information.

   All of the above are described in more detail in separate manpages
   whose names start with proc_.
```

AI翻译：

> 在 `/proc` 下，主要包含以下几类文件与子目录：
>
> ### `/proc/[pid]` 子目录
>
> 每个子目录包含对应进程 ID 的相关信息。
>
> 在每个 `/proc/[pid]` 下，存在 `task/[tid]` 子目录，
>
> 包含进程中每个线程的信息，`tid` 为内核线程 ID。
>
> 使用 `getdents(2)` 遍历 `/proc` 时，这些目录可见。
>
> ### `/proc/[tid]` 子目录
>
> 包含对应线程 ID 的信息，内容与 `/proc/[pid]/task/[tid]` 一致。
>
> 使用 `getdents(2)` 遍历 `/proc` 时，这些目录**不可见**。
>
> ### `/proc/self`
>
> 当进程访问此魔法符号链接时，会解析为进程自身的 `/proc/[pid]` 目录。
>
> ### `/proc/thread-self`
>
> 当线程访问此魔法符号链接时，会解析为当前线程自己的
>
> `/proc/self/task/[tid]` 目录。
>
> ### `/proc/[a-z]*`
>
> `/proc` 下其他各类文件与子目录，用于展示**系统全局信息**。
>
> 以上所有内容在以 `proc_` 开头的对应手册页中有更详细说明。

