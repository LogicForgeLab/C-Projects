# Thread Mutex Increment

## Description

This program demonstrates the use of POSIX threads (`pthread`) and mutexes for synchronized access to a shared global variable. A global variable is initialized to `0`. Multiple threads are created, and each thread increments the global variable by `100`. A mutex is used to prevent race conditions and ensure that only one thread can modify the variable at a time.

## Compilation

gcc thread_mutex_increment.c -o thread_mutex_increment -lpthread


## Execution

./thread_mutex_increment


## Example Output

Final value: 1000


## How It Works

1. A global variable is initialized to `0`.
2. A mutex is created and initialized.
3. Multiple threads are spawned.
4. Each thread locks the mutex, adds `100` to the global variable, and unlocks the mutex.
5. The main thread waits for all threads to finish.
6. The final value of the global variable is printed.

## Key Concepts

- POSIX Threads (`pthread`)
- Mutex synchronization
- Shared resources
- Race condition prevention
- Multithreaded programming in C