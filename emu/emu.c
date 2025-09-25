#include <stdio.h>
#include <stdlib.h>

#define STR 0
#define LOD 1
#define MOV 2
#define IOR 4
#define ADD 5
#define AND 6
#define XOR 7
#define NOT 8
#define INC 9
#define DEC 10
#define BSL 11
#define BSR 12
#define CLU 3
#define ZERO_MASK     0b0010000000000000
#define NOT_ZERO_MASK 0b0001000000000000
#define EQUALS_MASK   0b0000100000000000
#define GREATER_MASK  0b0000010000000000
#define LESS_MASK     0b0000001000000000
#define SIGNED_MASK   0b0000000100000000
#define LSB_FOUR_MASK 0b0000000000001111

#define RAM_SIZE 65536 //2^16
#define REG_SIZE 16
#define SCREEN_START RAM_SIZE - 4092 //256*256

short memory[RAM_SIZE];
short regester[REG_SIZE];
short instruction;
short address;
short temp;
short cycle;

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

void ExecuteInstruction() {
    instruction = memory[address];
    address++;

    short numonic = instruction >> 14;
    short oppcode = instruction >> 12;
    short destination = (instruction >> 8) & LSB_FOUR_MASK;
    short source1 = (instruction >> 4) & LSB_FOUR_MASK;
    short source2 = instruction & LSB_FOUR_MASK;

    if      (oppcode == STR) { memory[address] = regester[source1]; address++; }
    else if (oppcode == LOD) { regester[destenation] = memory[address]; address++; }
    else if (oppcode == MOV) { regester[destination] = regester[source1]; }
    else if (oppcode == IOR) { regester[destination] = regester[source1] | regester[source2]; }
    else if (oppcode == ADD) { regester[destination] = regester[source1] + regester[source2]; }
    else if (oppcode == AND) { regester[destination] = regester[source1] & regester[source2]; }
    else if (oppcode == XOR) { regester[destination] = regester[source1] ^ regester[source2]; }
    else if (oppcode == NOT) { regester[destination] = !regester[source1]; }
    else if (oppcode == INC) { regester[destination] = regester[source1]++; }
    else if (oppcode == DEC) { regester[destination] = regester[source1]--; }
    else if (oppcode == BSL) { regester[destination] = regester[source1] << 1; }
    else if (oppcode == BSR) { regester[destination] = regester[source1] >> 1; }
    else if (numonic == CLU) {
        bool zeroCheck = instruction & ZERO_MASK;
        bool notZeroCheck = instruction & NOT_ZERO_MASK;
        bool equalsCheck = instruction & EQUALS_MASK;
        bool greaterCheck = instruction & GREATER_MASK;
        bool lessCheck = instruction & LESS_MASK;
        bool signedCheck = instruction & SIGNED_MASK;

        if      (zeroCheck && (regester[source1] == 0)) { instruction = memory[address]; address++; }
        else if (notZeroCheck && (regester[source1] != 0)) { instruction = memory[address]; address++; }
        else if (equalsChcek && (regester[source1] == regester[source2])) { instruction = memory[address]; address++; }
        else if (greaterCheck && (regester[source1] > regester[source2])) { instruction = memory[address]; address++; }
        else if (lessCheck && (regester[source1] < regester[source2])) { instruction = memory[address]; address++; }
        else if (signedCheck && (regester[source1] < 0)) { instruction = memory[address]; address++; }
    }
}

void RunEmulator() {
    while (true) {
        ExecuteInstruction();
        if (instruction >= SCREEN_START) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadProgram(argv[1]);
    RunEmulator();
    return 0;
}
