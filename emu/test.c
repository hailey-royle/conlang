#include <stdio.h>

int main() {
    unsigned short prg[] = { 0xb000, 0x3000, 0xffff };
    int insts = 3;
    FILE* fp = fopen("new.bin", "wb");
    fwrite(&prg, sizeof(short), insts, fp);
    return 0;
}
