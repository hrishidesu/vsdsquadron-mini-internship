# VSDSquadron mini Internship Cohort 20th May 2024

<details>

<summary><mark>Task 1</mark>: Testing riscv gnu tools and identifying assembly codes coressponding to the c code </summary>

## Task 1 


1. Succesfully installed the provided vdi file on Virtualbox following the given instructions. All the required softwares and packages were installed: gnu risc-v toolchain
2. Installed vscode using `sudo snap install code` to edit the c codes. 

### <span style="background-color:yellow; color:black">LAB 1</span>
3. To perform `Lab 1`, we need to write a c program which calculates the sum of first n numbers. `code ./sum1to15.c` opens a empty c file named <span style="color: #ffef96;">sum1to15</span> in vscode in the same directory.</p>

![sum1to15 terminal code](./Task%201/Screenshots/1.png)

</p>

The output can also be compiled in the terminal inside vscode. The command `gcc -o sum1to15 sum1to15.c` compiles the <span style="color: #ffef96;">sum1to15.c</span> code and outputs an object file. </p>

![sum1to15 vscode](./Task%201/Screenshots/2.png)

The code for calculating sum of first n numbers is:

```c

#include<stdio.h>

int main()
{
    int i,n=15,sum=0;
    
    for (i=1;i<=n;i++)
    {
        sum+=i;
    }
    printf("The sum from 1 to %d is %d\n\n",n,sum);
    return 0;
}
```
The same procedure is followed for n=100

![sum1to100 vscode](./Task%201/Screenshots/3.png)

</p>
</br>
</p>

![sum1to100 terminal](./Task%201/Screenshots/4.png)  

### <span style="background-color:yellow; color:black">LAB 2</span>

4. To perform `Lab 2`, GNU compiler for RISC V is used. `riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1to15.o sum1to15.c` command is used recompile the code using the RISC V architecture.
</p>

![sum1to15 riscv](./Task%201/Screenshots/5.png)  

In the above command, <span style= "color:yellow">riscv64-unknown-elf-gcc</span> specifies that it is a GNU code for RISCV architecture where <span style= "color:yellow">unknown</span> is a placeholder for vendor or system, <span style= "color:yellow">elf</span> <span style= "color:#96ceb4">(_Executable and Linkable Format_)</span> specifies output binary format. </p>

<span style= "color:yellow">-O1</span> specifies optimization levels of the generated code. Other optimization levels are: <span style= "color:#96ceb4">_O0, O2, O3, Os, Ofast_</span>. Each indicates a different level of optimization.

<span style= "color:yellow">-mabi=lp64</span> specifies the ABI (Application Binary Interface) which determines how the program interact with the hardware. Here, lp64 stands for 64 bit long integer and pointers. Some other options are: ilp32, ilp32d, lp64, lp64d.  

<span style= "color:yellow">march=rv64i</span> specifies the target architecture and type of instructions set the compiler should generate. Rest of the code <span style= "color:yellow">-o sum1to15.o sum1to15.c</span> is same as discussed in `LAB 1`, `ls -ltr sum1to15.o` gives detail of the object file.  

5. To view the RISC V ISA instructions, the objectdump file which contains the disassembled components of the converted source code. It contains the instructions in assembly language. To access the instructions, the command `riscv64-unknown-elf-objdump -d sum1to15.o`.


![riscv obj sum1to15](./Task%201/Screenshots/6.png)


The assembly codes for the RISC V is very large.

![objdump large](./Task%201/Screenshots/7.png)

6. So, to browse effectively and find the <span style= "color:#96ceb4">main</span> section of the code which executes the source code, `riscv64-unknown-elf-objdump -d sum1to15.o | less` command is used. It is easy to browse through the instructions to find the <span style="color:#96ceb4">main</span> section by using <span style="color:yellow">/main</span>.

![sum1to15 main assembly](./Task%201/Screenshots/13_1to15.png)  

11 instructions are required to calculate the sum from 1 to 15 using <span style="color:yellow">-O1</span>. This can also be calculated by subtracting the first instruction address of the main section from the first instruction address of the next section and then dividing the result by 4 because it is a word addressable memory architecture.  

