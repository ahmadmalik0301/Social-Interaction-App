# Social Connecting App

## Author
Muhammad Ahmad (F2022266093)

## University
University of Management and Technology

## Department
School of Science and Technology (SST)

## Degree
Bachelor of Computer Science

## Email
- mahmadmalik0301@gmail.com

## Summary
This project is a Social Connecting App with various functionalities, including a user-friendly interface, managing multiple aspects such as posts, private chats, group chats, and a friend system. It lacks an undo functionality but incorporates features like a linked list for user connections, a graph for friend connections, and a tree for post and reply organization. The program is implemented in C++ using Visual Studio Code with the latest compiler.

## Sequential Implementation
The program utilizes multiple custom header files for various functionalities, including managing accounts, chats, group chats, posts, and the friend system. The main program uses data structures like linked lists, graphs, and trees. A `mainManager()` function controls user interactions, ensuring a clean user experience.

## Modules

### User Account
The `accounts.h` header file contains a class named `userAccount` with functions to manipulate user data, ensure unique usernames, and handle login functionality.

### Private Chat
Private chat functionality is implemented through the `chat.h` header file, using a class named `chatBox` to store messages between users.

### Group Chat
Similar to private chat, group chat functionality is implemented through the `groupChat.h` header file, with each chatbox having a unique ID and a vector of participants.

### Posting Implementation
The posting system is represented by the `post.h` header file, using a tree structure to organize posts and replies. Functions include adding replies, finding posts by ID, printing the entire tree, and deleting posts.

### Friend System
The friend system is implemented through the `friendSystem.h` header file, using a class named `friendGraph` with functions to send, receive, and delete friend requests.

