#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lexical toxen stored as { type, tokenA, (optional)tokenB }

#define TYPE_INSTRUCTION 0x00
#define TYPE_GRAMMER 0x01
#define TYPE_REGESTER 0x02
#define TYPE_IMMEDIATE 0x03

#define OPEN_PAREN 0x0a
#define CLOSED_PAREN 0x0b
#define CLAUSE_END 0x0f

#define STI 0x03
#define NOT 0x07

#define r0 0
#define r1 1

struct buffer {
    char* buffer;
    size_t length;
};
struct buffer lexer;
struct buffer code;

struct file {
    struct buffer data;
    char* name;
    unsigned int possition;
};
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
    file.data.length = getdelim(&file.data.buffer, &file.data.length, '\0', fp);
    fclose(fp);
}

void BufferAppend(struct buffer* buffer, char* append, int appendLength) {
    char* new = realloc(buffer->buffer, buffer->length + appendLength);
    if (new == NULL) {
        printf("realloc failed\n");
        exit(1);
    }
    memcpy(&new[buffer->length], append, appendLength);
    buffer->buffer = new;
    buffer->length += appendLength;
}

void LexGrammer(char token) {
    char write[2];
    write[0] = TYPE_GRAMMER;
    write[1] = token;
    BufferAppend(&lexer, write, 2);
    file.possition++;
}

void LexRegester() {
    char write[2];
    write[0] = TYPE_REGESTER;
    file.possition++;
    if (file.data.buffer[file.possition] >= '0' && file.data.buffer[file.possition] <= '9') {
        write[1] = file.data.buffer[file.possition] & 0x0f;
    } else if (file.data.buffer[file.possition] >= 'a' && file.data.buffer[file.possition] <= 'f') {
        write[1] = (file.data.buffer[file.possition] & 0x0f) + 9;
    } else {
        printf("LexRegester error, char: %c", file.data.buffer[file.possition]);
        exit(1);
    }
    BufferAppend(&lexer, write, 2);
    file.possition++;
}

void LexNumber() {
    char write[5];
    write[0] = TYPE_IMMEDIATE;
    for (int i = 1; i < 5; i++) {
        if (file.data.buffer[file.possition] >= '0' && file.data.buffer[file.possition] <= '9') {
            write[i] = file.data.buffer[file.possition] & 0x0f;
        } else if (file.data.buffer[file.possition] >= 'a' && file.data.buffer[file.possition] <= 'f') {
            write[i] = (file.data.buffer[file.possition] & 0x0f) + 9;
        } else {
            printf("LexNumber error, char: %c", file.data.buffer[file.possition]);
            exit(1);
        }
        file.possition++;
    }
    BufferAppend(&lexer, write, 5);
    file.possition++;
}

void LexInstruction() {
    char write[1];
    if (file.data.buffer[file.possition] == 'S') {
        write[0] = STI;
    } else if (file.data.buffer[file.possition] == 'N') {
        write[0] = NOT;
    } else {
        printf("LexNumber error, char: %c", file.data.buffer[file.possition]);
        exit(1);
    }
    BufferAppend(&lexer, write, 5);
    file.possition += 3;
}

void Lexer() {
    while (file.possition < file.data.length) {
        if      (file.data.buffer[file.possition] == '(') { LexGrammer(OPEN_PAREN); }
        else if (file.data.buffer[file.possition] == ')') { LexGrammer(CLOSED_PAREN); }
        else if (file.data.buffer[file.possition] == ';') { LexGrammer(CLAUSE_END); }
        else if (file.data.buffer[file.possition] == 'r') { LexRegester(); }
        else if ((file.data.buffer[file.possition] >= '0' && file.data.buffer[file.possition] <= '9') ||
                (file.data.buffer[file.possition] >= 'a' && file.data.buffer[file.possition] <= 'f')) { LexNumber(); }
        else if (file.data.buffer[file.possition] >= 'A' && file.data.buffer[file.possition] <= 'Z') { LexInstruction(); }
        else if (file.data.buffer[file.possition] == ' ' ) { file.possition++; }
        else if (file.data.buffer[file.possition] == '\n' ) { file.possition++; }
        else {
            printf("LexNumber error, char: %c", file.data.buffer[file.possition]);
            exit(1);
        }
    }
}

void StoreFile() {
    FILE* fp = fopen("out.bin", "wb");
    fwrite(code.buffer, code.length, 1, fp);
    fclose(fp);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc, argv);
    LoadFile();
    Lexer();
    code.buffer = lexer.buffer;
    code.length = lexer.length;
    StoreFile();
    return 0;
}
