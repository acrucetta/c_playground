#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define LIST_LENGTH 1000

// Concurrent Linked List

typedef struct __node_t
{
  int key;
  pthread_mutex_t lock;
  struct __node_t *next;
} node_t;

typedef struct __list_t
{
  node_t *head;
  pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L)
{
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key)
{
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL)
  {
    perror("malloc");
    return -1;
  }
  new->key = key;
  new->next = NULL;


  pthread_mutex_lock(&L->lock);

  // If this is the first insert, head will be NULL
  // so we want to insert at the beginning of the list
  if (L->head == NULL || L->head->key > key)
  {
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
    return 0;
  }

  node_t *prev, *curr;
  prev = L->head;
  curr = L->head->next;

  pthread_mutex_lock(&prev->lock);
  pthread_mutex_unlock(&L->lock);
  if (curr)
    pthread_mutex_lock(&curr->lock);

  while (curr)
  {
    if (curr->key > key)
      break;
    node_t *old_prev = prev;
    prev = curr;
    curr = curr->next;
    pthread_mutex_unlock(&old_prev->lock);
    if (curr)
      pthread_mutex_lock(&curr->lock);
  }

  new->next = curr;
  prev->next = new;
  pthread_mutex_unlock(&prev->lock);
  if (curr)
    pthread_mutex_unlock(&curr->lock);
}

void List_Delete(list_t *L, int key)
{
  // Grab prev and head
  node_t *prev, *curr;
  pthread_mutex_lock(&L->lock);
  prev = L->head;
  curr = L->head->next;
  pthread_mutex_lock(&prev->lock);
  pthread_mutex_unlock(&L->lock);
  if (curr)
    pthread_mutex_lock(&curr->lock);

  // Iterate until we find the desired key to delete
  while (curr)
  {
    if (curr->key == key)
    { // Found the value
      prev->next = curr->next;
      pthread_mutex_unlock(&prev->lock);
      pthread_mutex_unlock(&curr->lock);
      free(curr);
    }

    // Keep iterating
    node_t *old_prev = prev;
    prev = curr;
    curr = curr->next;
    pthread_mutex_unlock(&old_prev->lock);
    if (curr)
      pthread_mutex_lock(&curr->lock);
  }
  pthread_mutex_unlock(&prev->lock);
}

int List_Lookup(list_t *L, int key)
{
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr)
  {
    if (curr->key == key)
    {
      rv = 0;
      printf("Found value: %i\n",key);
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return rv;
}

// Concurrent Operations

void *thread_func(void *arg)
{
  list_t *list = (list_t *)arg;
  int number = (random() / ((double) RAND_MAX + 1)) * LIST_LENGTH;
  List_Lookup(list, number);
  return NULL;
}

/*
Goal:
- Use over hand locking and test the performance at different
thread values
  - Insert multiple values at a time
  - Lookup the same key simultaneously
*/

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage counter <threads>");
    exit(1);
  }

  struct timeval start, end;
  int N_THREADS = atoi(argv[1]);
  list_t L;
  List_Init(&L);

  // Add artificial values
  for (size_t i = 0; i < LIST_LENGTH; i++)
  {
    List_Insert(&L, i);
  }

  pthread_t p[N_THREADS];
  gettimeofday(&start, NULL);
  for (size_t i = 0; i < N_THREADS; i++)
  {
    pthread_create(&p[i], NULL, &thread_func, &L);
  }

  for (size_t i = 0; i < N_THREADS; i++)
  {
    pthread_join(p[i], NULL);
  }
  gettimeofday(&end, NULL);

  long seconds = end.tv_sec - start.tv_sec;
  long micros = end.tv_usec - start.tv_usec;
  long elapsed = seconds * 1000000 + micros;

  printf("Elapsed Time: %ld (ms)", elapsed);
}
