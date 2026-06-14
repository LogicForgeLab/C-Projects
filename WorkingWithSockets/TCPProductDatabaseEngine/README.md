# TCP Product Database Engine

## Overview

A simple client-server application that manages a product catalog over a TCP connection. The server stores products in a binary database file and processes commands sent by clients.

## Features

* Multi-threaded TCP server (`pthread`)
* Raw TCP communication
* Binary file database (`db.dat`)
* Thread-safe file access using mutexes
* Fixed-size product records
* Stateless request handling

## Product Structure

```c
typedef struct {
    char name[50];
} Product;
```

## Supported Commands

### Add Product

```text
POST apple
```

Response:

```text
ADDED
```

### Get Product

```text
GET apple
```

Response:

```text
apple
```

If not found:

```text
NOT FOUND
```

### Get All Products

```text
GET
```

Response:

```text
apple
banana
orange
```

## Build

```bash
gcc server.c -o server -pthread
gcc client.c -o client
```

## Run

Start the server:

```bash
./server
```

Start the client:

```bash
./client
```

Then enter a command such as:

```text
POST apple
GET apple
GET
```

## Technologies

* C
* POSIX Sockets
* TCP/IP
* Pthreads
* Binary File Storage
