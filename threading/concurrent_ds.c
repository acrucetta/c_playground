#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Mutex counter

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value++;
  pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  c->value--;
  pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
  pthread_mutex_lock(&c->lock);
  int rc = c->value;
  pthread_mutex_unlock(&c->lock);
  return rc;
}

// Concurrent Linked List

typedef struct __node_t {
  int key;
  struct __node_t *next;
} node_t;

typedef struct __list_t {
  node_t *head;
  pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return -1;
  }
  new->key = key;

  // Just lock the critical section; when we modify the list
  pthread_mutex_lock(&L->lock);
  new->next = L->head;
  pthread_mutex_unlock(&L->lock);
  return 0;
}

int List_Lookup(list_t *L, int key) {
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr) {
    if (curr->key == key) {
      rv = 0;
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return rv;
}

// Thread Functions

void *increase_counter(void *arg) {
  counter_t *counter = (counter_t *)arg;
  increment(counter);
}

void *add_node(void *arg) {
  list_t *list = (list_t *)arg;
  int random = random_num; // TODO: Add random number;
  int key = 10;
  List_Insert(list, key);
}

int main() {
  counter_t counter;
  list_t list;
  init(&counter);
  List_Init(&list);
  increment(&counter);
  increment(&counter);
  increment(&counter);
  int rc = get(&counter);
  printf("Single thread counter: %i", rc);

  // Create 10000 threads and have them use the structure
  pthread_t p[10000];
  pthread_t p2[10000];
  for (size_t i = 0; i < 10000; i++) {
    pthread_create(&p[i], NULL, &increase_counter, &counter);
    pthread_create(&p2[i], NULL, &add_node, &list);
  }

  for (size_t i = 0; i < 10000; i++) {
    pthread_join(p[i], NULL);
    pthread_join(p2[i], NULL);
  }

  int multi_rc = get(&counter);
  printf("Multi-thread counter: %i", multi_rc);
}
