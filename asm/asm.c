#include <stdio.h>
#include <stdlib.h>

char* oppcode[] = { "HLT", "LDM", "STM", "MOV", "ADD", "AND", "IOR", "NOT", "INC", "DEC", "BSL", "BSR", "JMP", "JPZ", "JPN", "JPS", "JPE", "JPG", "JPL", "JGL", "JGE", "JLE", "NOP" }
int oppcodeCount = 23;

char* inputFile;
char* outputFile;
int inputFileLength;
int inputPlace;
int outputLength;

struct instruction{
    char numonic;
    char opcode;
    char destenation;
    char sourceA;
    char sourceB;
};
struct instruction instruction;

void VerifyArgs(const int argc) {
    if (argc != 2) {
        printf("format: $ asm <filename>\n");
        exit(1);
    }
}

void LoadFile(char* argv) {
    FILE *file = fopen(argv, "rb");
    if (file == NULL) {
        printf("file: %s not found\n", argv);
        exit(1);
    }
    inputFileLength = getdelim(&inputFile, 0, '\0', file);
    fclose(file);
}

void BufferAppend(char* buffer, int* bufferLength, char* append, int appendLength) {
    char* new = realloc(buffer, *bufferLength + appendLength);
    if (new == NULL) {
        return;
    }
    memcpy(&new[*bufferLength], append, appendLength);
    buffer = new;
    *bufferLength += appendLength;
}

int CompareOppcode(int oppcode) {
    if (oppcode[oppcodeNumber][0] != intputFile[inputPlace]) {
        return 0;
    }
    if (oppcode[oppcodeNumber][1] != intputFile[inputPlace + 1]) {
        return 0;
    }
    if (oppcode[oppcodeNumber][2] != intputFile[inputPlace + 2]) {
        return 0;
    }
    return 1;
}

void GetInstruction() {
    for (int i = 0; i < insturctionCount; i++) {
        if (CompareOppcode(i);) {
            break;
        }
    }
}

void Assemble() {
    while (inputFilePlace <= inputFileLength) {
        GetInstruction();
    }
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadFile(argv[1]);
    Assemble();
    StoreFile();
    return 0;
}
