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

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

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
    handle_error("open");
  }
  if ((stat(path, &file_info)) == -1) {
    handle_error("stat");
  }
  if (lseek(fd, -1, SEEK_END) == -1) {
    handle_error("lseek");
  }
  char *tiny_buffer[1];
  int offset;
  while (lines>0) {
      if (read(fd, tiny_buffer, 1) == -1) {
          handle_error("read");
      }
      if (tiny_buffer[0] == '\n') {
          lines--;
      }
      offset = lseek(fd, -2, SEEK_CUR);
      if (offset==-1) {
        break;
      }
  }

  printf("Filled up buffer:\n%s",tiny_buffer);
  if (offset>0 || lines ==0) {
      if (lseek(fd, 2, SEEK_CUR) == -1) {
          handle_error("lseek");
      }
  } else {
      if (lseek(fd,0, SEEK_SET) == -1) {
          handle_error("lseek");
      }
  }

  char *buffer[file_info.st_size];
  memset(buffer,0,file_info.st_size);
  printf("Empty buffer:\n%s",buffer);
  if (read(fd, buffer, file_info.st_size) == -1) {
      handle_error("read");
  }
  printf("Full Buffer:\n%s", buffer);
  close(fd);
  exit(EXIT_SUCCESS);
}
