# Paradigms_1

## Control questions
### 1. What is structural programming paradigm?

Structural programming is a software development and design methodology that focuses on maintaining a consistent and logical structure in the writing of programs. It proposes that simple control structures like sequence, selection, and iteration should be utilized instead of unstructured ones such as “goto” statements. The ultimate goal of structural programming is to enhance the quality, clarity, and efficiency of software development by ensuring that the control flow is simple, which translates to predictability.

### 2. What is procedural programming paradigm?

Procedural programming organizes code into procedures, which have better modularity, reusability, and maintainability. It uses clear control structures and calls procedures to perform certain tasks, being the principle paradigm where other high-level programming languages are formed. Procedural programming is still broadly practiced, and it is the base of other more complicated paradigms.

### 3. Which primitive data types do you know? Key differences between them?
##### Here will be small descriptions from lecture about types and most important information:

boolean - (зберігання 1 byte) true/false meaning; 
char - зберігання символа
byte - робота одразу з байтами (byte b  = 0x11;)

Numbers:
unsigned (int/short/long - only non-negative numbers with different length
int - 4 byte hole numbers as + as -
int32_t - 32 bit
float - дві частини числа розділені комою (4 byte)
double - 8 byte 

### 4. Which segments does the process memory have?

|----------------------------|
|    Reserved Segment        |
|----------------------------|
|    Memory-Mapped Segment   |
|----------------------------|
|          Stack             | <- Growing downwards
|----------------------------|
|         (empty)            |
|----------------------------|
|           Heap             | <- Growing upwards
|----------------------------|
|    Uninitialized Data (BSS)|
|----------------------------|
|  Initialized Data Segment  |
|----------------------------|
|       Text Segment         |
|----------------------------|

### 5. What is the virtual memory space?

  - Each process has its own virtual address space, which is divided into pages.
  - Virtual addresses are mapped to physical addresses by the operating system using a mechanism called the page table.
  - An alternative or complementary method to paging, where memory is divided into variable-sized segments based on logical divisions, such as code, data, and stack segments.
  - Each segment is independently managed and can grow or shrink dynamically.

### 6. How to allocate the memory in each segment?

Allocating memory in both process memory and virtual memory space involves interacting with the operating system's memory management functions. These functions manage the allocation and deallocation of memory, both in physical RAM and virtual memory.
Allocating memory in process memory typically involves using standard library functions like malloc/free. When dealing with virtual memory, system-specific calls like VirtualAlloc/VirtualFree

### 7. How to reallocate the memory in case we don’t have enough space?

Using realloc or mmap.
1. Allocating a new, larger memory block.
2. Copying data from the old memory block to the new one.
3. Freeing the old memory block.

### 8. What is a runtime stack?

"the stack," is a region of a process's memory that is used for managing function calls and local variables during the execution of a program. It operates in a last-in, first-out (LIFO) manner, which means that the most recently pushed item is the first to be popped off.
Стек куди зберігається послідовне виконання програми та посилання на комірки куди треба переходити, а де залишати змінні "в очікуванні"
