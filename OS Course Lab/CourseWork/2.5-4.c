#include "unistd.h"
#include "stdio.h"
#include "string.h"

int main() {
    int i;
    static char buffer[10];
    if (fork() == 0) strcpy(buffer, "Children\n");
    else strcpy(buffer, "Parent\n");
    for (i = 0; i < 5; i++) {
        sleep(1);
        write(1, buffer, sizeof(buffer));
    }
    return 0;
}