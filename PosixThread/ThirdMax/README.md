# Third Largest Element (Multithreaded C Program)

## Description
This project is a simple C program that uses POSIX threads to find the third largest element in an integer array. The computation is performed in a separate thread.

## Features
- Uses pthread for multithreading
- Dynamically allocated array
- Finds the third largest unique element
- Handles invalid input (array size < 3)
- Memory cleanup included

## How It Works
1. User enters array size (minimum 3)
2. User inputs array elements
3. A separate thread processes the array
4. The thread finds the third largest element
5. Result is printed in main thread

## Compilation
gcc main.c -o program -pthread

## Run
./program

## Example
Enter array size
5
Enter array elem: 1 -> 10
Enter array elem: 2 -> 20
Enter array elem: 3 -> 30
Enter array elem: 4 -> 15
Enter array elem: 5 -> 25

Third largest value is 20