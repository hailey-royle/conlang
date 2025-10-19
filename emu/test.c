#include <stdio.h>

int main() {
    short prg[] = { 0x7010, //NOT b a
                    0x3000, //STM a efff
                    0xefff, };
    FILE* fp = fopen("test.bin", "wb");
    fwrite(&prg, sizeof(prg[0]), sizeof(prg) / sizeof(prg[0]), fp);
    return 0;
}
