#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include "common_threads.h"

#define PORT 8080
#define MAX_CLIENTS 10

int main()
{
  int socket_listen;
  int client_socket;
  struct sockaddr_un server_addr;
  struct sockaddr_un client_addr;

  int result;

  socket_listen = socket(AF_UNIX, SOCK_STREAM, 0);

  if (!ISVALIDSOCKET(socket_listen))
  {
    printf("Error: could not create socket\n");
    return 1;
  }

  server_addr.sun_family = AF_UNIX;
  strcpy(server_addr.sun_path, "unix_socket");

  int slen = sizeof(server_addr);

  // Bind the socket to an address
  printf("Binding socket to local address...\n");
  bind(socket_listen, (struct sockaddr *)&server_addr, slen);

  // Listen for connections
  listen(socket_listen, MAX_CLIENTS);

  // Setting up select() for polling connections
  fd_set master;
  FD_ZERO(&master);
  FD_SET(socket_listen, &master);
  SOCKET max_socket = socket_listen;

  printf("Waiting for connections...\n");

  while (1)
  {
    fd_set reads;
    reads = master;
    if (select(max_socket + 1, &reads, 0, 0, 0) < 0)
    { // select() will wait for a connection
      printf("Error: select() failed\n");
      exit(1);
    }

    SOCKET i;
    for (i = 1; i <= max_socket; ++i)
    {
      if (FD_ISSET(i, &reads)) // Check if socket is ready
      {
        if (i == socket_listen) // New connection
        {
          struct sockaddr_in client_address; // Client address
          socklen_t client_len = sizeof(client_address);
          SOCKET socket_client = accept(socket_listen, (struct sockaddr *)&client_address, &client_len);
          if (!ISVALIDSOCKET(socket_client))
          {
            printf("Error: accept() failed\n");
            exit(1);
          }
          FD_SET(socket_client, &master); // Add socket to master set
          if (socket_client > max_socket)
          { // Keep track of max socket, so we know when to stop searching for connections
            max_socket = socket_client;
          }

          char address_buffer[100];
          getnameinfo((struct sockaddr *)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
          printf("New proxy connection for %s\n", address_buffer);
        }
        else
        { // Handle existing connection
          char read[1024];
          int bytes_received = recv(i, read, 1024, 0);
          if (bytes_received < 1)
          {
            FD_CLR(i, &master);
            CLOSESOCKET(i);
            continue;
          }
          read[bytes_received] = '\0';
          printf("%s", read);
        }
      }
    }
  }
  close(socket_listen);
  return 0;
}
