#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("wrong number of args\n");
        return 1;
    }
    printf("%d, %s\n", argc, argv[1]);
    return 0;
}
