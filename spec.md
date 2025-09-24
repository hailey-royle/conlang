
# architechure

## instructions

| numonic | opp | dst | src1 | src2 | machine code |
|---|---|---|---|---|---|
| LSU | O | - | - | - | 00OOddddaaaabbbb |
| * | STR | m | r |   | 0000----aaaa---- |
| * | LOD | r | m |   | 0001dddd-------- |
|   | MOV | r | r |   | 0010ddddaaaa---- |
|   | IOR | r | r | r | 0011ddddaaaabbbb |
| ALU | O | - | - | - | 01OOddddaaaabbbb |
|   | ADD | r | r | r | 0100ddddaaaabbbb |
|   | AND | r | r | r | 0101ddddaaaabbbb |
|   | XOR | r | r | r | 0110ddddaaaabbbb |
|   | NOT | r | r |   | 0111ddddaaaa---- |
|   | INC | r | r |   | 1000ddddaaaa---- |
|   | DEC | r | r |   | 1001ddddaaaa---- |
|   | BSL | r | r |   | 1010ddddaaaa---- |
|   | BSR | r | r |   | 1011ddddaaaa---- |
| CLU | O | - | - | - | 11ZNEGLSaaaabbbb |
| * | NOP |   | r |   | 11000000aaaa---- |
| * | JMP |   | r |   | 11110000aaaa---- |
| * | JIZ |   | r |   | 11100000aaaa---- |
| * | JNZ |   | r |   | 11010000aaaa---- |
| * | JIS |   | r |   | 11000001aaaa---- |
| * | JIE |   | r | r | 11001000aaaabbbb |
| * | JNE |   | r | r | 11000110aaaabbbb |
| * | JGR |   | r | r | 11000100aaaabbbb |
| * | JGE |   | r | r | 11001100aaaabbbb |
| * | JLS |   | r | r | 11000010aaaabbbb |
| * | JLE |   | r | r | 11001010aaaabbbb |

*instruction also includes location immeditly after in memory for addressing

O: oppcode  
d: destination
a: source1
b: source2
Z: zero flag mask
N: not zero flag mask
E: equals flag mask
G: greater then flag mask
L: less then flag mask
S: signed flagg mask

## regerster layout

0x0-0xf: general purpose  
: instruction  
: address  
: temp  

## memory layout

0x0000-0xefff: general purpose  
0xf000-0xffff: screen output  
: keyboard input?  

## cycles

### 0

- R address
- R memory
- W instruction

### 1

- Increment address
- LSU
    - LOD/STR
        - Read memory
        - Read address
        - Write temp
    - MOV
        - Read source1 regester
        - Write destenation regester
        - SIGNAL DONE
    - IOR
        - Read source1 regester
        - Read source2 regester
        - Write destenation regester
        - SIGNAL DONE
- ALU
    - Read source1 regester
    - Read source2 regester
    - Enable ALU
    - Write destenation regester
    - SIGNAL DONE
- CLU
    - Read source1 regester
    - Read source2 regester
    - Enable CLU
    - Read memory
    - Read address
    - Write temp

### 2

- Increment address
- Read temp
- LSU
    - LOD
        - Read memory
        - Write regester
        - SIGNAL DONE
    - STR
        - Write memory
        - Read regester
        - SIGNAL DONE
    - MOV - NEXT 0
    - IOR - NEXT 0
- ALU - NEXT 0
- CLU
    - if jump enabled
        - Write instruction
        - SIGNAL DONE

# keyboard

|**Default**|   |   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|---|---|
|[ r  ]|[ l  ]|[ m  ]|[ n  ]|      |      |[ v  ]|[ d  ]|[ z  ]|[ j  ]| 111xxx
|[ a  ]|[ e  ]|[ i  ]|[ w  ]|      |      |[ f  ]|[ t  ]|[ s  ]|[ x  ]| 110xxx
|[ +  ]|[ >  ]|[ :  ]|[ (  ]|      |      |[ )  ]|[ =  ]|[ <  ]|[ /  ]| 100xxx
|      |      |[ \e ]|[ \b ]|[ \h ]|[LAY2]|[ _  ]|[ \n ]|      |      |
|**LAY2**|   |   |   |   |   |   |   |   |   |
|[1111]|[1110]|[1101]|[1100]|      |      |[1000]|[1001]|[1010]|[1011]| 011xxx
|[0111]|[0110]|[0101]|[0100]|      |      |[0000]|[0001]|[0010]|[0011]| 010xxx
|[ *  ]|[ {  ]|[ \| ]|[ !  ]|      |      |[ &  ]|[ #  ]|[ }  ]|[ %  ]| 101xxx
|      |      |[ \e ]|[ \b ]|[ \h ]|[LAY2]|[ _  ]|[ \n ]|      |      |

# ascii

```
00000000 \0  
00000001 _  
00000010 \n  
00000011  
00000100 \h  
00000101 \b  
00000110 \e  
00000111  
00001000  
00001001  
00001010  
00001011  
00001100  
00001101  
00001110  
00001111  
00010000 0000  
00010001 0001  
00010010 0010  
00010011 0011  
00010100 0100  
00010101 0101  
00010110 0110  
00010111 0111  
00011000 1000  
00011001 1001  
00011010 1010  
00011011 1011  
00011100 1100  
00011101 1101  
00011110 1110  
00011111 1111  
00100000 +  
00100001 >  
00100010 :  
00100011 (  
00100100 )  
00100101 =  
00100110 <  
00100111 /  
00101000 *  
00101001 {  
00101010 |  
00101011 !  
00101100 &  
00101101 #  
00101110 }  
00101111 %  
00110000 f  
00110001 t  
00110010 s  
00110011 x  
00110100 w  
00110101 i  
00110110 e  
00110111 a  
00111000 v  
00111001 d  
00111010 z  
00111011 j  
00111100 n  
00111101 m  
00111110 l  
00111111 r  
```
