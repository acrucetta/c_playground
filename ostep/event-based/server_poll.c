#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_CLIENTS 10
#define MAX_EVENTS 10
#define SERVER_PORT 8888

// Resources:
// https://stackoverflow.com/questions/40864527/what-is-file-descriptor
// https://dev.to/frosnerd/writing-a-simple-tcp-server-using-kqueue-cah
// https://eradman.com/posts/kqueue-tcp.html
// https://wiki.netbsd.org/tutorials/kqueue_tutorial/

// Now, add the select() interface. Build a main program that can accept
// multiple connections, and an event loop that checks which file descriptors
// have data on them, and then read and process those requests. Make sure to
// carefully test that you are using select() correctly.

int main()
{
    int status;
    int kq, listener, new_socket;
    struct kevent change_event, event_list[MAX_EVENTS];

    struct addrinfo hints;
    struct addrinfo *servinfo; // pointer to results
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // dont care bout ipv4 or 6
    hints.ai_socktype = SOCK_STREAM; // tcp stream socket
    hints.ai_flags = AI_PASSIVE;     // fill in the ip for me

    if ((status = getaddrinfo(NULL, "8080", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    kq = kequeue();

    int listener = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (bind(listener, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
    {
        perror("bind");
    };

    if (listen(listener, MAX_CLIENTS) != 0)
    {
        perror("listen");
    }

    // Register listener with kqueue
    EV_SET(&change_event, listener, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    // Event loop
    while (1)
    {
        int new_events = kevent(kq, NULL, 0, event_list, MAX_EVENTS, NULL);

        if (new_events < 1)
        {
            perror("new events");
        }
        for (size_t i = 0; i < new_events; i++)
        {
            // disconnect the socket and delete the connection
            if (event_list[i].flags & EV_EOF) {
                printf("disconnect\n");
            }
            // new connection: accept and register
            else if (event_list[i].ident == listener)
            {
                // accept the socket
                // add to the event queue
                // send message welcoming it to our server
            }
            // read connection: read from the connection buffer
            else if (event_list[i].flags == EVFILT_READ)
            {
                // recieve message
            }
        }
    }
}