<table>
<tr>
    <td><img src="./Task 1/Screenshots/Calculate1.png" alt="calculate 1"></td>
    <td><img src="./Task 1/Screenshots/Calculate2.png" alt="calculate 2"></td>
</tr>
</table>  

The same code is complied again using `riscv64-unknown-elf-gcc -Ofast -mabi=lp64 -march=rv64i -o sum1to15f.o sum1to15.c`. The only change is <span style="color:yellow">-Ofast</span> for better optimization and shorter code. No difference is seen in output. But difference is seen when <span style="color:yellow">sum1to100.c</span> is compiled using <span style="color:yellow">-O1</span> and <span style="color:yellow">-Ofast</span>.  

![riscv sum1to15f](./Task%201/Screenshots/8.png)  

![obj sum1to15f](./Task%201/Screenshots/14_1to15f.png)

Similary code for sum from 1 to 100 is compiled using <span style="color:yellow">-O1</span> and <span style="color:yellow">-Ofast</span>.  

![riscv sum1to100](./Task%201/Screenshots/10.png)  

Observing the assembly instructions, it is noticed that <span style="color:yellow">-Ofast</span> mode requires 12 instructions and <span style="color:yellow">-O1</span> requires 15 instructions.

![sum1to100](./Task%201/Screenshots/15_1to100.png)  

![sum1to100f](./Task%201/Screenshots/17_1to100f.png)  

<br>

</details>

<br>

<details>

## Task 2

<summary><mark>Task 2</mark>: Detailed study of RISCV ISA and identifying the 32 bit binary code for basic instructions</summary>

### RISCV Instruction Set Architecture

RISC V Instructions Set Architecture offers two different levels of access to the system hardware: **Unprivileged mode** and **Privileged mode**.

The three modes of RISC V ISA are **User mode**, **Machine mode** and **Supervisor mode**.

**User mode** is a type of Unprivileged mode which provides least or limited access to the system's hardware. It provides a safe environment for user applications to run, restricting them from changing critical system resources.   

The other two modes: **Machine mode** and **Supervisor mode** are types of Privileged Mode. In Privileged mode, privileged set of instructions can be run.   

Machine mode provides unrestricted access to the hardware for firmware or low-level system management.   

Supervisor mode is used to manage system resources and provide an execution environment for user applications, typically used by the operating system kernel.  

<br>

RISC-V ISA is defined as a base integer ISA. The base consists of a minimal set of instructions sufficient for compilers, assemblers, linkers and operating systems. There are currently four base ISAs: **RV32I**, **RV32E**, **RV64I** and **RV64E**.

![base version](./Task%202/Baseversion.png)

**RV32E** and **RV64E** are reduced subsets of **RV32I** and **RV64I** respectively. Each base integer instruction set is characterized by the width of the integer registers and the corresponding size of the address space and by the number of integer registers. There are two primary base integer variants, RV32I and RV64I.  

Each base ISAs can be extended using extensions for added functionality. Some extensions are:  
- **M** Extension: Integer multiply/divide.
-  **A** Extension: Atomic operations.
- **F** Extension: Single-precision floating-point.
- **D** Extension: Double-precision floating-point.
- **C** Extension: Compressed 16-bit instructions.  

The steps involved in executing a given instructions are:

1. **Instruction Fetch**(IF): The instruction is fetched from memory using the address provided by the program counter (PC).

2. **Instruction Decode** (ID): The instruction is decoded to determine the operation to be performed and the operands involved.

3. **Execution** (EX): The actual operation specified by the instruction is performed. This could be an arithmetic operation, a logical operation, an address calculation for memory access, etc.Branch Evaluation: If the instruction is a branch, the branch condition is evaluated to determine the next PC value.

4. **Memory Access** (MEM): the memory is accessed for load/store operations. Loads read data from memory into a register, while stores write data from a register to memory.
5. **Write Back** (WB): The result is written back to the destination register.  

<br>

In the base **RV32I** ISA, there are six instruction formats, four core instruction formats:  
1. R
2. I
3. S
4. U  

![core instruction formats](./Task%202/Core%20instructions.png)

And two immediate encoding variants based on the handling of immediates:

