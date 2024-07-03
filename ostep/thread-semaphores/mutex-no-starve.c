// #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//
int loops;
int value = 0;

typedef struct __ns_mutex_t
{
    int room1;
    int room2;
    sem_t mutex;
    sem_t *t1;
    sem_t *t2;
} ns_mutex_t;

ns_mutex_t lock;

void ns_mutex_init(ns_mutex_t *m)
{
    m->room1 = 0;
    m->room2 = 0;
    m->mutex = Sem_open("mutex", 1);
    m->t1 = Sem_open("turnstile1", 1);
    m->t2 = Sem_open("turnstile2", 0);
}

void ns_mutex_acquire(ns_mutex_t *m)
{
    Sem_wait(m->mutex);
    m->room1++;
    Sem_post(m->mutex);

    Sem_wait(m->t1);
    m->room2++;
    Sem_wait(m->mutex);
    m->room1--;

    if (m->room1==0) {
        Sem_post(m->mutex);
        Sem_post(m->t2);
    } else {
        Sem_post(m->mutex);
        Sem_post(m->t1);
    }

    Sem_wait(m->t2);
    m->room2++;
}

void ns_mutex_release(ns_mutex_t *m)
{
    if (m->room2==0) {
        Sem_post(m->t1);
    } else {
        Sem_post(m->t2);
    }
}

void *worker(void *arg)
{
    int thread_id = *(int*)arg;
    printf("Thread ID: %i\n", thread_id);
    ns_mutex_acquire(&lock);
    value++;
    ns_mutex_release(&lock);
    return NULL;
}

int main(int argc, char *argv[])
{
    assert(argc == 2);
    int workers = atoi(argv[1]);

    pthread_t pr[workers];
    ns_mutex_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < workers; i++)
        Pthread_create(&pr[i], NULL, worker, &i);

    for (i = 0; i < workers; i++)
        Pthread_join(pr[i], NULL);

    printf("counter: %i\n", value);
    Sem_close(lock.mutex);
    Sem_close(lock.t1);
    Sem_close(lock.t2);

    return 0;
}
