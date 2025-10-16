/* Simple Server
We create a socket (phone), bind it to a local port (connect it to the wall jack), 
listen for a client to call (open), accept the connection (pick up when a call comes in), 
send a message once they've connected (say hello), then close and exit (hangup)
*/ 


#include <stdio.h>          // printf, perror
#include <string.h>         // strlen, memset
#include <stdlib.h>         // exit
#include <unistd.h>         // close
#include <arpa/inet.h>      // socket structs, functions, etc


int main() {
    int server_fd;                                  // The listening phone
    int client_fd;                                  // The active call once picked up
    struct sockaddr_in server_addr;                 // The server's IP/port
    struct sockaddr_in client_addr;                 // Where the caller is IP/Port?
    socklen_t client_len = sizeof(client_addr);     // helper for accept()
    char buffer[1024] = {0};    


    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("server_fd = %d\n", server_fd);
    if (server_fd < 0) { perror("socket"); exit(1); }


    // Bind the server to port 3490
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(3490);
    printf("server_addr.sin_family = %d\n", server_addr.sin_family);
    printf("server_addr.sin_addr.s_addr = %d\n", server_addr.sin_addr.s_addr);
    printf("server_addr.sin_port = %d\n", server_addr.sin_port);
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind"); exit(1);
    }


    // Listen for a client
    if (listen(server_fd, 1) < 0) { perror("listen"); exit(1); }
    printf("Server is up/waiting on port 3490...\n");


    // Accept a connection
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    printf("client_fd = %d\n", client_fd);
    if (client_fd < 0) { perror("accept"); exit(1); }
    printf("Client connected!..\n");


    // Send a message
    char *msg = "Hello from the server!\n";
    send(client_fd, msg, strlen(msg), 0);


    // Close it all down
    close(client_fd);
    close(server_fd);
    return 0;
}