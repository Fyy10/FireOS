#include "semaphore.h"

int lrc = 0;
int rlc = 0;
sem mutex = 1;
sem mlrc = 1;
sem mrlc = 1;
int true = 1;

void left() {
    while (true) {
        P(&mlrc);
        if (lrc == 0) {
            P(&mutex);
        }
        lrc++;
        V(&mlrc);
        // go right;
        P(&mlrc);
        lrc--;
        if (lrc == 0) {
            V(&mutex);
        }
        V(&mlrc);
    }
}

void right() {
    while (true) {
        P(&mrlc);
        if (rlc == 0) {
            P(&mutex);
        }
        rlc++;
        V(&mrlc);
        // go left;
        P(&mrlc);
        rlc--;
        if (rlc == 0) {
            V(&mutex);
        }
        V(&mrlc);
    }
}

int main() {
    // parbegin
    return 0;
}