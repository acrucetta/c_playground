#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Concurrent Linked List

typedef struct __node_t
{
  int key;
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

  // Just lock the critical section; when we modify the list
  pthread_mutex_lock(&L->lock);
  new->next = L->head;
  pthread_mutex_unlock(&L->lock);
  return 0;
}

int List_Lookup(list_t *L, int key)
{
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr)
  {
    printf("Iterating through node key: %i", curr->key);
    if (curr->key == key)
    {
      rv = 0;
      printf("Found value\n");
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return rv;
}

// Thread Functions

void *add_node(void *arg)
{
  list_t *list = (list_t *)arg;
  int random_key = rand() % 10;
  printf("Adding %i to the list\n", random_key);
  List_Insert(list, random_key);
  return NULL;
}

int main()
{

  list_t list;
  srand(time(0));
  List_Init(&list);
  pthread_t p2[10];
  for (size_t i = 0; i < 10; i++)
  {
    pthread_create(&p2[i], NULL, &add_node, &list);
  }

  for (size_t i = 0; i < 10; i++)
  {
    pthread_join(p2[i], NULL);
  }

  int list_rc = List_Lookup(&list, 5);
  printf("Found value in list: %i\n", list_rc);
}
