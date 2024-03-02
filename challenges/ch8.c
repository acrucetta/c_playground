
// CHALLENGE 8 (Shortest path). Extend the idea of an adjacency matrix of a
// graph G to a distance matrix D that holds the distance when going from point
// i to point j. Mark the absence of a direct arc with a very large value, such
// as SIZE_MAX. Can you find the shortest path between two nodes x and y given
// as an input?

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_N 6

int drow[] = {-1, 0, 1, 0};
int dcol[] = {0, 1, 0, -1};

void dijkstra(size_t A[][SIZE_N], size_t N, int source, int target) {
  // Shortest path between nodes in a graph
  // Mark all nodes as unvisited
  bool visited[SIZE_N][SIZE_N] = {0};
  int distances[SIZE_N][SIZE_N] = {0};

  // Current node = 0,0
  // For all nodes nearby, check their distance and update the distances array

  // After checking the distance with the unvisited neighbor nodes, mark
  // the current node as visited

  return;
}

int main() {
  size_t A[SIZE_N][SIZE_N] = {{0, 7, 9, 0, 0, 14},  {7, 0, 10, 15, 0, 0},
                              {9, 10, 0, 11, 0, 2}, {0, 15, 11, 0, 6, 0},
                              {0, 0, 0, 6, 0, 9},   {14, 0, 2, 0, 9, 0}};
  printf("A:\n");
  for (size_t i = 0; i < SIZE_N; i++) {
    for (size_t j = 0; j < SIZE_N; j++) {
      printf("%zu ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  size_t source = 0, destination = 5;
  dijkstra(A, SIZE_N, source, destination);
  return EXIT_SUCCESS;
}
