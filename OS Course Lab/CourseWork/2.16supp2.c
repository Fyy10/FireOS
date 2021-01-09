#include "semaphore.h"

sem call = 0;
sem mutex = 1;
sem empty = 10;
sem full = 0;
int true = 1;

void customer() {
    while (true) {
        P(&empty);
        P(&mutex);
        // get number;
        V(&mutex);
        V(&full);
        P(&call);
    }
}

void waiter() {
    while (true) {
        P(&full);
        V(&call);
        V(&empty);
    }
}

int main() {
    // parbegin
    return 0;
}