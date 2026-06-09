# Multithreaded TCP Palindrome Checker

## Description
This project is a multithreaded client-server application written in C using TCP sockets and pthreads.

The client sends a string to the server, and the server checks whether the string is a palindrome and returns the result.

Each client connection is handled in a separate thread.

---

## Features
- TCP client-server communication
- Multithreaded server (pthread)
- Palindrome string validation
- Simple text-based protocol

---

## How it works
1. Server starts and listens on port `8080`
2. Client connects to the server
3. Client sends a string
4. Server checks if the string is a palindrome
5. Server sends response:
   - Polidrome` (if true)
   - Not polidrom` (if false)

---

## Compilation

### Server

gcc server.c -o server -lpthread