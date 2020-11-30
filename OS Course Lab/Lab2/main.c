#include "stdio.h"

int j = 0x302004;

int main() {
    printf("The address of j is 0x%x\n", &j);
    while (j);
    printf("Program terminated normally.\n");
    return 0;
}
