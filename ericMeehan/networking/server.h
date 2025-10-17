// This block is for the compiler, not run-time, it reads this as "if server_h not yet 
// defined", define it to be used as a helper file. Prevents duplications
#ifndef Server_h
#define Server_h


#include <sys/socket.h>
#include <netinet/in.h>


struct Server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    // Socket
    int socket;

    // Member function that launches the server, takes in no param's
    void (*launch)(struct Server *server);
};


// Constructor, creates the server object
struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server *server));



#endif /*End Server_h*/