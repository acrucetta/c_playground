#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//  Recursive Search: Write a program that prints out the names of each file and
//  directory in the file system tree, starting at a given point in the tree.
//  For example, when run without arguments, the program should start with the
//  current working directory and print its contents, as well as the contents of
//  any sub-directories, etc., until the entire tree, root at the CWD, is
//  printed. If given a single argu- ment (of a directory name), use that as the
//  root of the tree instead. Refine your recursive search with more fun
//  options, similar to the powerful find command line tool. Useful interfaces:
//  figure it out.

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

void print_usage() { printf("Usage: find -<num lines> <file>\n"); }

/*
Goal: Print the name of each file in the dir of the file system tree.

No args: start with current dir and print its contents along with any subdir.
Args: start with the given path.

Requirements:
- Go to the directory: opendir(), readdir(), getcwd()
- Print files in that directory: opendir(), readdir(), getcwd()
- Detect if an item is a directory: stat()
- Get full path of a directory

## Workflow (Recursive Function)

Base Case: No more directories in a path.
Recursive Case: Print all files in the current path. If any of them
is a directory, call the function again. Else return.

*/

void print_file_name(const char *path) {
  struct stat file_stat;
  if (stat(path, &file_stat) == 0) {
    printf("%s\n", path);
  } else {
    perror("stat");
  }
}

// Prints all the files in a given directory
void print_directory(const char *base_path) {
  DIR *dir = opendir(base_path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
  struct dirent *entry;
  char path[1024];
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0) continue;
    snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
    if (entry->d_type == DT_DIR) {
      print_directory(path);
    } else {
      print_file_name(path);
    }
  }
  closedir(dir);
}

int main(int argc, char *argv[]) {
  char cwd[1024];
  if (argc < 2) {
    getcwd(cwd,sizeof(cwd));
    print_directory(cwd);
  } else
  {
    // Open directory at path argv[1]
    print_directory(argv[1]);
  }
  
}
