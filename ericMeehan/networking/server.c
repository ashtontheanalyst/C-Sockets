#include "server.h"
#include <stdio.h>
#include <stdlib.h>

// Define the server constructor (function prototype), creates a Server object and returns it
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server *server)) {
    
    struct Server server;

    // Set object parameters equal to the ones passed in
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;           // This is how many clients are waiting in line to connect


    // Define the address struct
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);                  // Convert the integer port to network port (Big/Little Endian)
    server.address.sin_addr.s_addr = htonl(interface);      // Same but for interface


    // Create a socket
    server.socket = socket(domain, service, protocol);
    if (server.socket == 0) {
        perror("Failed to connect socket...\n");
        exit(1);    // Exit the program with an error
    }


    // Bind the socket to the network
    if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0) {
        perror("Failed to bind socket...\n");
        exit(1);
    }


    // Tell the server to listen on the specified port
    if ((listen(server.socket, server.backlog)) < 0) {
        perror("Failed to start listening...\n");
        exit(1);
    }


    // Define the launch function
    server.launch = launch;

    return server;
}