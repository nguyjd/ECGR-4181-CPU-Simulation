# ECGR 4181 CPU Simulation
The CPU Simulation Project for ECGR 4181 at UNCC

<b>Project Members</b>
<ul>  
  <li>Jonathon Nguyen</li>
  <li>Jarrett Long</li>
</ul>

# Features

- 32-bit Words
- 32-bit Instruction
- Uses a master event system

# Instruction Set

The CPU is using the RISC-V instruction set.
It does not support any 64-bit instruction such as ADDW

This table is a subset of what is supported.
<table style="width:100%">
  <tr>
    <th>Instruction</th>
    <th>Meaning</th>
  </tr>
  <tr>
    <th colspan="2">Load/store Instruction</th>
  </tr>
  <tr>
    <th>LW</th>
    <th>Load a word from memory and store it into the registor</th>
  </tr>
  <tr>
    <th>SW</th>
    <th>Store a word from registor into a specific location in memory.</th>
  </tr>
    <tr>
    <th colspan="2">ALU Instruction</th>
  </tr>
  <tr>
    <th>ADD</th>
    <th>Add two words from the registor file and store back into the registor</th>
  </tr>
  <tr>
    <th>SUB</th>
    <th>Subtract two words from the registor file and store back into the registor</th>
  </tr>
  <tr>
    <th>DIV</th>
    <th>Divide two words from the registor file and store back into the registor</th>
  </tr>
  <tr>
    <th>MUL</th>
    <th>Multiply two words from the registor file and store back into the registor</th>
  </tr>
    <tr>
    <th colspan="2">Jump/Branch Instruction</th>
  </tr>
  <tr>
    <th>BEQ</th>
    <th>Branch by an offset if the words from the registor are equal.</th>
  </tr>
  <tr>
    <th>JAL</th>
    <th>Jump by an offset and store the PC+4 into the registor.</th>
  </tr>
  <tr>
    <th>JALR</th>
    <th>Jump by an offset that is given from the registor and store the PC+4 into the registor.</th>
  </tr>
</table>

# Diagram of the CPU
![The diagram of our CPU](https://github.com/nguyjd/ECGR-4181-CPU-Simulation/blob/main/Diagrams/Main%20Diagram.png)

# Links
- [Project Boards](https://github.com/nguyjd/ECGR-4181-CPU-Simulation/projects)
- [RISC-V Instruction Set](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
