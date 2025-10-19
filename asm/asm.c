#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_NULL 0
#define INSTRUCTION 1
#define REGESTER 2
#define IMMEDIATE 3

#define STI 0x03
#define NOT 0x07

#define r0 0
#define r1 1

#define INSTRUCTION_OFFSET 12
#define SOURCEA_OFFSET 8
#define DESTINATION_OFFSET 0

struct instruction {
    unsigned short instruction[2];
    size_t length;
};

struct token {
    unsigned short token;
    char type;
};

struct buffer {
    unsigned short* buffer;
    size_t length;
};

struct file {
    char* buffer;
    char* name;
    size_t length;
    unsigned int possition;
};

struct instruction instruction;
struct token token;
struct buffer code;
struct file file;

void VerifyArgs(int argc, char* argv[]) {
    if (argc != 2) {
        printf("format: $ asm <filename>\n");
        exit(1);
    }
    file.name = argv[1];
}

void LoadFile() {
    FILE* fp = fopen(file.name, "rb");
    if (fp == NULL) {
        printf("file: %s not found\n", file.name);
        exit(1);
    }
    file.length = getdelim(&file.buffer, &file.length, '\0', fp);
    fclose(fp);
}

void GetToken(char type) {
    token.type = TYPE_NULL;
    token.token = 0;
    while (file.possition < file.length) {
        if      (file.buffer[file.possition] == ' ') { file.possition++; }
        else if (file.buffer[file.possition] == '\n') { file.possition++; }
        else if (file.buffer[file.possition] == 'r') {
            if (type != REGESTER) {
                printf("GetToken error unexpected regester\n");
                exit(1);
            }
            token.type = REGESTER;
            token.token = file.buffer[file.possition + 1] & 0xf;
            file.possition += 2;
            return;
        }
        else if ((file.buffer[file.possition] >= '0' && file.buffer[file.possition] <= '9') ||
                (file.buffer[file.possition] >= 'a' && file.buffer[file.possition] <= 'f')) {
            if (type != IMMEDIATE) {
                printf("GetToken error unexpected immediate\n");
                exit(1);
            }
            token.type = IMMEDIATE;
            for (int i = 0; i < 4; i++) {
                token.token = token.token << 4;
                if (file.buffer[file.possition + i] >= '0' && file.buffer[file.possition + i] <= '9') {
                    token.token |= (file.buffer[file.possition + i] & 0xf);
                }
                else if (file.buffer[file.possition + i] >= 'a' && file.buffer[file.possition + i] <= 'f') {
                    token.token |= ((file.buffer[file.possition + i] & 0xf) + 9);
                }
                else {
                    printf("GetImmediateToken error malformed immediate");
                    exit(1);
                }
            }
            file.possition += 4;
            return;
        }
        else if (file.buffer[file.possition] == 'N') {
            if (type != INSTRUCTION) {
                printf("GetToken error unexpected instruction\n");
                exit(1);
            }
            token.type = INSTRUCTION;
            token.token = NOT;
            file.possition += 3;
            return;
        }
        else if (file.buffer[file.possition] == 'S') {
            if (type != INSTRUCTION) {
                printf("GetToken error unexpected instruction\n");
                exit(1);
            }
            token.type = INSTRUCTION;
            token.token = STI;
            file.possition += 3;
            return;
        }
        else {
            printf("GetToken error unknown character: '%c'\n", file.buffer[file.possition]);
            exit(1);
        }
    }
}

void GetInstruction() {
    instruction.instruction[0] = 0;
    instruction.instruction[1] = 0;
    instruction.length = 0;
    GetToken(INSTRUCTION);
    instruction.instruction[0] |= token.token << INSTRUCTION_OFFSET;
    if (token.token == NOT) {
        instruction.length = 1;
        GetToken(REGESTER);
        instruction.instruction[0] |= token.token << SOURCEA_OFFSET;
        GetToken(REGESTER);
        instruction.instruction[0] |= token.token << DESTINATION_OFFSET;
    }
    if (token.token == STI) {
        instruction.length = 2;
        GetToken(REGESTER);
        instruction.instruction[0] |= token.token << DESTINATION_OFFSET;
        GetToken(IMMEDIATE);
        instruction.instruction[1] |= token.token;
    }
}

void CodeAppend() {
    unsigned short* new = realloc(code.buffer, (code.length + instruction.length) * sizeof(instruction.instruction[0]));
    if (new == NULL) {
        printf("realloc failed\n");
        exit(1);
    }
    code.buffer = new;
    for (size_t i = 0; i < instruction.length; i++) {
        code.buffer[code.length + i] = instruction.instruction[i];
    }
    code.length += instruction.length;
}

void Assemble() {
    while (file.possition < file.length) {
        GetInstruction();
        CodeAppend();
    }
}

void StoreFile() {
    FILE* fp = fopen("out.bin", "wb");
    fwrite(code.buffer, code.length * sizeof(code.buffer[0]), 1, fp);
    fclose(fp);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc, argv);
    LoadFile();
    Assemble();
    StoreFile();
    return 0;
}
