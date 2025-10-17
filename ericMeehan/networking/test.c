#include <stdio.h>
#include <string.h>     // strlen()
#include <unistd.h>     // read(), write(), close()
#include "server.h"


// Launch function, param is
void launch(struct Server *server) {
    // We define the variables up here so they're not constantly re-made
    int address_length = sizeof(server->address);
    char *hello = "What's up nerd.";
    int new_socket;
    
    while (1) {
        printf("----- WAITING FOR CONNECTION -----\n");
    
        // accept() is a function from sys/socket.h, it accepts a new incoming client to the server
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        printf("Client Connected!\n");

        write(new_socket, hello, strlen(hello));
        printf("Message Sent...\n");

        close(new_socket);
        printf("Client Connection Closed\n\n");
    }
}



int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8090, 10, launch);
    server.launch(&server);
}