
// CHALLENGE 7 (Adjacency matrix)
// The adjacency matrix of a graph G is a matrix A that holds a value
// true or false in element A[i][j] if there is an arc from node i to node j.
// At this point,  can you use an adjacency matrix to conduct a breadth first
// search in a graph G
// Can you find connected components?
// Can you find a spanning tree?
#include "../utils/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4

int drow[] = {-1, 0, 1, 0};
int dcol[] = {0, 1, 0, -1};

typedef struct IntPair {
  int row;
  int col;
} IntPair;

void enqueue_intpair(Queue *q, int row, int col) {
  IntPair *pair = (IntPair *)malloc(sizeof(IntPair));
  pair->row = row;
  pair->col = col;
  enqueue(q, pair);
}

IntPair *dequeue_intpair(Queue *q) {
  void *data = dequeue(q);
  if (data == NULL) {
    return NULL;
  }
  IntPair *pair = (IntPair *)data;
  return pair;
}

bool is_valid(bool visited[][N], bool A[][N], int row, int col) {
  if (row < 0 || col < 0 || row >= N || col >= N) {
    return false;
  }
  if (visited[row][col]) {
    return false;
  }

  if (!A[row][col]) {
    return false;
  }
  return true;
}

int **bfs(const bool A[static N][N], const int G[static N][N],
          bool visited[static N][N], size_t row, size_t col) {
  Queue q;
  init_queue(&q);
  enqueue_intpair(&q, row, col);
  visited[row][col] = 1;
  while (!is_queue_empty(&q)) {
    IntPair cell = *dequeue_intpair(&q);
    int row = cell.row;
    int col = cell.col;
    for (int i = 0; i < N; i++) {
      int dx = row + drow[i];
      int dy = col + dcol[i];
      if (is_valid(visited, A, dx, dy)) {
        enqueue_intpair(&q, dx, dy);
        visited[dx][dy] = 1;
      }
    }
  }
  return EXIT_SUCCESS;
}

// Connected components are a set of vertices in a graph that are connected to
// each other by paths. In a connected component, there is a path between any
// pair of vertices. A graph can have one or more connected components. A
// connected graph has exactly one connected component, consisting of the whole
// graph. A disconnected graph has two or more connected components.
int find_connected_components() { return EXIT_SUCCESS; }

// A spanning tree of a graph is a subgraph that is a tree and connects all the
// vertices together. A single graph can have many different spanning trees.
// A graph is connected if it has a spanning tree. A graph with n vertices has
// a spanning tree with n-1 edges. A graph can have many spanning trees. A
// spanning tree does not have cycles.
int find_spanning_tree() { return EXIT_SUCCESS; }

int main(int argc, char *argv[argc + 1]) {

  bool A[N][N] = {{true, true, false, true},
                  {false, true, false, true},
                  {false, false, false, true},
                  {true, true, true, false}};
  int G[N][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  printf("Adjacency Matrix:\n");
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  bool visited[N][N] = {0};
  bfs(A, G, visited, 0, 0);

  printf("Visited Array:\n");
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      printf("%d ", visited[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 1;
}
