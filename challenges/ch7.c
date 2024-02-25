
// CHALLENGE 7 (Adjacency matrix)
// The adjacency matrix of a graph G is a matrix A that holds a value
// true or false in element A[i][j] if there is an arc from node i to node j.
// At this point,  can you use an adjacency matrix to conduct a breadth first
// search in a graph G
// Can you find connected components?
// Can you find a spanning tree?
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_M 4

int bfs(bool **A, size_t M, bool *visited, size_t start) {

  // Set-up queue

  // For each vertex next to the current start
  // If the vertex wasn't visited and is true,
  // then keep looking, add them to the queue
}

int find_connected_components() { return EXIT_SUCCESS; }
int find_spanning_tree() { return EXIT_SUCCESS; }

int main(int argc, char *argv[argc + 1]) {

  // The adjacency matrix of a grap G is a matrix
  // that holds true or false in element A[i][j] if
  // there is an arc from node i to node j
  bool A[SIZE_M][SIZE_M] = {{false, false, false, true},
                            {false, false, false, true},
                            {false, false, false, true},
                            {true, true, true, false}};
  printf("A:\n");
  for (size_t i = 0; i < SIZE_M; i++) {
    for (size_t j = 0; j < SIZE_M; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  // Do BFS of the graph
  // Find connected components
  // Find the spanning tree

  return 1;
}
