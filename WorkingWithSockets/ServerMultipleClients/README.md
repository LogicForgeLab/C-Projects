# Multithreaded TCP Client-Server (C)

## Description
This project is a simple TCP client-server application written in C.  
The server supports multiple clients using multithreading (`pthread`).  
Clients can send messages to the server and receive responses.

---

## Features
- TCP socket communication
- Multithreaded server (pthread)
- Multiple client support
- Continuous message exchange
- Real-time communication

---

## How It Works
1. Server starts and listens on port `8080`
2. Client connects to the server
3. Client sends a message
4. Server receives message in a separate thread
5. Server sends response back to client
6. Client displays server response

---

## Project Structure
server.c  
client.c  

---

## Compilation

Server:

gcc server.c -o server -lpthread