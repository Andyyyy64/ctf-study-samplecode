// Problem where a child process is created, and the user is asked to guess the child process's Process ID (PID)

#include <stdio.h>
#include <stdlib.h>  // Header for utility functions like exit, atoi, malloc, etc.
#include <sys/types.h>  // Header for data types like pid_t, size_t, etc
#include <unistd.h>  // Header for UNIX standard system calls and macros like fork, execve, etc

int main() {
    pid_t pid;
    char buf[16];
    int user_input;

    pid = fork();  // System call to create a new child process. if successful, the parent process receives the child's PID and the child receives 0
    if(pid == 0) {
        puts("Segmentation Fault");
        exit(0);
    } else {
        puts("Enter the pid of the child process");
        fgets(buf, sizeof(buf), stdin);
        user_input = atoi(buf);
        if(pid == user_input) {
            puts("Correct! your Flag is ctf4b{trace}");
        }
    }

    return 0;
}

/*
strace -> Used to trace system calls. System calls are a set of functions provided by the kernel, used for file operations, memory allocation, process control, etc

Output when tracing this program's binary using strace:


clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fb45aac8810) = 9103  -> Returns the child process's PID. clone is a system call to create a new process just like fork. in Linux, fork is implemented as a wrapper around clone
Segmentation Fault
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=9103, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
brk(NULL)                               = 0x55eea8d7e000
brk(0x55eea8d9f000)                     = 0x55eea8d9f000
write(1, "Enter the pid of the child proce"..., 35Enter the pid of the child process)              -> Output of puts
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
read(0, 9103) -> User's input
"9103\n", 1024)                 = 5
write(1, "Correct! your Flag is ctf4b{trac"..., 35Correct! your Flag is ctf4b{trace}
) = 35
exit_group(0)                           = ?        -> System call indicating process termination
+++ exited with 0 +++

*/
