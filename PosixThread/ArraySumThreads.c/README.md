# Array Sum Using Multiple Threads

## Description

This program demonstrates multithreaded programming in C using POSIX threads (`pthread`). The array is divided into several parts, and each part is processed by a separate thread. Every thread calculates the sum of its assigned segment and safely adds the result to a shared global variable using a mutex.

## Features

* Dynamic array allocation
* Multiple thread creation
* Array partitioning between threads
* Mutex synchronization
* Global sum calculation

## Compilation

gcc array_sum_threads.c -o array_sum_threads -lpthread


## Execution

./array_sum_threads


## Example

Input:
Enter Array size
8

Enter array elements
1 2 3 4 5 6 7 8


Output:

Total sum = 36


## How It Works

1. The user enters the array size and elements.
2. The array is divided into equal parts.
3. A thread is created for each part.
4. Each thread computes the sum of its assigned elements.
5. The partial sums are added to a global variable using a mutex.
6. After all threads finish, the total sum is displayed.

## Technologies Used

* C Programming Language
* POSIX Threads (pthread)
* Mutex Synchronization
* Dynamic Memory Allocation
