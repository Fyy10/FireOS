#include "unistd.h"

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        char *argv[] = {"ls", "-al", "./", 0};
        execvp("ls", argv);
    }
    else {
//        char *argv[] = {"ls", "-al", "../", 0};
//        execvp("ls", argv);
        execlp("ls", "ls", "-al", "../", (char*)0);
    }
    return 0;
}