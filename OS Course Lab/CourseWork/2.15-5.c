#include "semaphore.h"

sem emptyAP2 = 1, emptyAP3 = 1, emptyB = 1, emptyC = 1;
sem fullAP2 = 0, fullAP3 = 0, fullB = 0, fullC = 0;
sem mutexA = 1, mutexB = 1, mutexC = 1;
int true = 1;

void P1() {
    while (true) {
        // get random;
        P(&emptyAP2);
        P(&emptyAP3);
        P(&mutexA);
        // put A;
        V(&mutexA);
        V(&fullAP2);
        V(&fullAP3);
    }
}

void P2() {
    while (true) {
        P(&fullAP2);
        P(&mutexA);
        // get data;
        V(&mutexA);
        V(&emptyAP2);
        // cal x^2;
        P(&emptyB);
        P(&mutexB);
        // put data;
        V(&mutexB);
        V(&fullB);
    }
}

void P3() {
    while (true) {
        P(&fullAP3);
        P(&mutexA);
        // get data;
        V(&mutexA);
        V(&emptyAP3);
        // cal x^3;
        P(&emptyC);
        P(&mutexC);
        // put data;
        V(&mutexC);
        V(&fullC);
    }
}

void P4() {
    P(&fullB);
    P(&mutexB);
    // get B data;
    V(&mutexB);
    V(&emptyB);

    P(&fullC);
    P(&mutexC);
    // get C data;
    V(&mutexC);
    V(&emptyC);

    // add, print;
}

int main() {
    // parbegin(P1(), P2(), P3(), P4());
    return 0;
}
