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
    FILE *file = fopen(argv, "rb");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
    fread(&buffer, sizeof(buffer), 1, file);
    fclose(file);
}

void CreateTest() {
    short test[10];
    test[0] = 0b0111000000010000;// NOT r0 r1
    test[1] = 0b1111111111111111;
    test[2] = 0b1111111111111111;// STR r0
    test[3] = 0b1111111111111111;
    test[4] = 0b1111111111111111;// STR r0
    test[5] = 0b1111111111111110;
    test[6] = 0b1111111111111111;// STR r0
    test[7] = 0b1111111111111101;
    test[8] = 0b1111111111111111;// STR r0
    test[9] = 0b1111111111111100;

    short nothing[1];
    nothing[0] = 0b1100000000000000;

    FILE *file = fopen("test.bin", "wb");
    //fwrite(nothing, sizeof(nothing), 1, file);
    fwrite(test, sizeof(test), 1, file);
    fclose(file);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    //LoadFile(argv[1]);
    CreateTest();
    return 0;
}
