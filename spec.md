
# architechure

## instructions

| numonic | dst | srca | srcb | code | assmbly | compiled |
|---|---|---|---|---|
|^JMP | - | r | r | 0000NEGLaaaabbbb | JMP(*flags*,a,b);(d) | ?adr;imm  |
|^LDI | r | i | - | 0001dddd-------- | LDI(a);(d)           | d=imm     |
|^LDM | r | m | - | 0010dddd-------- | LDM(a);(d)           | d=mem.imm |
|^STM | m | r | - | 0011----aaaa---- | STM(a);(d)           | mem.imm=a |
| LDP | r | p | - | 0100ddddaaaa---- | LDP(a);(d)           | d=mem.a   |
| STP | p | r | - | 0101ddddaaaa---- | STP(a);(d)           | mem.d=a   |
| MOV | r | r | - | 0110ddddaaaa---- | MOV(a);(d)           | d=a       |
| ADD | r | r | r | 0111ddddaaaabbbb | ADD(a,b);(d)         | +a,b;d    |
| AND | r | r | r | 1000ddddaaaabbbb | AND(a,b);(d)         | &a,b;d    |
| IOR | r | r | r | 1001ddddaaaabbbb | IOR(a,b);(d)         | |a,b;d    |
| XOR | r | r | r | 1010ddddaaaabbbb | IOR(a,b);(d)         | #a,b;d    |
| NOT | r | r | - | 1011ddddaaaa---- | NOT(a);(d)           | !a;d      |
| SHL | r | r | - | 1100ddddaaaa---- | SHL(a);(d)           | {a;d      |
| SHR | r | r | - | 1101ddddaaaa---- | SHR(a);(d)           | }a;d      |
| INC | r | r | - | 1110ddddaaaa---- | INC(a);(d)           | +a,1;d    |
| DEC | r | r | - | 1111ddddaaaa---- | DEC(a);(d)           | +a,-1;d   |

^instruction also includes location immeditly after in memory for addressing

## regerster layout

- general puropse (r0-rf)
    - Flood memory bus
    - Take memory bus
    - Flood address bus
    - individual to ALU

- instruction
    - Take memory bus
    - Flood CPU control

- address
    - Take memory bus
    - Flood address bus
    - Increment

## cycles

- next ins
    - Inc   adr    
    - Flood adr    adr bus
    - Flood mem    mem bus
    - Take  ins    mem bus

### 0

- JMP
    - Inc   adr    
    - Flood adr    adr bus
    - Flood mem    mem bus
    - Take  reg[p] mem bus
    - Flood reg[a] ALU
    - Flood reg[b] ALU
- STM
    - Inc   adr    
    - Flood adr    adr bus
    - Flood mem    mem bus
    - Take  reg[p] mem bus
- LDM
    - Inc   adr    
    - Flood adr    adr bus
    - Flood mem    mem bus
    - Take  reg[p] mem bus
- LDI
    - Inc   adr    
    - Flood adr    adr bus
    - Flood mem    mem bus
    - Take  reg[d] mem bus
- MOV
    - Flood reg[a] mem bus
    - Take  reg[d] mem bus
- STP
    - Flood reg[d] adr bus
    - Take  mem    mem bus
    - Flood reg[a] mem bus
- LDP
    - Flood reg[d] adr bus
    - Flood mem    mem bus
    - Take  reg[a] mem bus
- ALU
    - Flood reg[a] ALU
    - Flood reg[b] ALU
    - Take  reg[d] mem bus

### 1

- JMP
    - if jump
        - Flood reg[p] mem bus
        - Take  adr    mem bus
    - not jump
        - next  ins
- STM
    - Flood reg[p] adr bus
    - Take  mem    mem bus
    - Flood reg[a] mem bus
- LDM
    - Flood reg[p] adr bus
    - Flood mem    mem bus
    - Take  reg[a] mem bus
- LDI
    - next  ins
- STP
    - next  ins
- LDP
    - next  ins
- MOV
    - next  ins
- ALU
    - next  ins

### 2

- STM
    - next  ins
- LDM
    - next  ins

# pgl

//function declaration
    function(arg1,arg2).(
        *body*
    );(return)

//function call
    function(arg1,arg2);(return)

//start
    start().(
        *body*
    );()

//data
    data().(
        *body*
    );()

//variable
    name=value

//array
    name.count=(value1,value2)

//struct
    name(
        name1=value
        name2=value
    )

Arathmetic Opearations, Conditionals, and Loops are functions

# keyboard

. not an end
, end of list
; end of clause
: end of sentance

|Default||||||||||
|---|---|---|---|---|---|---|---|---|---|
| r  | l  | m  | n  | (  | )  | v  | d  | z  | j  | 111xxx
| a  | e  | i  | w  | :  | ;  | f  | t  | s  | x  | 110xxx
| \| | &  | ?  | <  | .  | ,  | >  | =  | /  | +  | 100xxx
|    |    | \e | \b | \h | L2 | _  | \n |    |    |
|Layer 2||||||||||
|1111|1110|1101|1100| (  | )  |1000|1001|1010|1011| 011xxx
|0111|0110|0101|0100| :  | ;  |0000|0001|0010|0011| 010xxx
| #  | !  | @  | {  | .  | ,  | }  | *  | %  | -  | 101xxx
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
00001011   
00001100   
00001101   
00001110   
00001111   
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
00100000 (  
00100001 =  
00100010 /  
00100011 +  
00100100 )  
00100101 ,  
00100110 .  
00100111 &  
00101000 >  
00101001 *  
00101010 %  
00101011 -  
00101100 >  
00101101 :  
00101110 !  
00101111 |  
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
