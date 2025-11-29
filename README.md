# Arbitrary-Precision-Calculator-APC
A modular C program that performs arithmetic operations on extremely large integers using doubly linked lists. Supports addition, subtraction, multiplication, division, modulus, and square operations without overflow.

---

## 🔎 OVERVIEW
The APC (Arbitrary Precision Calculator) handles numbers far larger than the limits of built-in C data types.  
Each number is stored as a **doubly linked list**, where each node contains a single digit.  
This enables precise computation of huge values using manual arithmetic logic.

The program works through a **CLI (Command Line Interface)** in the format: 
./a.out number1 operator number2

Operators supported:
- `+`  Addition  
- `-`  Subtraction  
- `*`  Multiplication  
- `/`  Division  
- `^`  Square  
- `%`  Modulus  

---

## ✨ FEATURES
- Handles numbers of any size (as long as memory allows)
- Uses doubly linked lists for digit storage
- Supports positive and negative integers
- Implements manual arithmetic (same as pen-and-paper)
- Removes leading zeros automatically

---

## 🧩 CONCEPTS USED
- Doubly Linked Lists  
- Dynamic memory allocation  
- Linked-list based comparison, subtraction, addition  
- Removal of leading zeros  
- Long multiplication  
- Long division  
- Modulus logic using repeated subtraction  
- Input validation  
- Makefile-based build system  

---

## 📌 CONCLUSION
The Arbitrary Precision Calculator demonstrates a strong command of data structures, memory management, algorithmic thinking, and low-level C design. It replicates how real big-number libraries operate internally and showcases your understanding of linked list manipulation for real-world applications.
