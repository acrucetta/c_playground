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

typedef struct Blob Blob;

struct Blob {
  char *data;
  struct Blob *prev;
  struct Blob *next;
};

void split_text_blob(struct Blob *blob, size_t split_point);
void join_text_blobs(struct Blob *blob1, struct Blob *blob2);
void concatenate_text_blobs(struct Blob *blob);
void print_text_blob(struct Blob *blob);

Blob *blob_new(const char *src);
Blob *blob_init(Blob *blob, const char *src);

Blob *blob_new(const char *src) { return blob_init(malloc(sizeof(Blob)), src); }

Blob *blob_init(Blob *blob, const char *src) {
  if (blob) {
    if (src) {
      *blob = (Blob){
          .data = malloc(sizeof(char[strlen(src) + 1])), .prev = 0, .next = 0};
    };
    if (blob->data) {
      strcpy(blob->data, src);
    }
  } else {
    *blob = (Blob){0};
  }
  return blob;
}

void blob_set_data(Blob *blob, char *src) {
  if (blob) {
    free(blob->data);
    blob->data = malloc(sizeof(char[strlen(src) + 1]));
    strcpy(blob->data, src);
  }
}

void blob_destroy(Blob *blob) {
  if (blob) {
    free(blob->data);
    if (blob->next) {
      blob->next->prev = blob->prev;
    }
    if (blob->prev) {
      blob->prev->next = blob->next;
    }
    blob_init(blob, 0);
  }
}

void blob_free(Blob *blob) {
  blob_destroy(blob);
  free(blob);
}

/*
Splits a [blob] into two instances at the [split_point]
*/
void split_text_blob(struct Blob *blob, size_t split_point) {

  Blob *split_blob = (struct Blob *)malloc(sizeof(struct Blob));

  int str_len = strlen(blob->data);

  char *first_half_str = (char *)malloc(split_point + 1);
  strncpy(first_half_str, blob->data, split_point);
  first_half_str[split_point] = '\0';
  blob->data = first_half_str;

  split_blob->data = (char *)malloc(str_len - split_point + 1);
  strncpy(split_blob->data, &blob->data[split_point], str_len - split_point);
  split_blob->data[str_len - split_point] = '\0';

  blob->next = split_blob->prev;
  split_blob->prev = blob;
  split_blob->next = blob->next;
}

int main() {
  Blob blob1;

  // Initialize with random text
  blob1.data = "This is a test";
  blob1.prev = 0;
  blob1.next = 0;

  // Add a few more blobs
  Blob blob2;
  blob2.data = "This is another test";
  blob2.prev = &blob1;

  Blob blob3;
  blob3.data = "This is yet another test";
  blob3.prev = &blob2;

  blob1.next = &blob2;
  blob2.next = &blob3;

  printf("\nBefore Split %s\n", blob1.data);
  split_text_blob(&blob1, 5);
  printf("\nAfter Split %s", blob1.data);
  // join_text_blobs(&blob1, &blob2);
  // concatenate_text_blobs(&blob1);
  // print_text_blob(&blob1);

  return EXIT_SUCCESS;
}
