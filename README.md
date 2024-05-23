# VSDSquadron mini Internship Cohort 20th May 2024

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