5. B (variant of S)
6. J (variant of U)  

### R-Type Instructions

The R-type Instructions are used for integer register-register functions, i.e., used for arithmetic and logical operations that do not involve an immediate value. The R-Type instruction format is:

![R type](./Task%202/R.png)  

Different R-Type instructions are :

![R insctructions](./Task%202/R_ins.png)

### I-Type Instructions

The I-Type instructions use a 12-bit immediate value and are typically used for operations like arithmetic with an immediate value, loads, and certain system instructions. The I-Type instruction format is:  

![I-type](./Task%202/I.png)

Defferent I-type instructions are:

- Arithmetic type instructions

![I arithmetic](./Task%202/I_a_ins.png)

- Load type instructions

![I load](./Task%202/I_load_ins.png)

### S-Type Instructions

The S-type instructions are mainly used for store operations. The 12 bits immediate is disjointed and separated in 5 bits lower immediate and 7 bits upper immediate. The upper immediate is used to offset the rs2 register. The S-Type instruction format is:

![S type](./Task%202/S.png)

S-type instructions are:

![S instructions](./Task%202/S_ins.png)

### B-Type Instructions

B-Type instructions are used for conditional branching. B-Type instruction is a immediate_encoding variant of S-type. The immediate is arranged in a different way in B-type. The source registers, funct and opcode locations are same as S-Type.

![B-type](./Task%202/B.png)

B-type instructions are:

![B instructions](./Task%202/B_ins.png)

### U-Type Instructions

U-Type instructions are used for instructions that set an upper 20-bit immediate value, such as LUI (Load Upper Immediate) and AUIPC (Add Upper Immediate to PC). U-Type instructions are used to handle large constant immediates.

![U-Type](./Task%202/U.png)

U-Type instructions are:

![U instructions](./Task%202/U_ins.png)

### J-Type instructions

J-Type instructions are used for jump operations with a 20-bit immediate value. J-Type instruction is an immediate_encoding variant of U-type. The immediate is arranged in a different way in J-type from U-type. The location of opcode and destination register is same as U-Type.

![J-type](./Task%202/J.png)

J-Type instruction:

![J instruction](./Task%202/J_ins.png)

## `To Identify Instruction Type`

**Identify various RISC-V instruction type (R, I, S, B, U, J) and exact 32-bit instruction code in the instruction type format for below RISC-V instructions**  

- **<mark>ADD r6, r2, r1</mark>**  
    The ADD is a R-Type instruction. The base format is `add rd, rs1, rs2`. It adds the value stored in rs1 and rs2, and stores it in rd. So, in above instruction-

    * opcode for `add`: 0110011
    * funct3 for `add`: 000
    * funct7 for `add`: 0000000
    * rd: 00110(r6)
    * rs1: 00001(r1) 
    * rs2: 00010(r2)

    The full 32 bits instruction is `0000000 00001 00010 000 00110 0110011`
    
- **<mark>SLL r15, r1, r2</mark>**  
    The SLL (Shift Left Logical) is R-Type instruction. The base format is `sll rd, rs1, rs2`. It shifts the value stored in rs1 left by the number of bit positions specified in rs2, and stores the result in rd. So, in the above instruction:

    * opcode for `sll`: 0110011
    * funct3 for `sll`: 001
    * funct7 for `sll`: 0000000
    * rd: 01111 (r15)
    * rs1: 00001 (r1)
    * rs2: 00010 (r2)

The full 32 bits instruction is `0000000 00010 00001 001 01111 0110011`.  

- **<mark>SUB r7, r1, r2</mark>**  
    The SUB instruction is R-Type instruction. The base format is `sub rd, rs1, rs2`. It subtracts the value stored in `rs2` from the value stored in `rs1`, and stores the result in `rd`. So, in the above instruction:

    * opcode for `sub`: 0110011
    * funct3 for `sub`: 000
    * funct7 for `sub`: 0010000
    * rd: 00111 (r7)
    * rs1: 00001 (r1)
    * rs2: 00010 (r2)

The full 32 bits instruction is `0010000 00010 00001 000 00111 0110011`.  

