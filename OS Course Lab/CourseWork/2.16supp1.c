#include "semaphore.h"

int seat = 5;
sem mutex = 1;
sem ready = 0;
sem finished = 0;
int true = 1;

void baber() {
    while (true) {
        P(&ready);
        // serve;
        V(&finished);
    }
}

void customer() {
    while (true) {
        P(&mutex);
        if (seat == 0) {
            // leave;
            V(&mutex);
            continue;
        }
        seat--;
        V(&mutex);
        V(&ready);
        P(&finished);
        P(&mutex);
        seat++;
        V(&mutex);
    }
}

int main() {
    return 0;
}