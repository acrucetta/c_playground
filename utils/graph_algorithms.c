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
