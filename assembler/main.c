#include <stdio.h>
#include <stdlib.h>

void VerifyArgs(const int argc) {
    if (argc < 2) {
        printf("no args given");
        exit(1);
    }
    if (argc > 2) {
        printf("too many args");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    printf("%d, %s\n", argc, argv[1]);
    return 0;
}
