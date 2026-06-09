TCP File Transfer System

Description

This project implements a simple TCP File Transfer System in C using the client-server architecture.

The client sends a file name to the server. The server searches for the requested file, reads its contents, and sends the data back to the client. The client then displays the received file content on the terminal.

Features

* TCP socket communication
* File request by name
* Server-side file reading
* File content transfer
* Error handling for missing files
* Stateless client-server interaction


Project Structure

project/
├── server.c
├── client.c
├── README.md

Compilation

Compile the programs using GCC:


gcc server.c -o server
gcc client.c -o client


Running the Application

Start the server:


./server


In another terminal, start the client:


./client


Enter the file name when prompted:

Enter filename: test.txt

The client will receive and display the file contents sent by the server.

Example

Requested file:

test.txt

File content:

Hello World
TCP File Transfer Example

Output on client:

Hello World
TCP File Transfer Example

Technologies Used

* C Programming Language
* TCP/IP Sockets
* Linux System Calls
* GCC Compiler
