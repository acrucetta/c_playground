#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// List Files: Write a program that lists files in the given directory. When
// called without any arguments, the program should just print the file names.
// When invoked with the -l flag, the program should print out information about
// each file, such as the owner, group, per- missions, and other information
// obtained from the stat() system call. The program should take one additional
// argument, which is thedirectorytoread,e.g.,myls -l directory.Ifnodirectoryis
// given, the program should just use the current working directory. Useful
// interfaces: stat(), opendir(), readdir(), getcwd().

/*
Requirements:
- List files in the directory.
- Receive flags (-l): print out info about each file
- Receive directory parameter
- Use: stat, opendir, readdir, getcwd

No arguments -> print file names in current dir
    - get cwd: print out file names

No flag, dir -> crawl dir, and print values inside of it

Flag -l and no dir -> print file details in cwd
    - get cwd: for each file, get stat() and print out the details

Flag -l and dir -> print file details in selected path
    - go to the selected dir; open it, get file names in it
    - for each file, get stat() and print out the details
*/

void print_usage() { printf("Usage: ls [-l]\n"); }

void print_file_info(const char *path, bool verbose) {
  struct stat file_stat;
  if (stat(path, &file_stat) == 0) {
    if (verbose) {
      printf("%s\t\t", path);
      printf("size: %lld bytes\t", (long long)file_stat.st_size);
      printf("permissions: %o\t\n", file_stat.st_mode & 0777);
    }
    else {
        printf("%s\n",path);
    }
  } else {
      perror("stat");
  }
}

void print_directory(const char *path, bool verbose) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    print_file_info(entry->d_name, verbose);
  }
  closedir(dir);
}

bool is_valid_dir() { return EXIT_SUCCESS; }

int main(int argc, char *argv[]) {

  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("Current working dir: %s", cwd);
  } else {
    perror("cwd");
  }

  bool verbose = false;

  // No arguments; just print current directory's names
  if (argc < 2) {
    print_directory(".", verbose);
    return EXIT_SUCCESS;
  }

  int i = 1;
  char *crawl_dir;
  if (strcmp(argv[i], "-l") == 0) {
    verbose = true;

    // Received path name
    if (i + 1 < argc) {
      crawl_dir = argv[++i];
    } else {
      crawl_dir = ".";
    }
  }
  print_directory(crawl_dir, verbose);
  return EXIT_SUCCESS;
}
