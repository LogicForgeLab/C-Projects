# Prime Numbers using Multithreading (C / pthread)

## Description
This project is a simple C program that uses POSIX threads to generate and display all prime numbers up to a given range. One thread generates the prime numbers, and another thread prints them and frees the allocated memory.

## Features
- Uses pthread (multithreading)
- Dynamic memory allocation
- Prime number generation up to N
- Separate thread for printing and memory cleanup
- Synchronization using pthread_join

## How It Works
1. User enters a number (range N)
2. Thread 1 generates all prime numbers from 2 to N and stores them in a dynamic array
3. Thread 2 waits for Thread 1 to finish
4. Thread 2 prints the prime numbers
5. Thread 2 frees allocated memory

## Compilation
gcc dynamic_array.c -o program -pthread

## Run
./program

## Example
Enter array range: 20

Prime Numbers:
2 3 5 7 11 13 17 19

## Notes
- Input must be ≥ 2
- Memory is dynamically allocated and freed properly