- **<mark>AND r8, r1, r3</mark>**  
    The AND is R-Type instruction. The base format is `and rd, rs1, rs2`. It performs a bitwise AND operation on the values stored in `rs1` and `rs2`, and stores the result in `rd`. So, in the above instruction:

    * opcode for and: 0110011
    * funct3 for and: 111
    * funct7 for and: 0000000
    * rd: 01000
    * rs1: 00001
    * rs2: 00011  
    
    The full 32 bits instruction is `0000000 00011 00001 111 01000 0110011`.

- **<mark>OR r9, r2, r5</mark>**  
    The OR is R-Type instruction. The base format is `or rd, rs1, rs2`. It performs a bitwise OR operation on the values stored in `rs1` and `rs2`, and stores the result in `rd`. So, in the above instruction:

    * opcode for `or`: 0110011
    * funct3 for `or`: 110
    * funct7 for `or`: 0000000
    * rd: 01001
    * rs1: 00010
    * rs2: 00101

The full 32 bits instruction is `0000000 00101 00010 110 01001 0110011`  

- **<mark>XOR r10, r1, r4</mark>**  
    The XOR is R-Type instruction. The base format is `xor rd, rs1, rs2`. It performs a bitwise XOR operation on the values stored in `rs1` and `rs2`, and stores the result in `rd`. So, in the above instruction:

    * opcode for `xor`: 0110011
    * funct3 for `xor`: 100
    * funct7 for `xor`: 0000000
    * rd: 01010
    * rs1: 00001
    * rs2: 00100

The full 32 bits instruction is `0000000 00100 00001 100 01010 0110011`  

- **<mark>SLT r11, r2, r4</mark>**  
    The SLT (Set Less Than) is R-Type instruction. The base format is `slt rd, rs1, rs2`. It sets `rd` to 1 if the value in `rs1` is less than the value in `rs2`, otherwise it sets `rd` to 0. So, in the above instruction:

    * opcode for `slt`: 0110011
    * funct3 for `slt`: 010
    * funct7 for `slt`: 0000000
    * rd: 01011
    * rs1: 00010
    * rs2: 00100

The full 32 bits instruction is `0000000 00100 00010 010 01011 0110011`  

- **<mark>ADDI r12, r4, 5</mark>**  
    The ADDI (Add Immediate) is an I-Type instruction. The base format is `addi rd, rs1, imm`. It adds the immediate value `imm` to the value in `rs1` and stores the result in `rd`. So, in the above instruction:

    * opcode for `addi`: 0010011
    * funct3 for `addi`: 000
    * imm (immediate): 000000000101 (12-bit immediate for the value 5)
    * rd: 01100
    * rs1: 00100

The full 32 bits instruction is `000000000101 00100 000 01100 0010011`  

- **<mark>SW r3, r1, 2</mark>**  
    The SW (Store Word) is S-Type instruction. The base format is `sw rs2, imm(rs1)`. It stores the value in `rs2` at the memory address obtained by adding the immediate value `imm` to the value in `rs1`. So, in the above instruction:

* opcode for `sw`: 0100011
* funct3 for `sw`: 010
* imm (immediate): 000000000010 (12-bit immediate for the value 2)
* rs1: 00001
* rs2: 00011

The 12-bit immediate value is split into two parts:
- imm[11:5] (7 bits) = 0000000
- imm[4:0] (5 bits) = 00010

The full 32 bits instruction is `0000000 00011 00001 010 00010 0100011`  

- **<mark>SRL r16, r14, r2</mark>**  
    The SRL (Shift Right Logical) is R-Type instruction. The base format is `srl rd, rs1, rs2`. It performs a logical right shift on the value in `rs1` by the number of positions specified in `rs2` and stores the result in `rd`. So, in the above instruction:

* opcode for `srl`: 0110011
* funct3 for `srl`: 101
* funct7 for `srl`: 0000000
* rd: 10000 (r16)
* rs1: 01110 (r14)
* rs2: 00010 (r2)

The full 32 bits instruction is `0000000 00010 01110 101 10000 0110011`  

