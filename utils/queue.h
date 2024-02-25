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
void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int queue_print(Queue *q);
