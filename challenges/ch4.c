
// CHALLENGE 4 (Union - Find)
//
// We want to perform two principal operations.
//
// A Find operation receives one element of the ground set and returns the root
// of corresponding set
//
// A Union a operation receives two elements and merges the two sets to which
// these elements belong into one.
//
// Each set has a root.
//
// We want to implement a forest data structure in an index table of base type
// size_t called parent.
//
// Here, a value in the table SIZE_MAX would mean a position represents a root
// of one of the trees.
//
// One of the important features to start the implementation is an
// initialization function that makes parent the singleton partition: that is,
// the partition where each element is the root of its own private set.

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t *parent;
// Value at parent[i] => parent of element i

void initialize_forest(size_t n);
size_t find(size_t *parent, size_t i);
void find_compress(size_t *parent, size_t i);
void union_set(size_t *parent, size_t x, size_t y);

void initialize_forest(size_t n) {
  parent = (size_t *)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    parent[i] = i;
  }
}

// For a given index I find the root of the tree
size_t find(size_t *parent, size_t i) {
  // We want to iterate starting through the index i
  // then get to the root of the tree. We return
  // the final index of where we end up.
  while (parent[i] != i && parent[i] != SIZE_MAX) {
    i = parent[i];
  }
  return i;
}

// FindCompress function that changes all parent entries to the root that has
// been found
void find_compress(size_t *parent, size_t i) {
  size_t root = find(parent, i);
  while (parent[i] != i) {
    size_t next = parent[i];
    parent[i] = root;
    i = next;
  }
};

// Union function that, for two given elements, combines their trees into one.
void union_set(size_t *parent, size_t x, size_t y) {
  size_t root_x = find(parent, x);
  size_t root_y = find(parent, y);
  while (root_x != root_y) {
    parent[root_y] = root_x;
  }
}

int main() {
  initialize_forest(5);
  return EXIT_SUCCESS;
}
