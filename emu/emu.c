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

int fsize(FILE *file) {
    int possition = ftell(file);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, possition, SEEK_SET);
    return size;
}

void LoadProgram(char* argv) {
    FILE* file;
    file = fopen(argv, "rb");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
    fread(emu.ram, sizeof(emu.ram[0]), 1, file);
    fclose(file);
}

void OutputBinary() {
    FILE* file;
    file = fopen("testemu.bin", "wb");
    fwrite(emu.ram, sizeof(emu.ram[0]), 1, file);
    fclose(file);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadProgram(argv[1]);
    OutputBinary();
    return 0;
}
