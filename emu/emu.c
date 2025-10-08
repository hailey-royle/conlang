#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define STR 0
#define LOD 1
#define MOV 2
#define IOR 3
#define ADD 4
#define AND 5
#define XOR 6
#define NOT 7
#define INC 8
#define DEC 9
#define BSL 10
#define BSR 11
#define CLU 3
#define ZERO_MASK     0b0010000000000000
#define NOT_ZERO_MASK 0b0001000000000000
#define EQUALS_MASK   0b0000100000000000
#define GREATER_MASK  0b0000010000000000
#define LESS_MASK     0b0000001000000000
#define SIGNED_MASK   0b0000000100000000
#define LSB_FOUR_MASK 0b0000000000001111
#define MAX_SIGNED 32767

#define RAM_SIZE 65536 //2^16
#define REG_SIZE 16
#define SCREEN_START 61444

#define CYCLES_FRAME 6250 // 1mh clock 64 fps 2.5 clock per instruction
#define FPS 64

unsigned short memory[RAM_SIZE];
unsigned short regester[REG_SIZE];
unsigned short instruction;
unsigned short address;

void VerifyArgs(const int argc) {
    if (argc != 2) {
        printf("Format: $ emu <filename>\n");
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
    fread(memory, size, 1, file);
    fclose(file);
}

void ExecuteInstruction() {
    if (memory[address] == 0b0000000000000000) {
        return;
    }
    instruction = memory[address];
    address++;
    unsigned short numonic = instruction >> 14;
    unsigned short oppcode = instruction >> 12;
    unsigned short destination = (instruction >> 8) & LSB_FOUR_MASK;
    unsigned short source1 = (instruction >> 4) & LSB_FOUR_MASK;
    unsigned short source2 = instruction & LSB_FOUR_MASK;
    if      (oppcode == STR) { memory[memory[address]] = regester[source1]; address++; }
    else if (oppcode == LOD) { regester[destination] = memory[memory[address]]; address++; }
    else if (oppcode == MOV) { regester[destination] = regester[source1]; }
    else if (oppcode == IOR) { regester[destination] = regester[source1] | regester[source2]; }
    else if (oppcode == ADD) { regester[destination] = regester[source1] + regester[source2]; }
    else if (oppcode == AND) { regester[destination] = regester[source1] & regester[source2]; }
    else if (oppcode == XOR) { regester[destination] = regester[source1] ^ regester[source2]; }
    else if (oppcode == NOT) { regester[destination] = ~regester[source1]; }
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
        if      (zeroCheck & (regester[source1] == 0)) { instruction = memory[address]; address++; }
        else if (notZeroCheck & (regester[source1] != 0)) { instruction = memory[address]; address++; }
        else if (equalsCheck & (regester[source1] == regester[source2])) { instruction = memory[address]; address++; }
        else if (greaterCheck & (regester[source1] > regester[source2])) { instruction = memory[address]; address++; }
        else if (lessCheck & (regester[source1] < regester[source2])) { instruction = memory[address]; address++; }
        else if (signedCheck & (regester[source1] < MAX_SIGNED)) { instruction = memory[address]; address++; }
    }
}

void Frame() {
    int bitMasks[16] = { 0b1000000000000000,
                         0b1100000000000000,
                         0b1010000000000000,
                         0b1001000000000000,
                         0b1000100000000000,
                         0b1000010000000000,
                         0b1000001000000000,
                         0b1000000100000000,
                         0b1000000010000000,
                         0b1000000001000000,
                         0b1000000000100000,
                         0b1000000000010000,
                         0b1000000000001000,
                         0b1000000000000100,
                         0b1000000000000010,
                         0b1000000000000001 };
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = SCREEN_START; i < RAM_SIZE; i++) {
        for (int j = 0; j < 16; j++) {
            if (memory[i] & bitMasks[j]) {
                DrawRectangle((i % 256) * 4, (i / 256) * 4, 4, 4, RAYWHITE);
            }
        }
    }
    EndDrawing();
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc);
    LoadProgram(argv[1]);
    InitWindow(1024, 1024, "emu");
    SetTargetFPS(64);
    while (!WindowShouldClose()) {
        for (int i = 0; i < CYCLES_FRAME; i++) {
            ExecuteInstruction();
        }
        Frame();
    }
    CloseWindow();
    return 0;
}
