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

Blob *split_text_blob(struct Blob *blob, size_t split_point);
Blob *join_text_blobs(struct Blob *blob1, struct Blob *blob2);
void concatenate_text_blobs(struct Blob *blob);
void print_text_blob(struct Blob *blob);

Blob *blob_new(const char *src);
Blob *blob_init(Blob *blob, const char *src);

Blob *blob_new(const char *src) { return blob_init(malloc(sizeof(Blob)), src); }

Blob *blob_init(Blob *blob, const char *src) {
  if (blob) {
    if (src) {
      *blob = (Blob){
          .data = malloc(sizeof(char[strlen(src) + 1])), .prev = 0, .next = 0
          };
    if (blob->data) {
      strcpy(blob->data, src);
    }
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
Blob *split_text_blob(Blob *blob, size_t split_point) {

  int len = strlen(blob->data);

  char *data1 = malloc(split_point + 1);
  char *data2 = malloc(len - split_point + 1);

  strncpy(data1, blob->data, split_point);
  strncpy(data2, blob->data, len - split_point);

  blob_set_data(blob, data1);
  Blob *blob2 = blob_new(data2);
  blob2->prev = blob;
  blob2->next = blob->next;

  if (blob->next) {
    blob->next->prev = blob2;
    blob->next = blob2;
  }

  free(data1);
  free(data2);

  return blob;
}

Blob *join_text_blobs(Blob *blob1, Blob *blob2) {
  if (blob1 && blob2 && blob1->data && blob2->data && blob1->next == blob2 &&
      blob2->prev == blob1) {
    size_t len1 = strlen(blob1->data);
    size_t len2 = strlen(blob2->data);
    if (len1 && len2) {
      char *joint_data = malloc(len1 + len2 + 1);

      strcpy(joint_data, blob1->data);
      strcpy(joint_data + len1, blob2->data);

      blob_set_data(blob1, joint_data);
      blob_destroy(blob2);
    }
  }

  return blob1;
}

void blob_print_all(Blob *blob) {
  while (blob) {
    printf("%s", blob->data);
    blob = blob->next;
  }
}

int main() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    perror("File open failed");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read = 0;
  Blob *head = 0, *tail = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    Blob *new_blob = blob_new(line);
    if (new_blob) {
      if (tail) {
        tail->next = new_blob;
        new_blob->prev = tail;
        tail = new_blob;
      } else {
        head = tail = new_blob;
      }
    }
  }
  // split_text_blob(head, 4);
  // printf("Split blob %s", head->data);

  join_text_blobs(head, head->next);
  printf("Joint blob %s", head->data);
  // printf("Joint blob %s", head->data);
  // printf("\nAfter join%s", joint_blob);
  // concatenate_text_blobs(&blob1);
  // print_text_blob(&blob1);

  return EXIT_SUCCESS;
}
