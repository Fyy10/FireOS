#include "semaphore.h"

int cntl = 0;
int cntr = 0;
sem ml = 1;
sem mr = 1;
sem cnt = 4;
sem mutex = 1;
int true = 1;

void left() {
    while (true) {
        P(&ml);
        if (cntl == 0) P(&mutex);
        cntl++;
        V(&ml);

        P(&cnt);
        // go right;
        V(&cnt);

        P(&ml);
        cntl--;
        if (cntl == 0) V(&mutex);
        V(&ml);
    }
}

void right() {
    while (true) {
        P(&mr);
        if (cntr == 0) P(&mutex);
        cntr++;
        V(&mr);

        P(&cnt);
        // go left;
        V(&cnt);

        P(&mr);
        cntr--;
        if (cntr == 0) V(&mutex);
        V(&mr);
    }
}

int main() {
    // parbegin
    return 0;
}