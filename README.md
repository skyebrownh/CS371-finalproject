# CS371 Final Project

A console-based client-server application that implements a simplified chat application using socket programming written in C++.

***Background:***
- There are two main files required to run this application: `server.cpp` and `client.cpp`. These files must be run independently of each other as these two programs are meant to interact with each other. 
- `server.cpp`:
  - Implements the server functionality of this application
  - Waits for a connection from a client on a specific port, then begins exchanging chat messages until the client terminates the connection
  - Prints the proper error message to the console if an error occurs *server-side* and exits the program with a non-zero exit code
- `client.cpp`:
  - Implements the client functionality of this application
  - Establishes a connection with a server on a specific host and port, then begins exchanging chat messages until *'!quit'* is sent to the server to terminate the connection
  - Prints the proper error message to the console if an error occurs *client-side* and exits the program with a non-zero exit code
- `server-helpers.h server-helpers.cpp client-helpers.h client-helpers.cpp`:
  - Implements helper functions used within main files
  - Header files contain function prototypes for their respective implementations
  
**Note:** This application allows for connections to occur over a number of networks (not just localhost). The client provides a hostname and port number at runtime so that this application is not just restricted to a single network. As long as the client hostname and port matches the server's hostname and port, the application should run correctly.

***How it works:***
1. Unzip the source code *(class submission only)* or clone this project
2. Compile both source files
  - `g++ -o server server.cpp`
  - `g++ -o client client.cpp`
3. Run each program indepently to interact with each other
  - `./server <port>`
  - `./client <hostname> <port>`
4. Chat away!
