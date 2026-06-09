# TCP Chat Application

A multi-threaded TCP chat application written in C. The project consists of a server and multiple clients that can communicate in real time through TCP sockets.

## Features

* Multi-client support
* Real-time messaging
* Multi-threaded server
* Concurrent send/receive operations
* TCP socket communication

## Build

gcc server.c -o server -lpthread
gcc client.c -o client -lpthread


## Run

Start the server:

./server

Start one or more clients:

./client

## Technologies

* C
* POSIX Sockets
* Pthreads

## Project Structure

server.c
client.c
README.md

