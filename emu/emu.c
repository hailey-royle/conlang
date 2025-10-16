#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define JMP 0
#define LDI 1
#define LDM 2
#define STM 3
#define LDP 4
#define STP 5
#define MOV 6
#define ADD 7
#define AND 8
#define IOR 9
#define XOR 10
#define NOT 11
#define SHL 12
#define SHR 13
#define INC 14
#define DEC 15
#define NOT_ZERO_MASK   0b0000100000000000
#define EQUALS_MASK     0b0000010000000000
#define GREATER_MASK    0b0000001000000000
#define LESS_MASK       0b0000000100000000
#define RIGHT_FOUR_MASK 0b0000000000001111

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
    unsigned short numonic = instruction >> 12;
    unsigned short destination = (instruction >> 8) & RIGHT_FOUR_MASK;
    unsigned short sourceA = (instruction >> 4) & RIGHT_FOUR_MASK;
    unsigned short sourceB = instruction & RIGHT_FOUR_MASK;

    if (numonic == JMP) { 
        address++;
        bool notZeroCheck = instruction & NOT_ZERO_MASK;
        bool equalsCheck = instruction & EQUALS_MASK;
        bool greaterCheck = instruction & GREATER_MASK;
        bool lessCheck = instruction & LESS_MASK;
        if      (notZeroCheck && (regester[sourceA] != 0)) { instruction = memory[address]; }
        else if (equalsCheck && (regester[sourceA] == regester[sourceB])) { instruction = memory[address]; }
        else if (greaterCheck && (regester[sourceA] > regester[sourceB])) { instruction = memory[address]; }
        else if (lessCheck && (regester[sourceA] < regester[sourceB])) { instruction = memory[address]; }
    }
    else if (numonic == LDI) { address++; regester[destination] = memory[address]; }
    else if (numonic == LDM) { address++; regester[destination] = memory[memory[address]]; }
    else if (numonic == STM) { address++; memory[memory[address]] = regester[sourceA]; }
    else if (numonic == LDP) { regester[destination] = memory[regester[sourceA]]; } 
    else if (numonic == STP) { memory[regester[sourceA]] = regester[destination]; } 
    else if (numonic == MOV) { regester[destination] = regester[sourceA]; }
    else if (numonic == ADD) { regester[destination] = regester[sourceA] + regester[sourceB]; }
    else if (numonic == AND) { regester[destination] = regester[sourceA] & regester[sourceB]; }
    else if (numonic == IOR) { regester[destination] = regester[sourceA] | regester[sourceB]; }
    else if (numonic == XOR) { regester[destination] = regester[sourceA] ^ regester[sourceB]; }
    else if (numonic == NOT) { regester[destination] = ~regester[sourceA]; }
    else if (numonic == SHL) { regester[destination] = regester[sourceA] << 1; }
    else if (numonic == SHR) { regester[destination] = regester[sourceA] >> 1; }
    else if (numonic == INC) { regester[destination] = regester[sourceA]++; }
    else if (numonic == DEC) { regester[destination] = regester[sourceA]--; }
    address++;
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
                DrawRectangle((((i % 16) * 16) + j) * 4, (i / 256) * 4, 4, 4, RAYWHITE);
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
