// CHALLENGE 12 (text processor). For a text processor, can you use a doubly
// linked list to store text? The idea is to represent a “blob” of text through
// a struct that contains a string (for the text) and pointers to preceding and
// following blobs.
//
// Can you build a function that splits a text blob in two at a
// given point?
//
// One that joins two consecutive text blobs?
//
// One that runs through the entire text and puts it in the form of one blob per
// line?
//
// Can you create a function that prints the entire text or prints until
// the text is cut off due to the screen size?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TextBlob {
  char *string;
  struct TextBlob *prev;
  struct TextBlob *next;
};

void split_text_blob(struct TextBlob *blob, size_t split_point);
void join_text_blobs(struct TextBlob *blob1, struct TextBlob *blob2);
void concatenate_text_blobs(struct TextBlob *blob);
void print_text_blob(struct TextBlob *blob);

/*
Splits a [blob] into two instances at the [split_point]
*/
void split_text_blob(struct TextBlob *blob, size_t split_point) {

  struct TextBlob *blob_1 = (struct TextBlob *)malloc(sizeof(struct TextBlob));
  struct TextBlob *blob_2 = (struct TextBlob *)malloc(sizeof(struct TextBlob));

  int str_len = strlen(blob->string);
  int half_len = (int)str_len / 2;

  blob_1->string = (char *)malloc(split_point + 1);
  strncpy(blob_1->string, blob->string, split_point);
  blob_1->string[split_point] = '\0';

  blob_2->string = (char *)malloc(str_len - split_point + 1);
  strncpy(blob_2->string, &blob->string[split_point], str_len - split_point);
  blob_2->string[str_len - split_point] = '\0';

  blob_1->prev = blob->prev;
  blob_1->next = blob_2;

  blob_2->prev = blob_1;
  blob_2->next = blob->next;

  if (blob->prev != NULL) {
    blob->prev->next = blob_1;
  }

  if (blob->next != NULL) {
    blob->next->prev = blob_2;
  }

  // free(blob->string);
  // free(blob);
}

int main() {
  struct TextBlob blob1;

  // Initialize with random text
  blob1.string = "This is a test";
  blob1.prev = 0;
  blob1.next = 0;

  // Add a few more blobs
  struct TextBlob blob2;
  blob2.string = "This is another test";
  blob2.prev = &blob1;
  struct TextBlob blob3;
  blob3.string = "This is yet another test";
  blob3.prev = &blob2;

  blob1.next = &blob2;
  blob2.next = &blob3;

  printf("\nBefore Split %s\n", blob1.string);
  split_text_blob(&blob1, 5);
  printf("\nAfter Split %s", blob1.string);
  // join_text_blobs(&blob1, &blob2);
  // concatenate_text_blobs(&blob1);
  // print_text_blob(&blob1);

  return EXIT_SUCCESS;
}
