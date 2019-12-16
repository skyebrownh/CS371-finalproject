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

// server chat function
void chat(int sock) {
    // client has been successfully connected - send and receive data
    char buffer[256]; // max buffer size for read-in
    int n;
    while (1) {
      bzero(buffer, 256);
      n = 0;
      // send message to client
      cout << "Your message: " << endl;
      // read input and copy into buffer
      fgets(buffer, sizeof(buffer), stdin);
      n = write(sock, buffer, sizeof(buffer));
      if (n < 0) {
        error("An error occurred trying to write to the client.\n");
      }
      cout << "Message sent to client" << endl;

      // receive message from client
      cout << "Waiting for client..." << endl;
      bzero(buffer, 256);
      // read message from client and copy into buffer
      n = read(sock, buffer, sizeof(buffer));
      // read will block until client writes
      if (n < 0) {
        error("An error occurred trying to read from the client.\n");
      }
      else if (strncmp("!quit", buffer, 5) == 0) {
        cout << "Client ended session" << endl;
        exit(0);
      }
      // print client message
      printf("Client: %s\n", buffer);
    }
}
