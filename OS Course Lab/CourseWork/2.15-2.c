#include "semaphore.h"

sem mutex = 1;
sem n_apple = 0, n_orange = 0;
sem empty = 1;
int true = 1;

void father() {
    while (true) {
        // prepare apple;
        P(&empty);
        P(&mutex);
        // put apple;
        V(&mutex);
        V(&n_apple);
    }
}

void mother() {
    while (true) {
        // prepare orange;
        P(&empty);
        P(&mutex);
        // put orange;
        V(&mutex);
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
    // parbegin(father(), mother(), son(), daughter());
    return 0;
}
