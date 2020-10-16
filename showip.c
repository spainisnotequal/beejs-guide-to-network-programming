/*
** showip.c -- show IP addresses for a host given on the command line
*/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main (int argc, char *argv[]) {

        if(argc != 2) {
                fprintf(stderr, "usage: showip hostname\n");
                return 1;
        }

        struct addrinfo hints;

        memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
        hints.ai_family = AF_UNSPEC;      // don't care IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;  // TCP stream sockets
        hints.ai_flags = AI_PASSIVE;      // fill in my IP for me

        char *server = argv[1];
        int status;
        struct addrinfo *servinfo; // will point to the results, which will be a linked list

        if((status = getaddrinfo(server, NULL, &hints, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
                return 2;
        }

        struct addrinfo *p;
        for(p = servinfo; p != NULL; p = p->ai_next) {
                void *addr;
                char *ipver;

                // get the pointer to the address itself, corresponding to different fields in IPv4 and IPv6
                if(p->ai_family == AF_INET) { // IPv4
                        struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
                        addr = &(ipv4->sin_addr);
                        ipver = "IPv4";
                } else { // IPv6
                        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
                        addr = &(ipv6->sin6_addr);
                        ipver = "IPv6";
                }

                // convert the IP to a string
                char ipstr[INET6_ADDRSTRLEN];
                inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));

                // print it
                printf("  %s: %s\n", ipver, ipstr);
        }

        freeaddrinfo(servinfo); // free the linked list
        return 0;
}
