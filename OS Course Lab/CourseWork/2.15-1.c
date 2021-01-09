#include "semaphore.h"

sem mutex = 1;
sem n_apple = 0, n_orange = 0;
sem empty = 1;
int true = 1;

void father() {
    while (true) {
        // prepare fruit;
        P(&empty);
        P(&mutex);
        // put fruit
        V(&mutex);
        // if fruit == "apple"
        V(&n_apple);
        // if fruit == "orange"
        V(&n_orange);
    }
}

void son() {
    while (true) {
        P(&n_orange);
        P(&mutex);
        // get orange
        V(&mutex);
        V(&empty);
    }
}

void daughter() {
    while (true) {
        P(&n_apple);
        P(&mutex);
        // get apple
        V(&mutex);
        V(&empty);
    }
}

int main() {
    // parbegin(father(), son(), daughter());
    return 0;
}
