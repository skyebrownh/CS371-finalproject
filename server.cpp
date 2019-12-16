#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
using namespace std;

// helper function prototypes
#include "server-helpers.h"

int main(int argc, char const *argv[]) {
  // check if user provided port number
  if (argc < 2) {
    error("Error: no port provided\n");
  }
  else if (argc > 2) {
    error("Too many command-line arguments provided\n");
  }

  int port_no = atoi(argv[1]);
  int new_fd, client_size;
  struct sockaddr_in server_addr, client_addr; // sockaddr_in - structure containing internet address

  // create a socket - socket()
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    error("An error occurred trying to connect to the client. Exiting...\n");
  }
  cout << "Socket created" << endl;

  bzero((char*) &server_addr, sizeof(server_addr)); // set all values of buffer to 0
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port_no); // convert port_no to network byte order
  server_addr.sin_addr.s_addr = INADDR_ANY; // IP address of host

  // bind socket to an address (for Internet, address includes port number on host) - bind()
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    error("An error occurred trying to bind the socket.\n");
  }
  cout << "Bind complete" << endl;

  // listen for connections - listen()
  listen(server_fd, 5); // 5 - number of connections that can be waiting while the process is handling a particular connection

  // accept connections - accept()
  client_size = sizeof(client_addr);
  // loop allows for mulitple clients to connect to this server
  while (1) {
    cout << "Waiting for incoming connection..." << endl;
    // accept new client
    new_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_size);
    if (new_fd < 0) {
      error("An error occurred trying to accept the connection.\n");
    }
    cout << "Connection created with client" << endl;

    // start new child process for chatting with this client
    int pid = fork();
    if (pid < 0) {
      error("An error occurred trying to fork a new process.\n");
    }
    if (pid == 0) {
      close(server_fd);
      chat(new_fd);
      exit(0); // exit child process
    }
    else {
      close(new_fd);
      // wait for more client connections...
    }
  }
  return 0;
}

// Sources:
//--- https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
//--- https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
