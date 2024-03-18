// CHALLENGE 15 (Text processing in strings). We’ve covered quite a bit about
// text process- ing, so let’s see if we can actually use it. Can you search for
// a given word in a string? Can you replace a word in a string and return a
// copy with the new contents? Can you implement some
// regular-expression-matching functions for strings? For example, find a
// character class such as [A-Q] or [^0-9], match with * (meaning “anything”),
// or match with ? (meaning “any character”). Or can you implement a
// regular-expression-matching function for POSIX character classes such as
// [[:alpha:]], [[:digit:]], and so on? Can you stitch all these functionalities
// together to search for a regexp in a string? Do query-replace with regexp
// against a specific word? Extend a regexp with grouping? Extend query-replace
// with grouping?

// Tasks:
// 1. Search fort a word in a string
// 2. Replace a word in a string and return a copy with new contents
// 3. Impelement regex matching funcs for strings
//      For example, find a character class such as [A-Q] or [^0-9], match with
//      * (meaning “anything”), or match with ? (meaning “any character”)
// 4. Stitch all the functionality to search for a regexp in a string.  Do
// query-replace with regexp against a specific word? Extend a regexp with
// grouping? Extend query-replace with grouping?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
search_word finds a [word] in [src] and return 1 if found or 0 if not found.

It does this by iterating over the chars in the string and finding the chars
that match it.
*/
int search_word(char *text, char *word) {
  if (strstr(text, word)) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

char *replace_word(char *text, char *word, char *replacement) {
  char *pos = strstr(text, word);
  if (pos) {
    int text_len = strlen(text);
    int word_len = strlen(word);
    int replacement_len = strlen(replacement);
    char *new_text =
        calloc(text_len - word_len + replacement_len, sizeof(char));
    // We want to get the start and end position of the original word
    // Then we copy everything before into a string, and add the replacement
    // word; finally we add anything after that word to the new text
    memcpy(new_text, text, text_len - word_len); //
    memcpy(new_text + (pos - new_text), replacement, replacement_len);
    printf("%s", new_text);
    return new_text;
  }
  return EXIT_FAILURE;
}

int main() {
  char *text = "a bird flies high";
  char *word = "high";
  char *repl = "low";
  char *new_txt = replace_word(text, word, repl);
  free(new_txt);
}