- **<mark>BNE r0, r1, 20</mark>**  
    The BNE (Branch if Not Equal) is a B-Type instruction. The base format is `bne rs1, rs2, imm`. It branches to the address offset by `imm` from the current PC if the values in `rs1` and `rs2` are not equal. So, in the above instruction:

    * opcode for `bne`: 1100011
    * funct3 for `bne`: 001
    * imm (immediate): 20 (which is 0b000000001010 in binary)
    * rs1: 00000 (r0)
    * rs2: 00001 (r1)

Given `imm = 20` (decimal) which is `000000001010` (binary), the 12-bit immediate value is split into the following parts for B-Type instructions:
- imm[12] = 0
- imm[10:5] = 000010
- imm[4:1] = 1010
- imm[11] = 0

The full 32 bits instruction is `0000000 00001 00000 001 10100 1100011`.

- **<mark>BEQ r0, r0, 15</mark>**  
    The BEQ (Branch if Equal) is B-Type instruction. The base format is `beq rs1, rs2, imm`. It branches to the address offset by `imm` from the current PC if the values in `rs1` and `rs2` are equal. So, in the above instruction:

    * opcode for `beq`: 1100011
    * funct3 for `beq`: 000
    * imm (immediate): 15 (which is 0b0000000001111 in binary)
    * rs1: 00000 (r0)
    * rs2: 00000 (r0)

Given `imm = 15` (decimal) which is `0000000001111` (binary), the 13-bit immediate value is split into the following parts for B-Type instructions:
- imm[12] = 0
- imm[10:5] = 000000
- imm[4:1] = 1111
- imm[11] = 0

The full 32 bits instruction is `0000000 00000 00000 000 01111 1100011`.  

- **<mark>LW r13, r1, 2</mark>**  
    LW (Load Word) is I-Type instruction. The base format is `lw rd, offset(rs1)`. It loads a 32-bit word from memory, where the memory address is calculated by adding the `offset` to the value in `rs1`, and stores it in `rd`. So, in the above instruction:

    * opcode for `lw`: 0000011
    * funct3 for `lw`: 010
    * imm (immediate): 2 (which is 0000000000010 in binary)
    * rd: 01101 (r13)
    * rs1: 00001 (r1)

The full 32 bits instruction is `000000000010 00001 010 01101 0000011`.
</details>

<br>

<details>
<summary><mark>Task 3</mark>: To run functional simulation using iverilog and analyse the output using gtkwave</summary>

## Task 3

To emulate risc v architecture and test the instructions from Task 2, we will use the verilog code from https://github.com/vinayrayapati/rv32i.git

First we will clone the repository to our local drive using `git clone https://github.com/vinayrayapati/rv32i.git`

Then we will cd to the rv32i directory `cd ./rv32i`

We can see in the <mark>iiitb_rv32i.v</mark> file that the instructions are coded in the verilog file.  

![coded_instructions](./Task%203/coded_instructionspng.png)  

Comparing it to the 32 bits binary codes obatained for the same instructions, we observe differences. For the instruction `add r6 r1 r2`, we got `0000000 00001 00010 000 00110 0110011`. Coverting it to hex, which is `32'h00110333` but in the verilog code, it is coded to `32'h02208300`.  

|                     | CODED INSTRUCTIONS | RISC V GNU COMPILER |
|---------------------|--------------------|---------------------|
| ADD r6, r2, r1      |  32'h02208300      |  32'h00110333  |
| SUB r7, r1, r2      |  32'h02209380      |  32'h202083B3  |
| AND r8, r1, r3      |  32'h0230a400      |  32'h0030F433  |
| OR r9, r2, r5       |  32'h02513480      |  32'h005164B3  |
| XOR r10, r1, r4     |  32'h0240c500      |  32'h0040C533  |
| SLT r11, r2, r4     |  32'h02415580      |  32'h004125B3  |
| ADDI r12, r4, 5     |  32'h00520600      |  32'h00520613  |
| SW r3, r1, 2        |  32'h00209181      |  32'h0030A123  |
| SRL r16, r14, r2    |  32'h00271803      |  32'h00275833  |
| BNE r0, r1, 20      |  32'h01409002      |  32'h00101A63  |
| BEQ r0, r0, 15      |  32'h00f00002      |  32'h000007E3  |
| LW r13, r1, 2       |  32'h00208681      |  32'h0020A683  |
| SLL r15, r1, r2     |  32'h00208783      |  32'h002097B3  |  

