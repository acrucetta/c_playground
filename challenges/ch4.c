
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

#include <stdio.h>
#include <stdlib.h>

size_t *parent;

void initializeForest(size_t n) {
  parent = (size_t *)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    // Initially, each node is its own parent (root of its own tree)
    parent[i] = i;
  }
}

// For a given index I find the root of the tree
void find(){};

// Change all parennt entries on a path to the root (including) to a
// specific value
void find_replace(){};

// FindCompress function that changes all parent entries to the root that has
// been found
void find_compress(){};

// Union function that, for two given elements, combines their trees into one.
void union(){};
