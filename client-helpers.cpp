#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
using namespace std;

// error display function
void error(const char *msg) {
    perror(msg);
    exit(1);
}

// client chat function
const int MAX_BUFFER_SIZE = 256;

void chat(int sock) {
  char buffer[MAX_BUFFER_SIZE]; // max buffer size for read-in
  int n;

  while (1) {
    cout << "Waiting for server..." << endl;
    // read from server
    bzero(buffer, MAX_BUFFER_SIZE);
    n = read(sock, buffer, sizeof(buffer));
    if (n < 0) {
        error("Error reading from socket\n");
    }
    printf("Server: %s\n", buffer);

    // write to server
    cout << "Your message ('!quit' to end session): ";
    bzero(buffer, MAX_BUFFER_SIZE);
    fgets(buffer, sizeof(buffer), stdin);
    n = write(sock, buffer, strlen(buffer));
    if (n < 0) {
        error("Error writing to socket\n");
    }
    else if (strncmp("!quit", buffer, 5) == 0) {
        cout << "Closing connection..." << endl;
        exit(0);
    }
    cout << "Message sent to server" << endl;
  }
}
