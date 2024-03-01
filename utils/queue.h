#include <stdbool.h>

typedef struct QueueNode {
  int data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
  int size;
} Queue;

void init_queue(Queue *q);
void enqueue(Queue *q, void *item);
void *dequeue(Queue *q);
int queue_print(Queue *q);
bool is_queue_empty(Queue *q);
