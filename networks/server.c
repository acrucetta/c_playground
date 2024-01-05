#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

// Tutorial of basic network programs in C

// To establish a socket on the client we want to:
// 1. Create a socket
// 2. Connect the socket to the address using connect()
// 3. Send and receive data with read() and write()


// To establish a socket on the server side we want to:
// 1. Create a socket
// 2. Bind the socket to an address using bind() system call
// 3. Listen for connections with listen() sys call
// 4. Accept connections with accept()
// 5. Send and receive data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;

    int result;

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    int slen = sizeof(server_addr);

    bind(server_socket, (struct sockaddr *) &server_addr, slen);

    listen(server_socket, 5);

    while(1){
        char ch;
        int clen = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        read(client_socket, &ch, 1);
        printf("\nServer: I recieved %c from client!\n", ch);
        ch++;
        write(client_socket, &ch, 1);
        close(client_socket);
    }

    exit(0);
}