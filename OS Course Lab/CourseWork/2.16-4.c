// writer first with sem z (real writer first)

#include "semaphore.h"

int reader_cnt = 0;
int writer_cnt = 0;
sem wsem = 1;
sem rsem = 1;
sem z = 1;
sem mrc = 1;
sem mwc = 1;
int true = 1;

void reader(int i) {
    while (true) {
        P(&z);
        P(&rsem);
        P(&mrc);
        if (reader_cnt == 0) {
            P(&wsem);
        }
        reader_cnt++;
        V(&mrc);
        V(&rsem);
        V(&z);
        // read;
        P(&mrc);
        reader_cnt--;
        if (reader_cnt == 0) {
            V(&wsem);
        }
        V(&mrc);
    }
}

void writer() {
    while (true) {
        P(&mwc);
        if (writer_cnt == 0) {
            P(&rsem);
        }
        writer_cnt++;
        V(&mwc);

        P(&wsem);
        // write;
        V(&wsem);

        P(&mwc);
        writer_cnt--;
        if (writer_cnt == 0) {
            V(&rsem);
        }
        V(&mwc);
    }
}

int main() {
    // parbegin
    return 0;
}