<br>  

To analyse the output in gtkwave, we use the command  `iverilog -o iiitb_rv32i iiitb_rv32i.v iiitb_rv32i_tb.v` which compiles the codes for iiitb_rv32i.v

![iverilogterminal](./Task%203/VirtualBox_vsdworkshop_31_05_2024_16_29_39.png)

`./iiitb_rv32i` runs the simulation using the compiled codes.

`gtkwave iiitb_rv32i.vcd`. This command generates a vcd file which contains the values from the simulation which is then opened in gtkwave where we can analyse the output waveforms.  

### Analysing the outputs in GTKWAVE

### <mark>add r6, r2, r1</mark>

![add](./Task%203/add.png)  

Here the first waveform is the clock. 2nd waveform is the instruction code in hex fetched from memory during the execution phase, hence the inputs of the instructions in reg A and reg B5 precedes the output and the instruction code waveforms in the snapshot. The 3rd and 4th waveforms are the input registers and the 5th wavefoem is the output of the operation.  

Similarly, we analyse all the instructions executed sequentially.  

### <mark>sub r7, r1, r2</mark>  

![sub](./Task%203/sub.png)

### <mark>and r8, r1, r3</mark>

![and](./Task%203/and.png)  

### <mark>or r9, r2, r5</mark>  

![or](./Task%203/or.png)  

### <mark>xor r10, r1, r4</mark>  

![or](./Task%203/xor.png)  

### <mark>slt r11, r2, r4</mark>  

![slt](./Task%203/slt.png)  

### <mark>addi r12, r4, 5</mark>  

![addi](./Task%203/addi.png)  

### <mark>sw r3, r1, 2</mark>  

![sw](./Task%203/sw.png)  

### <mark>beq r0, r0, 15</mark>

![sw](./Task%203/beq.png)  

### <mark>lw r13, r1, 2</mark>  

![lw](./Task%203/lw.png)

</details>  

<br>


## Project  

<details><summary><mark>Task 4</mark>: Project Overview</summary>  

## Task 4  

### 9's Complementer 

This project aims to design and implement a 9's Complementer circuit using VSD Squadron mini, a Seven segment Display to display output and switches to give input. The input will be given in BCD format using 4 switches. 

<mark>BCD (Binary coded Decimal)</mark> is form of decimal representation using binary numbers. Each decimal digit is grouped in 4 binary bits, or a nibble (half a byte) represents a decimal digit. For example, to represent <mark>7</mark> and <mark>17</mark> in BCD, it is written as `0111` and `0001 0111` respectively.  

<mark>9's complement</mark> of any decimal number m is givent by <mark>(9's complement = 9-m)</mark>. For example, 9's complement of 7 and 17 are `9-7=2` and `99-17=82` respectively.

<mark>7 segment display</mark> is made up of 7 led segments which are arranged in a 8 shape and any decimal number from 0 to 9 can be dislplayed by turning ON and OFF each individual LEDs.  

![7segdisp](./Task%204/seven_seg_disp.png)

### Components Required  

1. VSD Squadron mini
2. Seven Segment Display
3. Switches
4. Resistors
5. Breadboard
6. Jumper wires  

### Pin Connections  

|  Components         | VSD Squardron mini |
|---------------------|:------------------:|
| Switch 0            |  PC0      |
| Switch 1            |  PC1      |
| Switch 2            |  PC2      |
| Switch 3            |  PC3      |
| 7 segment LED A     |  PD0      |
| 7 segment LED B     |  PD1      |
| 7 segment LED C     |  PD2      |
| 7 segment LED D     |  PD3      |
| 7 segment LED E     |  PD4      |
| 7 segment LED F     |  PD5      |
| 7 segment LED G     |  PD6      |  

<br>  


### Working Code  

