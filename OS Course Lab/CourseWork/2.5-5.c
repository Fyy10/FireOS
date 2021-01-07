#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"

int global = 4;

int main() {
    int pid;
    int vari = 5;
    printf("before fork\n");
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(0);
    }
    else if (pid == 0) {
        global++;
        vari--;
    }
    printf("global=%d, vari=%d\n", global, vari);
    return 0;
}