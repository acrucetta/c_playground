#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct params params;
struct params {
  int a1, a2, ret;
};

void *thread_action(void *arg) {
  int *val = (int *)arg;
  printf("Thread %i\n", (*val));
  (*val)++;
  return (void *)(val);
}

void *modify_struct(void *arg) {
  params *p = (params *)arg;
  p->ret = p->a1 + p->a2;
  return NULL;
}

void *modify_struct_with_return(void *arg) {
  params *p = (params *)arg;
  return p->a1 + p->a2;
}

void *modify_with_lock(void *arg) {
  params *p = (params *)arg;
  return p->a1 + p->a2;
}

int main(int argc, char *argv[]) {

  pthread_t p[3];

  // Single int
  int rvalue = 10;
  pthread_create(&p[0], NULL, &thread_action, &rvalue);
  void *result;
  pthread_join(p[0], &result);
  printf("Returned %i\n", *(int *)result);

  // Struct
  params *ps = (params *)malloc(sizeof(params));
  ps->a1 = 2;
  ps->a2 = 4;
  pthread_create(&p[1], NULL, &modify_struct, ps);
  pthread_join(p[1], NULL);
  printf("Struct Returned %i\n", ps->ret);

  // Struct with return
  params *ps2 = (params *)malloc(sizeof(params));
  ps2->a1 = 2;
  ps2->a2 = 4;
  pthread_create(&p[2], NULL, &modify_struct_with_return, ps2);
  int *ret;
  pthread_join(p[2], &ret);
  printf("Struct 2 Returned %i\n", (int)ret);
  return 0;
}
