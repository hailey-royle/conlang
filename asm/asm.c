#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buffer{
    char* buffer;
    size_t length;
};
struct buffer code;

struct file{
    struct buffer data;
    char* name;
    int possition;
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

void StoreFile() {
    int nameLength = strlen(file.name);
    file.name[nameLength - 3] = 'b';
    file.name[nameLength - 2] = 'i';
    file.name[nameLength - 1] = 'n';
    FILE* fp = fopen(file.name, "wb");
    fwrite(code.buffer, code.length, 1, fp);
    fclose(fp);
}

int main(int argc, char* argv[]) {
    VerifyArgs(argc, argv);
    LoadFile();
    code.buffer = file.data.buffer;
    code.length = file.data.length;
    StoreFile();
    return 0;
}
