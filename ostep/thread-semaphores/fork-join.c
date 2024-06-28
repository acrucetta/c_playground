#include <stdio.h>
 #include <unistd.h>
 #include <pthread.h>
 #include "common_threads.h"

 sem_t s;

 void *child(void *arg) {
     printf("child\n");
     Sem_post(s);
     return NULL;
 }

 int main(int argc, char *argv[]) {
     pthread_t p;
     printf("parent: begin\n");
     char * semaphoreName = "/fork-join-semaphore";
     s = Sem_open(semaphoreName, 0);
     Pthread_create(&p, NULL, child, NULL);
     Sem_wait(s);
     Sem_close(s);
     Sem_unlink(semaphoreName);
     printf("parent: end\n");
     return 0;
 }

