# Third Largest Element Using Thread

## Description

This program demonstrates the use of POSIX Threads (pthread) in C. A thread is created to execute a function that receives an integer array and its size as arguments. The thread function finds the third largest distinct element in the array and returns the result to the main thread.

If the array does not contain three distinct values, an appropriate message is displayed.

## Features

* Dynamic array allocation
* User input for array elements
* Thread creation using `pthread_create()`
* Thread synchronization using `pthread_join()`
* Finding the third largest distinct element
* Proper memory management

## Compilation

gcc main.c -o main -lpthread


## Running

./main

## Example

Input:

Enter array size
5
Enter array elem: 1 -> 10
Enter array elem: 2 -> 50
Enter array elem: 3 -> 30
Enter array elem: 4 -> 20
Enter array elem: 5 -> 40
```

Output:

Third largest value is 30


## Author

Narek
