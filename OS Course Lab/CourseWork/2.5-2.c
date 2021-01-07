//
// Created by jefffu on 2021/1/7.
//

#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"

int main() {
    printf("Hello\n");
    fork();
    printf("Bye\n");
    return 0;
}