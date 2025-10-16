#include <stdio.h>

int main() {
    unsigned short prg[] = { 0xb000, 0x3000, 0xffff, 0x0f00, 0x0003 };
    int insts = 5;
    FILE* fp = fopen("test.bin", "wb");
    fwrite(&prg, sizeof(short), insts, fp);
    return 0;
}
