//
// Created by jefffu on 2021/1/7.
//

#include "unistd.h"
#include "stdio.h"

int main() {
    pid_t val;
    val = fork();
    if (val == 0) printf("children...\n");
    else {
        sleep(1);
        printf("father...\n");
    }
    return 0;
}
