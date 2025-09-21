#include <stdio.h>
#include <stdlib.h>

void VerifyArgs(int argc, char* argv[]) {
    if (argc == 2) {
        return;
    }
    if (argc <= 1) {
        printf("too few args, include program to run\n");
        exit(1);
    }
    if (argc >= 3) {
        printf("too many args, only include program to run\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc, argv);
    return 0;
}
