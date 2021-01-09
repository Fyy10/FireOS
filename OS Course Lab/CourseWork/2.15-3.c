#include "semaphore.h"

sem mutex = 1;
sem n_apple = 0, n_orange = 0;
sem empty_apple = 1, empty_orange = 1;
int true = 1;

void father() {
    while (true) {
        // prepare apple;
        P(&empty_apple);
        P(&mutex);
        // put apple;
        V(&mutex);
        V(&n_apple);
    }
}

void mother() {
    while (true) {
        // prepare orange;
        P(&empty_orange);
        P(&mutex);
        // put orange;
        V(&mutex);
        V(&n_orange);
    }
}

void daughter() {
    while (true) {
        P(&n_apple);
        P(&n_orange);
        P(&mutex);
        // get apple
        V(&mutex);
        V(&empty_apple);
        V(&empty_orange);
    }
}

int main() {
    // parbegin(father(), mother(), daughter());
    return 0;
}
