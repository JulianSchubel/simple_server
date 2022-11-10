#ifndef MTHREAD_SERVER_SOCKET_UTILITIS_H
#define MTHREAD_SERVER_SOCKET_UTILITIS_H

/* communication_domain: protocol family to be used for communication */
enum communication_domain {
    IPv4=AF_INET,   /* IP protocol v4 */
    IPv6=AF_INET6,  /* IP protocol v6 */
    CAN=AF_CAN      /* Controller Area Network: automotive bus protocol */
};

/* enum providing typical protocol binding to connection types */
enum communication_type {
    TCP=SOCK_STREAM,    /* sequenced, reliable, two-way, connection-based byte stream */
    UDP=SOCK_DGRAM,     /* connectionless, unreliable messages of a fixed maximum length */
    RAW=SOCK_RAW        /* raw network protocol access */
};

/* print_domain: print the communication domain */
void print_comm_domain(enum communication_domain);
/* handle_error: wrapper around perror() */
void handle_error(const char * msg);
/* check_socket: checks whether a socket file descriptor was returned successfully from socket() */
void check_socket(int socket_file_descriptor);
/* check_binding: check that the binding of a socket to a name (address) via bind() was successful, else calls perror() and exits */
void check_binding(int bind_return_value);
/* check_listen: check that a socket was set successfully as a passive socket (listener) via listen(), else calls perror() and exits */
void check_listen(int listen_return_value);
/* get_int_addr_type: determines whether the address type is IPv4 (AF_INET) or IPv6 (AF_INET6) */
void * get_in_addr_type(struct sockaddr * address);

void * get_in_addr_type(struct sockaddr * address)
{
    if( address->sa_family == AF_INET )
    {
        //Is Ipv4 internet address
        return &( ((struct sockaddr_in *)address)->sin_addr );
    }
    //Is IPv6 internet address
    return &( ((struct sockaddr_in6 *)address)->sin6_addr );
}

/* print_domain: outputs the integer value for the enumerated symbolic constants from sys/socket.h header */
void print_comm_domain(enum communication_domain domain)
{
    switch (domain) {
        case IPv4:
            printf("Communication domain: IPv4\n");
            break;
        case IPv6:
            printf("Communication domain: IPv6\n");
            break;
        case CAN:
            printf("Communication domain: Controller Area Network (automotive bus protocol)\n");
            break;
        default:
            printf("Unrecognized communication domain\n");
            break;
    }
}

/* check_socket: checks if socket() returned successfully, else calls perror() and exits */
void check_socket(int socket_file_descriptor) 
{
    if(socket_file_descriptor < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }
}

/* check_binding: check that the binding of a socket to a name (address) via bind() was successful, else calls perror() and exits */
void check_binding(int bind_return_value)
{
    if (bind_return_value < 0) {
        perror("Failed to bind socket to address");
        exit(EXIT_FAILURE);
    }
}

/* check_listen: check that a socket was set successfully as a passive socket (listener) via listen(), else calls perror() and exits */
void check_listen(int listen_return_value) 
{
    if(listen_return_value < 0) {
        perror("Failed to set socket as passive listener");
        exit(EXIT_FAILURE);
    }
}

#endif //MTHREAD_SERVER_SOCKET_UTILITIS_H
