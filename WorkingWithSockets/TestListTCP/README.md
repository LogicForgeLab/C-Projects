# TCP Multi-Client Exam System (C / Socket Programming)

## Overview
This project is a TCP-based client-server exam system written in C.  
The server stores a question database in a file and supports multiple clients simultaneously using POSIX threads (pthread).

Each client receives 5 random questions, submits answers, and receives a final score.

## Features

- Multi-client support using pthread
- Questions loaded from external file (question.txt)
- Random selection of questions per client
- Real-time question and answer communication
- Automatic scoring system
- Final result sent to client
- Stateless TCP communication model

## System Architecture

### Server
- Loads questions from question.txt
- Listens on TCP port 8080
- Accepts multiple clients
- Sends questions one by one
- Receives answers and calculates score
- Sends final result

### Client
- Connects to server
- Receives questions
- Sends answers (1–4)
- Displays final score

## Question File Format (question.txt)

question|option1|option2|option3|option4|correct_answer

Example:
2 + 2 = ?|3|4|5|6|2
5 * 3 = ?|10|15|20|25|2

correct_answer represents the correct option number (1–4).

## How to Compile

gcc server.c -o server -lpthread
gcc client.c -o client

## How to Run

./server

./client

## Workflow

1. Client connects to server  
2. Server sends a random question  
3. Client answers (1–4)  
4. Process repeats for 5 questions  
5. Server calculates score  
6. Final result is sent to client  

## Example Output

Client receives:
2 + 2 = ?
1)3
2)4
3)5
4)6

Your answer (1-4): 2

Final result:
Test finished! Score: 4/5

## Technologies Used

- C Programming Language
- TCP Sockets (AF_INET, SOCK_STREAM)
- POSIX Threads (pthread)
- File I/O
- Linux System Programming

## Notes

- Maximum 100 questions supported
- Each client receives 5 random questions
- Server must be started before client
- Works on localhost (127.0.0.1)

## Possible Improvements

- Timer per question
- User authentication system
- Leaderboard (top scores saved to file)
- JSON-based communication protocol
- Encryption and anti-cheat system
- GUI client application