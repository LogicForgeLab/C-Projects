Reverse String Client-Server Project (TCP)

Project Description

This is a simple client-server application written in C using TCP sockets.
The client sends a string to the server, and the server responds with the reversed version of that string.

---

How It Works

1. Server starts and listens on a specific port (8080).
2. Client connects to the server.
3. Client sends a string.
4. Server receives the string, reverses it, and sends it back.
5. Client prints the reversed string.

---

Technologies Used

* C programming language
* TCP sockets (AF_INET, SOCK_STREAM)
* Linux system calls (socket, bind, listen, accept, send, recv)

---

Project Structure

ReverseStringTCP/
│
├── server.c   # TCP server code
├── client.c   # TCP client code
└── README.md  # Project documentation

---

How to Compile

Compile server:

gcc server.c -o server

Compile client:

gcc client.c -o client

---

How to Run

Step 1: Run server


./server

Step 2: Run client (in another terminal)

./client

---

Example

Client input:

hello world

Server response:

dlrow olleh

---

Notes

* Server runs on 127.0.0.1:8080
* Each connection is handled once (stateless design)
* Connection closes after response

---

Author

Simple TCP project for learning socket programming in C.
