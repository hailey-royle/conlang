#include <stdio.h>

int main() {
    char write[12];
    write[0] = 0b00011111;//add dst c src c
    write[1] = 0b00000000;//^
    write[2] = 0xf0;//dst c
    write[3] = 0x00;//^
    write[4] = 0xf0;//src c
    write[5] = 0x01;//^
    write[6] = 0b00001110;//mov dst c src m
    write[7] = 0b00000000;//^
    write[8] = 0xff;//dst c
    write[9] = 0xff;//^
    write[10] = 0xf0;//src m
    write[11] = 0x00;//^
    FILE *file;
    file = fopen("test.bin", "wb");
    for (int i = 0; i <= sizeof(write); i++) {
        fwrite(&write[i], 1, 1, file);
    }
    fclose(file);
    return 0;
}
