#include "semaphore.h"

sem empty_father = 1, empty_mother = 1;
sem full_father = 0, full_mother = 0;
sem mutex = 1;
int true = 1;

void daughter() {
    while (true) {
        P(&empty_father);
        P(&empty_mother);
        P(&mutex);
        // draw;
        V(&mutex);
        V(&full_father);
        V(&full_mother);
    }
}

void father() {
    while (true) {
        P(&full_father);
        P(&mutex);
        // view;
        V(&mutex);
        V(&empty_father);
    }
}

void mother() {
    while (true) {
        P(&full_mother);
        P(&mutex);
        // view;
        V(&mutex);
        V(&empty_mother);
    }
}

int main() {
    // parbegin(daughter(), father(), mother());
    return 0;
}