# Even-Odd Index Thread Program

## Description
This project demonstrates multithreading in C using POSIX threads (pthreads).  
The program creates two threads that work simultaneously:

- One thread prints elements at **even indices**
- The other thread prints elements at **odd indices**

A mutex and condition variable are used to synchronize the threads and ensure correct alternating execution.

## Features
- Dynamic array input from user
- Two threads working in parallel
- Synchronization using:
  - pthread_mutex
  - pthread_cond
- Controlled alternating output between threads

## How it works
1. User enters array size
2. User fills array elements
3. Two threads are created:
   - Thread 1 → even indices (0, 2, 4, ...)
   - Thread 2 → odd indices (1, 3, 5, ...)
4. Threads alternate using a shared `type` variable
5. Output is printed in correct order

## Compilation
gcc even_odd_threads.c -o program -pthread

## Run
./program

## Example

Input:
Enter Array size
6
Enter array elements:
1 2 3 4 5 6

Output:
1 2 3 4 5 6

(or)
even index: 1
odd index: 2
even index: 3
odd index: 4
even index: 5
odd index: 6

## File Structure
even_odd_threads/
├── even_odd_threads.c
└── README.md

## Author
Student project – POSIX Threads practice