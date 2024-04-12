// CHALLENGE 16 (Text processing in streams). For text processing in streams,
// can you read on stdin, dump modified text on stdout, and report diagnostics
// on stderr? Count the occurrences of a list of words? Count the occurrences of
// a regexp? Replace all occurrences of a word with another?

#include <stdio.h>
#include <stdlib.h>

int main() {
  char *sample_text[256];
  char *query_text[256];
  fprintf(stdout, "Input the text: \n");
  if (fgets(sample_text, sizeof sample_text, stdin)) {
    fprintf(stdout, "Input the query text: \n");
    if (fgets(query_text, sizeof query_text, stdin)) {
      fprintf(stdout, "This was your input: %s", query_text);
    } else {
      fprintf(stderr, "Invalid query text");
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Invalid sample text\n");
    return EXIT_FAILURE;
  }
}
