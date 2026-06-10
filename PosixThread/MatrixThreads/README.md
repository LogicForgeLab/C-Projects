# Matrix Multithreaded Analysis (C / pthread)

## Description
This project creates an N x N matrix and performs multiple operations using POSIX threads (pthreads). Each thread handles a separate task concurrently.# Matrix Multithreaded Analysis (C / pthread)

## Description
This project creates an N x N matrix and performs multiple operations using POSIX threads (pthreads). Each thread handles a separate task concurrently.

## Functionalities
- Finds maximum value in matrix
- Finds minimum value in matrix
- Prints main diagonal
- Prints secondary diagonal
- Calculates average of all elements

## How It Works
1. User inputs matrix size (N)
2. Program allocates dynamic NxN matrix
3. User fills matrix elements
4. 4 threads are created:
   - Max value thread
   - Min value thread
   - Diagonal printing thread
   - Average calculation thread
5. Threads execute in parallel
6. Results are printed
7. Memory is freed at the end

## Compilation

gcc matrix_threads.c -o matrix -pthread