# Guess The Number - TCP Client/Server

## Description

A multithreaded TCP client-server application in C where the server generates a random number and the client tries to guess it.

The server responds with:
- "Too high"
- "Too low"
- "Success"

until the correct number is guessed.

## Files

- `server.c`
- `client.c`

## Compilation

gcc server.c -o server -lpthread
gcc client.c -o client

## Run

Server:

./server

Client:


./client


## Features

- TCP socket communication
- Multithreaded server
- Random number generation
- Multiple client support
- Guessing game