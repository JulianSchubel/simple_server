#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>     /* close() */
#include <sys/socket.h> /* Internet protocol family: basic socket definitions */
#include <arpa/inet.h>  /* htons(); convert port numbers to big-endian (internet network byte order) */
#include <string.h>     /* strncat() */

/* THREADING */
#include <pthread.h>
//#include <sys/types.h>  /* predefined typedefs and structures: ip_addr_t, pthread_mutex_t etc. */

/* UTILITY FUNCTION PROTOTYPES AND DEFINITIONS */
#include "./include/socket_utilities.h"
#include "./include/file_io_utilities.h"
#include "./include/http_utilities.h"

/* SYMBOLIC CONSTANTS */
#define ADDRESS struct sockaddr /* convenience */
#define CONNECTION_QUEUE_LIMIT 5
#define MAX_METHOD_LENGTH 6 /* DELETE + '\0' */
/* Client address variables: IPv4 max 16 byte string representation "255.255.255.255\0", IPv6 46 byte string representation (IPv6 is 39 byte max but with IPv4 tunneling can go up to 45 and then 1 byte for null terminator) "nnnn:nnnn:nnnn:nnnn:nnnn:nnnn:nnnn:nnnn\0" (just IPv6), "nnnn:nnnn:nnnn:nnnn:nnnn:nnnn:nnnn:nnnn:255.255.255.255\0" with IPv4 tunneling */
#define MAX_CLIENT_ADDRESS_LENGTH 46
#define HTTP_HEADER_LENGTH 22
#define RESOURCE_BUFFER_LENGTH 1024
#define RESPONSE_BUFFER_LENGTH 2048
#define METHOD_TABLE_LEN 4

/* Initialize mutex */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *handle_connection(void *sfd);

/* handle_connection: create a new thread to handle the incoming request */
void *handle_connection(void *sfd) 
{
    char request[2048];
    read(*((int*)sfd), request, 2048);
    /* Get the request method */
    /* 6 is max method length + '\0'. I.e. "DELETE\0" */
    char * request_method = (char *)malloc(sizeof(char)*MAX_METHOD_LENGTH);
    char resource[RESPONSE_BUFFER_LENGTH];
    /* Parse the request method (http_utilities) */
    get_method(request, request_method, MAX_METHOD_LENGTH);
    /* Parse the requested resource (http_utilities) */
    get_resource(request, resource, RESOURCE_BUFFER_LENGTH);

    printf("Method: %s\n", request_method);
    printf("Resource: %s\n", resource);
    printf("Request: %s\n", request);    
    
    int method = lookup_method(request_method, method_table, METHOD_TABLE_LEN);

    switch (method)
    {
        case GET:
            /* Acquire the mutex */
            pthread_mutex_lock(&lock);

            if(!strcmp(resource, "/")) {
                strcpy(resource, "/index.html");
            }

            char file_path[100] = "./www";
            strcat(file_path, resource);

            /* Open the file named as resource */
            FILE * data = fopen(file_path, "r");
            if(!data) {
                data = fopen("./www/error.html", "r");
            }

            /* get the length of the file (file_io_utilities) */
            int data_length = get_flen(data);
            /* Allocate sufficient memory */
            char * response_body = malloc(sizeof(char)*data_length+1);
            /* Copy the response data to a buffer (file_io_utilities) */
            get_fdata(response_body, data, data_length);
            /* close the response data file */
            fclose(data);

            /* HTTP header */ 
            char response[RESPONSE_BUFFER_LENGTH] = "HTTP/1.1 200 OK\r\n\n";

            /* Need to concat our header and the response body into one string */
            strncat(response, response_body, (size_t)data_length);

            /* Send the response back to the client */
            send(*((int*)sfd), response, sizeof(response), 0);

            /* DEALLOCATE HEAP MEMORY */
            /* deallocate response buffer */
            free(response_body);

            /* Release the mutex */
            pthread_mutex_unlock(&lock);
            break;
        case POST:
            break;
        case PUT:
            break;
        case DELETE:
            break;
        default:
            break;
    }
    /* deallocate request method buffer */
    free(request_method);

    /* Close client socket */
    close(*((int*)sfd));
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Expected port number as argument\n");
        exit(EXIT_FAILURE);
    }
    const int PORT = atoi(argv[1]);
    /* create socket file descriptor */
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    check_socket(sfd);
    /* create the socket address structure */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    print_comm_domain(server_address.sin_family);
    /* bind the socket to the address */
    int bind_status = bind(sfd, (struct sockaddr*)&server_address, sizeof(server_address));
    check_binding(bind_status);
    /* set the socket as a passive socket */
    int listen_status = listen(sfd, CONNECTION_QUEUE_LIMIT);
    check_listen(listen_status);

    while(1) {
        pthread_t thread;
        int client_socket;
        char client_address_string[MAX_CLIENT_ADDRESS_LENGTH];
        socklen_t client_addr_string_len = sizeof(client_address_string);
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);
    
        /* Accept connection on the client socket. */
        /* If not storing address (server_socket, NULL, NULL); */
        client_socket = accept(sfd, (struct sockaddr *)&client_address, &client_addr_len);

        /* Convert client address from binary to text */
        inet_ntop(client_address.sin_family, get_in_addr_type((struct sockaddr*)&client_address), client_address_string, client_addr_string_len);
        printf("Received connection from: %s\n", client_address_string);
        /* Open new thread to handle client connetion: client socket closed in handle_connection */
        pthread_create(&thread, NULL, handle_connection, &client_socket);
    }
    close(sfd);
}
