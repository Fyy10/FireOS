// fair

#include "semaphore.h"

int reader_cnt = 0;
sem mutex = 1;
sem wrsem = 1;
sem wsem = 1;
int true = 1;

void reader(int i) {
    while (true) {
        P(&wrsem);
        P(&mutex);
        if (reader_cnt == 0) {
            P(&wsem);
        }
        reader_cnt++;
        V(&mutex);
        V(&wrsem);
        // read;
        P(&mutex);
        reader_cnt--;
        if (reader_cnt == 0) {
            V(&wsem);
        }
        V(&mutex);
    }
}

void writer() {
    while (true) {
        P(&wrsem);
        P(&wsem);
        // write;
        V(&wsem);
        V(&wrsem);
    }
}

int main() {
    // parbegin
    return 0;
}