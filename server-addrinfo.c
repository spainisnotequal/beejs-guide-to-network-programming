#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "3490" // a string, not a number

int main (int argc, char *argv[]) {

        struct addrinfo hints;

        memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
        hints.ai_family = AF_UNSPEC;      // don't care IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
        hints.ai_flags = AI_PASSIVE;      // fill in my IP for me

        int status;
        struct addrinfo *servinfo; // will point to the results, which will be a linked list

        if ((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
                return 1;
        }

        // servinfo now points to a linked list of 1 or more struct addrinfos
        // do whatever you need to do until you don't need servinfo anymore
        // in this case, just print the first a message
        printf("servinfo now points to a linked list of 1 or more struct addrinfos\n");

        freeaddrinfo(servinfo); // free the linked list
        
        return 0;
}
