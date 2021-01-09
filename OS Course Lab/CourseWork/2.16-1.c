// reader first

#include "semaphore.h"

int reader_cnt = 0;
sem wsem = 1;
sem mutex = 0;

void reader(int i) {
    P(&mutex);
    if (reader_cnt == 0) {
        P(&wsem);
    }
    reader_cnt++;
    V(&mutex);
    // read data;
    P(&mutex);
    reader_cnt--;
    if (reader_cnt == 0) {
        V(&wsem);
    }
    V(&mutex);
}

void writer() {
    // produce data;
    P(&wsem);
    // write data;
    V(&wsem);
}

int main() {
    // parbegin
    return 0;
}
