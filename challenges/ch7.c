
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

#define SIZE_M 4

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

bool is_valid(bool visited[][SIZE_M], bool A[][SIZE_M], int row, int col) {
  if (row < 0 || col < 0 || row >= SIZE_M || col >= SIZE_M) {
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

int **bfs(const bool A[][SIZE_M], const int G[][SIZE_M], bool visited[][SIZE_M],
          size_t row, size_t col) {
  Queue q;
  init_queue(&q);
  enqueue_intpair(&q, row, col);
  visited[row][col] = 1;
  while (!is_queue_empty(&q)) {
    IntPair cell = *dequeue_intpair(&q);
    int row = cell.row;
    int col = cell.col;
    for (int i = 0; i < SIZE_M; i++) {
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

int find_connected_components() { return EXIT_SUCCESS; }
int find_spanning_tree() { return EXIT_SUCCESS; }

int main(int argc, char *argv[argc + 1]) {

  bool A[SIZE_M][SIZE_M] = {{true, true, false, true},
                            {false, true, false, true},
                            {false, false, false, true},
                            {true, true, true, false}};
  int G[SIZE_M][SIZE_M] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  printf("Adjacency Matrix:\n");
  for (size_t i = 0; i < SIZE_M; i++) {
    for (size_t j = 0; j < SIZE_M; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  bool visited[SIZE_M][SIZE_M] = {0};
  bfs(A, G, visited, 0, 0);

  printf("Visited Array:\n");
  for (size_t i = 0; i < SIZE_M; i++) {
    for (size_t j = 0; j < SIZE_M; j++) {
      printf("%d ", visited[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 1;
}
