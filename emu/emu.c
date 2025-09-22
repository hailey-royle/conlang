#include <stdio.h>
#include <stdlib.h>

#define WORD_LEN 16
#define RAM_SIZE 65536 //2^16

struct emu {
    short ram[RAM_SIZE];
};
struct emu emu;

void VerifyArgs(const int argc) {
    if (argc < 2) {
        printf("no args given\n");
        exit(1);
    }
    if (argc > 2) {
        printf("too many args\n");
        exit(1);
    }
}

void LoadProgram(char* argv) {
    FILE* file = fopen(argv, "rb");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    short size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fread(emu.ram, size, 1, file);
    fclose(file);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadProgram(argv[1]);
    return 0;
}
