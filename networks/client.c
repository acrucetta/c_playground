#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "unix_socket"

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    char send_char = 'C';
    char recv_char;

    // Create socket
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(1);
    }

    // Prepare the sockaddr_un structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    // Send data
    if (write(client_socket, &send_char, 1) != 1) {
        perror("write");
        exit(1);
    }

    // Receive data
    if (read(client_socket, &recv_char, 1) != 1) {
        perror("read");
        exit(1);
    }

    printf("Client: I received %c from server!\n", recv_char);

    close(client_socket);
    return 0;
}