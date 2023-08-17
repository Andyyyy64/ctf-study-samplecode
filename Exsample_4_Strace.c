// 子プロセスを生成して、ユーザーに子プロセスのプロセスID(PID)を当てさせるといった問題

#include <stdio.h>
#include <stdlib.h> // ユーティリティ関数のヘッダ exitやatoiやmallocなど
#include <sys/types.h> // データ型のヘッダ pid_tやsize_tなど
#include <unistd.h> // UNIX標準のシステムコールやマクロを使用するためのヘッダ forkやexecveなど

int main() {
    pid_t pid;
    char buf[16];
    int user_input;

    pid = fork(); // 新しい子プロセスを生成するシステムコール　成功すると親プロセスには子プロセスのPIDが、子プロセスには0が返される
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
このプログラムのバイナリをstraceでトレースした際の出力結果

execve("./a.out", ["./a.out"], 0x7fffd1850b90  33 vars) = 0
brk(NULL)                               = 0x55eea8d7e000　　　　　　　　　　　-> プロセスのメモリ空間の境界を示す
arch_prctl(0x3001  ARCH_??? , 0x7ffd7e8dfe00) = -1 EINVAL (Invalid argument)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3　　　　　　　　　　　　　　　　　　 -> プロセスのメモリ空間にロードされる共有ライブラリのキャッシュファイルを開く
fstat(3, {st_mode=S_IFREG|0644, st_size=40058, ...}) = 0
mmap(NULL, 40058, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fb45aac9000 　　　　　　　　　　　　　　　-> プロセスのメモリ空間にロードされる共有ライブラリのキャッシュファイルをマップする
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\300A\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
fstat(3, {st_mode=S_IFREG|0755, st_size=2029592, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fb45aac7000
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
mmap(NULL, 2037344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fb45a8d5000
mmap(0x7fb45a8f7000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7fb45a8f7000
mmap(0x7fb45aa6f000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7fb45aa6f000
mmap(0x7fb45aabd000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fb45aabd000
mmap(0x7fb45aac3000, 13920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fb45aac3000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7fb45aac8540) = 0
mprotect(0x7fb45aabd000, 16384, PROT_READ) = 0
mprotect(0x55eea8401000, 4096, PROT_READ) = 0
mprotect(0x7fb45ab00000, 4096, PROT_READ) = 0
munmap(0x7fb45aac9000, 40058)           = 0
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fb45aac8810) = 9103 　　　　　　-> 子プロセスのPIDが返される cloneはforkと同じく新しいプロセスを生成するシステムコール　linuxではforkはcloneのラッパーとして実装されている
Segmentation Fault
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=9103, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
brk(NULL)                               = 0x55eea8d7e000
brk(0x55eea8d9f000)                     = 0x55eea8d9f000
write(1, "Enter the pid of the child proce"..., 35Enter the pid of the child process　             -> putsの出力
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
read(0, 9103 -> ユーザーの入力
"9103\n", 1024)                 = 5
write(1, "Correct! your Flag is ctf4b{trac"..., 35Correct! your Flag is ctf4b{trace}
) = 35
exit_group(0)                           = ?    　　　　　　　　　　　　 -> プロセスの終了をあらわすシステムコール
+++ exited with 0 +++

*/