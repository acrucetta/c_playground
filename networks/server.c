#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
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

void error (char *msg) {
  perror(msg);
  exit(1);
}

int main (int argc, char *argv[]) {
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  // AF_INET - stands for address family, internet, specifies the IPv4 address family
  // SOCK_STREAM - uses TCP
  // 0 denotes the socket to pick whichever protocol it deems best
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("error opening socket");
  }

  // sets all values in a buffer to zero; first is a pointer, second size of buffer
  bzero((char *) &serv_addr, sizeof(serv_addr));

  // converts port to int
  portno = atoi(argv[1]);

  serv_addr.sin_family = AF_INET;

  // We need to convert the port to network byte order using htons
  // computer networks use big endian computers; which means
  // we need to convert the bytes when we send packets
  // these terms are borrowed from gulliver's travels
  // htons = host to network short
  serv_addr.sin_port = htons(portno);

  // this field is used to assign the IP address of the host
  // this is the INADDR_ANY constant
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 {
    error("ERROR on binding");
  }

  // we're now listening on the socket for connections
  // the first arg is the file descriptor
  // the second arg is the # of connections in the queue (max = 5 in most sys)
  listen(sockfd, 5);

  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0) {
    error("ERROR on accept");
  }

  // Reading information from the new socket
  bzero(buffer, 256);

  // read is a unix command to read from newsockfd into the buffer
  n = read(newsockfd, buffer, 255);
  if (n<0) {error("ERROR reading from socket");}
  printf("Here is the message: %s", buffer);

  // write is a unix command to write the message into newsockfd
  n = write(newsockfd, "I got your message", 18);
  if (n<0) { error("ERROR writing to socket");}

  return 0;
}