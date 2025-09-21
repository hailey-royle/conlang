#include <stdio.h>
#include <stdlib.h>

void VerifyArgs(int argc) {
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

void LoadProgram(char* argv) {
    FILE* file;
    file = fopen(argv, "r");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadProgram(argv[1]);
    return 0;
}
