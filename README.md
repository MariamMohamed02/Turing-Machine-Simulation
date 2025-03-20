# Universal Turing Machine Simulation  

##  **Description**  
The **Universal Turing Machine (UTM) Simulation** is a program written in **C** that simulates a Turing Machine, a fundamental model of computation. The program allows users to:  
- Define a **set of symbols** that the machine can process.  
- Specify **states and transition rules** for the machine.  
- Provide an **initial tape input** to be processed.  
- Observe the step-by-step execution of the Turing Machine as it **reads, writes, and moves the tape head**.  
- Receive a final output indicating **whether the input is accepted or rejected**.  

This project serves as a practical tool for learning how **Turing Machines** work and how they process computations through state transitions.  

---

## **How the Turing Machine Works**  
A Turing Machine operates with the following components:  
1. **Tape** – A sequence of symbols (characters) that can be read and modified.  
2. **Head Position** – A pointer that moves left (`l`) or right (`r`) on the tape.  
3. **States** – The machine operates through a **finite set of states** (`q0, q1, ...`).  
4. **Transition Rules** – Define how the machine moves between states based on the symbol it reads.  
5. **Halt Condition** – The machine **accepts (`y`) or rejects (`n`)** an input based on transition rules.



