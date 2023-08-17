//find hardcoded strings using ltrace

#include <stdio.h>
#include <string.h>

int main() {
    char buf[32];
    char key[] = "demodesufuckyou!!!";

    puts("Please input the passphrase");
    fgets(buf, sizeof(buf), stdin);
    strtok(buf, "\n"); // Remove newline character
    if(!strcmp(buf, key)) { // Compare the two strings
        puts("Congratulations! your flag is ctf4b{trace you life}");
    } else {
        puts("invalid inputs");
    }

    return 0;
}

/*
ltrace -> Used to trace library operations. Captures the operations when a program calls functions from dynamic libraries (like libc).

When tracing this program's binary using ltrace, the result is:

puts("Please input the passphrase"Please input the passphrase
)                                       = 28
fgets(test
"test\n", 32, 0x7f2bb6d85980)                                       = 0x7fffc68a1b00
strtok("test\n", "\n")                                                    = "test"
strcmp("test", "demodesufuckyou!!!")                                      = 16
invalid inputs
+++ exited (status 0) +++
*/
