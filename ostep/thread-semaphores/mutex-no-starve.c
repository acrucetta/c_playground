#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t
{
    sem_t mutex;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m)
{
    m->mutex = Sem_open("mutex", 1);
}

void ns_mutex_acquire(ns_mutex_t *m)
{
    Sem_wait(m);
}

void ns_mutex_release(ns_mutex_t *m)
{
    Sem_post(m);
}

void *worker(void *arg)
{
    printf("child: before\n");
    int i;
    for (i = 0; i < loops; i++)
    {
        ns_mutex_acquire(&lock);
        value++;
        ns_mutex_release(&lock);
    }
    printf("child: after\n");
    return NULL;
}

int loops;
value = 0;
ns_mutex_t lock;

int main(int argc, char *argv[])
{
    assert(argc == 4);
    int workers = atoi(argv[1]);
    loops = atoi(argv[3]);

    pthread_t pr[workers];

    ns_mutex_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < workers; i++)
        Pthread_create(&pr[i], NULL, worker, NULL);

    for (i = 0; i < workers; i++)
        Pthread_join(pr[i], NULL);

    printf("end: value %d\n", value);

    return 0;
}
