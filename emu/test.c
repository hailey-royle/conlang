#include <stdio.h>

int main() {
    unsigned short prg[] = { 0x7010, 0x3000, 0xefff, 0x0f00, 0x0003 };
    int insts = 5;
    FILE* fp = fopen("test.bin", "wb");
    fwrite(&prg, sizeof(short), insts, fp);
    return 0;
}
