#include <stdio.h>
#include <stdlib.h>

short buffer;

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

void LoadFile(char* argv) {
    FILE *file;
    file = fopen(argv, "rb");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
    fread(&buffer, sizeof(buffer), 1, file);
    fclose(file);
}

void StoreFile() {
    FILE *file;
    file = fopen("testasm.bin", "wb");
    fwrite(&buffer, sizeof(buffer), 1, file);
    fclose(file);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadFile(argv[1]);
    StoreFile();
    return 0;
}
