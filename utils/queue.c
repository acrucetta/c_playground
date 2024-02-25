#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Queue Implementation in C
//
// Basic First In, First Out implementation
//
// API
// Enqueue (queue, item)
// Dequeue (queue)
// Queue_print()
// Queue_peek()

typedef struct QueueNode {
  int data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
  int size;
} Queue;

void init_queue(Queue *q) {
  q->front = NULL;
  q->rear = NULL;
  q->size = 0;
}

void enqueue(Queue *q, int item) {
  QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
  new_node->data = item;
  if (q->size == 0) {
    q->front = q->rear = new_node;
  } else {
    q->rear->next = new_node;
    q->rear = new_node;
  }
  ++q->size;
}

bool is_queue_empty(Queue *q) { return q->size == 0; }

int dequeue(Queue *q) {
  if (is_queue_empty(q)) {
    return EXIT_FAILURE;
  }
  int front_val;
  QueueNode *temp = q->front;
  front_val = q->front->data;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);
  --q->size;
  return front_val;
}

void queue_print(const Queue *q) {
  printf("Queue: ");
  for (QueueNode *current = q->front; current != NULL;
       current = current->next) {
    if (current->next == NULL) {
      printf("%d", current->data);
      break;
    }
    printf("%d->", current->data);
  }
  printf("\n");
}

int queue_peek(Queue *q) {
  if (is_queue_empty(q)) {
    return EXIT_FAILURE;
  }
  return q->front->data;
}

int main() {
  Queue q;
  init_queue(&q);
  enqueue(&q, 4);
  enqueue(&q, 4);
  enqueue(&q, 4);
  queue_print(&q);
}
