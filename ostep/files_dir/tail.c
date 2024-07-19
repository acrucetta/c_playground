#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

// Tail: Write a program that prints out the last few lines of a file. The
// program should be efficient, in that it seeks to near the end of the file,
// reads in a block of data, and then goes backwards until it finds the
// requested number of lines; at this point, it should print out those lines
// from beginning to the end of the file. To invoke the program,
// one should type:mytail -n file,where n is the number of lines at the end of
// the file to print. Useful interfaces: stat(), lseek(), open(), read(),
// close().

void print_usage() { printf("Usage: tail -<num lines> <file>\n"); }

int main(int argc, char *argv[]) {
  if (argc < 3 || argv[1][0] != '-' || strlen(argv[1]) < 1) {
    print_usage();
  }
  int lines = atoi(argv[1] + 1);
  char *path = argv[2];
  int fd;
  struct stat file_info;

  if ((fd = open(path, O_RDONLY)) == -1) {
    perror("open");
  }
  if ((stat(path, &file_info)) == -1) {
    perror("stat");
  }

  char *buffer[file_info.st_size];

  // Create buffer with st_size
  // Seek to the end of the file
  // Read its contents line by line and add them to the buffer, then backtrack
  // Add as many as N lines to the file
  // Close the file
}
