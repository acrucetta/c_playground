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
// 1. Search fort a word in a string [x]
// 2. Replace a word in a string and return a copy with new contents [x]
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

// STRING FUNCTIONS //

int search_word(char *text, char *word) {
  if (strstr(text, word)) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

char *replace_word(char *text, char *word, char *replacement) {
  char *pos = strstr(text, word);
  printf("Pos: %s\n", pos);
  if (pos) {
    int text_len = strlen(text);
    int word_len = strlen(word);
    int replacement_len = strlen(replacement);
    char *new_text =
        calloc(text_len - word_len + replacement_len, sizeof(char));
    // We want to get the start and end position of the original word
    // Then we copy everything before into a string, and add the replacement
    // word; finally we add anything after that word to the new text

    // We want to copy the chars up to the replacement word
    // text up to pos? 0-first pos
    memcpy(new_text, text, pos - text);
    printf("0: %s\n", new_text);

    // Then we want to copy in the word
    // new_text + (pos - text)
    memcpy(new_text + (pos - text), replacement, replacement_len);
    printf("1: %s\n", new_text);

    // Paste the remaining characters
    // text+word+ (pos-repl length)
    memcpy(new_text + (pos - text) + replacement_len, pos + word_len,
           text_len - (pos - text) - word_len);
    printf("2: %s\n", new_text);
    return new_text;
  }
  return EXIT_FAILURE;
}

// REGEX MATCHING FUNCTIONS //
//
// DESCRIPTION:
// Impelement regex matching funcs for strings
// For example, find a character class such as [A-Q] or [^0-9], match with
// * (meaning “anything”), or match with ? (meaning “any character”)

int match(char *regexp, char *text);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text) {
  if (regexp[0] == '^')
    return matchhere(regexp + 1, text);
  do { /* must look even if string is empty */
    if (matchhere(regexp, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text) {
  if (regexp[0] == '\0')
    return 1;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp + 2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
    return matchhere(regexp + 1, text + 1);
  return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text) {
  do { /* a * matches zero or more instances */
    if (matchhere(regexp, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}

int main() {
  char *text = "a cow flies high";
  char *word = "cow";
  char *repl = "bear";
  char *new_txt = replace_word(text, word, repl);
  free(new_txt);
}
