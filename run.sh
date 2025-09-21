#!/bin/bash

if [ "$1" == "asm" ]; then
    gcc assembler/main.c -Wall -Wextra -std=c99 -Og && ./a.out $2 && rm a.out
fi
