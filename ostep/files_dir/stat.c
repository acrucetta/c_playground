#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

// Write your own version of the command line program stat, which simply calls
// the stat() system call on a given file or directory. Print out file size,
// number of blocks allocated, reference (link) count, and so forth. What is the
// link count of a directory, as the number of entries in the directory changes?
// Useful interfaces: stat(), naturally.

int main(int argc, char *argv[]) {
  // Execute stat()
  struct stat file_info;
  if (argc < 2) {
    printf("Usage stat <file_or_dir>");
    exit(EXIT_FAILURE);
  }
  char *filepath = argv[1];
  if (stat(filepath, &file_info) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
  printf("File: %s\n", filepath);
  printf("Size: %ld bytes\n", file_info.st_size);
  printf("Number of hard links: %i\n", file_info.st_nlink);
  printf("Blocks allocated: %i\n", file_info.st_blocks);
  printf("Permissions: %o\n", file_info.st_mode & 0777);
  printf("Last accessed: %d\n", ctime(&file_info.st_atime));
  printf("Last modified: %d\n", ctime(&file_info.st_mtime));
  printf("Last status change: %s\n", ctime(&file_info.st_ctime));
  return EXIT_SUCCESS;
}
