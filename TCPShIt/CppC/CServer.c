#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    //
    struct sockaddr_in address;
    // struct that holds information about ur socket e.g. port, hostname, it stores the values in non human readable form so you need to use functions to convert before you assign
    int opt = 1;
    //idk what this is
    int addrlen = sizeof(address);

    char buffer[1024] = {0};
    // array that holds the incoming data after a read
    char *hello = "Hello from server";


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    //AF_INET means IPv4, sets the internet protocol for the socket, must match for connections
    address.sin_addr.s_addr = INADDR_ANY;
    //tells the socket to allow any incoming addresses to dock
    address.sin_port = htons( PORT );
    //inputs the port into struct

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }


    valread = read( new_socket , buffer, 1024);
    //reads latest information received and puts it in buffer
    printf("%s\n",buffer );

    send(new_socket , hello , strlen(hello) , 0 );
    //sends information down a connection
    printf("Hello message sent\n");

    valread = read( new_socket , buffer, 1024);

    printf("%s\n",buffer );

    return 0;


}
