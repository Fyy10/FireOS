//
// Created by jefffu on 2021/1/8.
//

#include "semaphore.h"
#include "stdio.h"

void P(sem* s) {
    (*s)--;
    if ((*s) < 0) {
        // block
    }
}

void V(sem* s) {
    (*s)++;
    if ((*s) <= 0) {
        // wake up
    }
}

//int main() {
//    // test
//    sem s=1;
//    P(&s);
//    printf("%d\n", s);
//    V(&s);
//    printf("%d\n", s);
//    return 0;
//}