```c
#include <ch32v00x.h>
#include <stdio.h>

// Defining individual input pins for BCD (Port D)
#define BCD_PIN_0 GPIO_Pin_2
#define BCD_PIN_1 GPIO_Pin_3
#define BCD_PIN_2 GPIO_Pin_4
#define BCD_PIN_3 GPIO_Pin_5

// Defining segment pins for the 7-segment display (Port C)
#define SEG_A GPIO_Pin_0
#define SEG_B GPIO_Pin_1
#define SEG_C GPIO_Pin_2
#define SEG_D GPIO_Pin_3
#define SEG_E GPIO_Pin_4
#define SEG_F GPIO_Pin_5
#define SEG_G GPIO_Pin_6
#define SEG_DP GPIO_Pin_7

#define ALL_SEGMENTS (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP)

// Defining LED combination for each digit
#define NUM_0 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define NUM_1 (SEG_B | SEG_C)
#define NUM_2 (SEG_A | SEG_B | SEG_D | SEG_E | SEG_G)
#define NUM_3 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)
#define NUM_4 (SEG_B | SEG_C | SEG_F | SEG_G)
#define NUM_5 (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)
#define NUM_6 (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define NUM_7 (SEG_A | SEG_B | SEG_C)
#define NUM_8 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define NUM_9 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)
#define DOT   (SEG_DP)

//void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
//void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void Delay_Init(void);
void Delay_Ms(uint32_t n);

//initializing output pins
void GPIO_Init_Segment(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ALL_SEGMENTS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
} 

//initializing input pins
void GPIO_Init_BCD_Input(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = BCD_PIN_0 | BCD_PIN_1 | BCD_PIN_2 | BCD_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-up
    GPIO_Init(GPIOD, &GPIO_InitStructure);
} 

//assigning numbers to each digit given in input
void display_digit(uint8_t digit) {
    uint16_t segment_pins = 0;

    switch (digit) {
        case 0: segment_pins = NUM_0; 
        break;
        case 1: segment_pins = NUM_1; 
        break;
        case 2: segment_pins = NUM_2; 
        break;
        case 3: segment_pins = NUM_3; 
        break;
        case 4: segment_pins = NUM_4; 
        break;
        case 5: segment_pins = NUM_5; 
        break;
        case 6: segment_pins = NUM_6; 
        break;
        case 7: segment_pins = NUM_7; 
        break;
        case 8: segment_pins = NUM_8; 
        break;
        case 9: segment_pins = NUM_9; 
        break;
        default: segment_pins = NUM_0; 
        break;
    }

    GPIO_ResetBits(GPIOC, ALL_SEGMENTS);
    GPIO_SetBits(GPIOC, segment_pins);
}

//Display Dot when invalid BCD code is entered
void display_dot(void) {
    GPIO_ResetBits(GPIOC, ALL_SEGMENTS);
    GPIO_SetBits(GPIOC, SEG_DP);
}


//main code
int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
    GPIO_Init_Segment();
    GPIO_Init_BCD_Input();
    Delay_Init();


    //Fetch input from the GPIO pins
    uint8_t read_BCD(void) {
        uint8_t bcd_value = 0;
        if (GPIO_ReadInputDataBit(GPIOD, BCD_PIN_0)) bcd_value |= 0x01;
        if (GPIO_ReadInputDataBit(GPIOD, BCD_PIN_1)) bcd_value |= 0x02;
        if (GPIO_ReadInputDataBit(GPIOD, BCD_PIN_2)) bcd_value |= 0x04;
        if (GPIO_ReadInputDataBit(GPIOD, BCD_PIN_3)) bcd_value |= 0x08;
        return bcd_value;
    }

    uint8_t calculate_nines_complement(uint8_t bcd) {
        if (bcd > 9) {
            return 0xFF; // if greater than 9, invalid BCD code
        }
        return 9 - bcd; //9's complement
    }


    //while loop to read input and calculate output continuously
    while (1) {
        uint8_t bcd = read_BCD();
        uint8_t complement = calculate_nines_complement(bcd);

        if (complement == 0xFF) {
            display_dot(); //function call to display dot when invalid BCD code is entered
        } else {
            display_digit(complement); //function call to display 9's complement
        }

        Delay_Ms(500); //adding delay to avoid rapid polling
    }

    return 0;
}


```  

### Project Video   

<video src="https://youtu.be/3DUqD5rOVUM" width="560" height="315"/>

# Under Construction...


</details>