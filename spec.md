
# architechure

## instructions

| numonic | opp | cycles | dst | src1 | src2 | machine code |
|---|---|---|---|---|---|---|
| LSU | O | - | - | - | - | 00OOddddaaaa---- |
|   | HLT |   |   |   |   | 0000------------ |
| * | LDM | 3 | r | m |   | 0001dddd-------- |
| * | STM | 3 | m | r |   | 0010----aaaa---- |
|   | MOV | 2 | r | r |   | 0011ddddaaaa---- |
| ALU | O | - | - | - | - | 01OOddddaaaabbbb |
|   | ADD | 2 | r | r | r | 0100ddddaaaabbbb |
|   | AND | 2 | r | r | r | 0101ddddaaaabbbb |
|   | IOR | 2 | r | r | r | 0110ddddaaaabbbb |
|   | NOT | 2 | r | r |   | 0111ddddaaaa---- |
|   | INC | 2 | r | r |   | 1000ddddaaaa---- |
|   | DEC | 2 | r | r |   | 1001ddddaaaa---- |
|   | BSL | 2 | r | r |   | 1010ddddaaaa---- |
|   | BSR | 2 | r | r |   | 1011ddddaaaa---- |
| CLU | O | - | - | - | - | 11ZNEGLSaaaabbbb |
| * | JMP | 2 |   | r |   | 11110000aaaa---- |
| * | JPZ | 2 |   | r |   | 11100000aaaa---- |
| * | JPN | 2 |   | r |   | 11010000aaaa---- |
| * | JPS | 2 |   | r |   | 11000001aaaa---- |
| * | JPE | 2 |   | r | r | 11001000aaaabbbb |
| * | JPG | 2 |   | r | r | 11000100aaaabbbb |
| * | JPL | 2 |   | r | r | 11000010aaaabbbb |
| * | JGL | 2 |   | r | r | 11000110aaaabbbb |
| * | JGE | 2 |   | r | r | 11001100aaaabbbb |
| * | JLE | 2 |   | r | r | 11001010aaaabbbb |
| * | NOP | 2 |   | r |   | 11000000-------- |

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
S: signed flag mask  

## regerster layout

- genelar puropse (r0-r12)
    - Flood memory bus
    - Take memory bus
    - Flood individual to ALU/CLU
    - Take individual to result

- instruction (r13 | INS)
    - Take memory bus
    - Flood CPU control

- pointer (r14 | ADP)
    - Take memory bus
    - Flood address bus

- address (r15 | ADR)
    - Flood address bus
    - Take pointer
    - Increment

- result - not addressable
    - Take ALU
    - Flood individual

- jump - not addressable - single bit
    - Take CLU

## memory layout

0x0000-0xefff: general purpose  
0xf000-0xffff: screen output  
: keyboard input?  

## cycles

- Next ()
    - Increment address
    - Flood address
    - Flood memory
    - Take ()

### 1

- LSU
    - LDM/STM
        - Next (pointer)
    - MOV
        - Flood regester[source1]
        - Take regester[destenation]
- ALU
    - Next (instruction)
    - Enable ALU
    - Flood regester[source1]
    - Flood regester[source2]
    - Take result
- CLU
    - Next (pointer)
    - Enable CLU
    - Flood regester[source1]
    - Flood regester[source2]
    - Take jump

### 2

- LSU
    - LDM
        - Flood pointer
        - Flood memory
        - Take regester
    - STM
        - Flood pointer
        - Take memory
        - Flood regester
    - MOV
        - Next (instruction)
- ALU
    - Flood result
    - Take regester[destenation]
    - Next (instruction)
- CLU
    - If jump
        - Flood pointer
        - Take address
        - Flood address
        - Flood memory
        - Take instruction
    - Not jump
        - Next (instruction)

### 3

- LSU
    - LDM
        - Next (instruction)
    - STM
        - Next (instruction)
    - MOV - next 0
- ALU - next 0
- CLU - next 0

# prl

pointers?
keywords?
stdlib?
program input?

```
data():(
    variable=0
    array.3=(9,3,1)
    struct(
        first = 0,
        second = 0
    )
)

function(a,b,d):(
    !a:a
    +a,1:d
    +a,b:d
)

start():(
    +array.2,array.0:struct.first
    loop(<>array(1),variable):(
        function(struct.first,struct.second,variable)
    )
    if(=array(1),variable):(
        function(struct.first,struct.second,variable)
    )
)
```

# asm

## opperators

```
- ADD   +a,b:d
- AND   &a,b:d
- IOR   |a,b:d
- NOT   !a:d
- INC   +a,1:d
- DEC   -a,1:d
- BSL   *a,2:d
- BSR   /a,2:d
```

## conditionals

```
- JPZ   =a,0:()
- JPN   <>a,0:()
- JPS   <a,0:()
- JPE   =a,b:()
- JPG   <a,b:()
- JPL   >a,b:()
- JGL   <>a,b:()
- JGE   >=a,b:()
- JLE   <=a,b:()
```

## opperator macros

```
- MUL   *a,b:d
    -
- DIV   /a,b:d
    -
- MOD   %a,b:d
    -
- SUB   -a,b:d
    -   !a:a
    -   +a,1:d
    -   +a:b:d
```

# keyboard

|Default||||||||||
|---|---|---|---|---|---|---|---|---|---|
| r  | l  | m  | n  |    |    | v  | d  | z  | j  | 111xxx
| a  | e  | i  | w  |    |    | f  | t  | s  | x  | 110xxx
| &  | .  | ,  | (  |    |    | )  | =  | /  | +  | 100xxx
|    |    | \e | \b | \h | L2 | _  | \n |    |    |
|Layer 2||||||||||
|1111|1110|1101|1100|    |    |1000|1001|1010|1011| 011xxx
|0111|0110|0101|0100|    |    |0000|0001|0010|0011| 010xxx
| |  | !  | :  | <  |    |    | >  | *  | %  | -  | 101xxx
|    |    | \e | \b | \h | L2 | _  | \n |    |    |

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
00001011 :  
00001100 .  
00001101 ,  
00001110 (  
00001111 )  
00010000 0000 0  
00010001 0001 1  
00010010 0010 2  
00010011 0011 3  
00010100 0100 4  
00010101 0101 5  
00010110 0110 6  
00010111 0111 7  
00011000 1000 8  
00011001 1001 9  
00011010 1010 10  
00011011 1011 11  
00011100 1100 12  
00011101 1101 13  
00011110 1110 14  
00011111 1111 15  
00100000 >  
00100001 -  
00100010 *  
00100011 =  
00100100 >  
00100101 +  
00100110 /  
00100111 %  
00101000 &  
00101001 ]  
00101010 {  
00101011 !  
00101100 |  
00101101 [  
00101110 }  
00101111 ~  
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
