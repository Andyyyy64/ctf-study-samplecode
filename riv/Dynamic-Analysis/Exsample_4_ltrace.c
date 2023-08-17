// ハードコードされた文字列をltraceで見つける問題

#include <stdio.h>
#include <string.h>

int main() {
    char buf[32];
    char key[] = "demodesufuckyou!!!";

    puts("Please input the passphrase");
    fgets(buf, sizeof(buf), stdin);
    strtok(buf, "\n"); // 改行コードを削除
    if(!strcmp(buf, key)) { // 二つの文字列を比較
        puts("Congratulations! your flag is ctf4b{trace you life}");
    } else {
        puts("invalid inputs");
    }

    return 0;
}

/*
ltrace -> ライブラリのトレースに使用する。プログラムの動的ライブラリ(libcなど)の関数を呼び出す際の操作をキャッチします５

このプログラムのバイナリをltraceでトレースしたさいの結果

puts("Please input the passphrase"Please input the passphrase
)                                       = 28
fgets(test
"test\n", 32, memory!!)                                       = 0x7fffc68a1b00
strtok("test\n", "\n")                                                    = "test"
strcmp("test", "demodesufuckyou!!!")                                      = 16
invalid inputs
+++ exited (status 0) +++
*/

