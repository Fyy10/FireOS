#include "semaphore.h"

sem mutex = 1;
int true = 1;

void left() {
    while (true) {
        P(&mutex);
        // go right;
        V(&mutex);
    }
}

void right() {
    while (true) {
        P(&mutex);
        // go left;
        V(&mutex);
    }
}

int main() {
    // parbegin
    return 0;
}