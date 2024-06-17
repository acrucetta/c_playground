#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// Mutex counter

typedef struct __counter_t
{
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c)
{
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

void *increase_counter(void *arg)
{
    counter_t *counter = (counter_t *)arg;
    increment(counter);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc<2) {
        fprintf(stderr, "Usage counter <threads>");
        exit(1);
    }

    struct timeval start, end;
    counter_t counter;

    init(&counter);
    int N_THREADS = atoi(argv[1]);
    pthread_t p[N_THREADS];
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < N_THREADS; i++)
    {
        pthread_create(&p[i], NULL, &increase_counter, &counter);
    }

    for (size_t i = 0; i < N_THREADS; i++)
    {
        pthread_join(p[i], NULL);
    }
    gettimeofday(&end, NULL);
    

    long seconds = end.tv_sec - start.tv_sec;
    long micros = end.tv_usec- start.tv_usec;
    long elapsed = seconds * 1000000 + micros;

    // Time of day is precise up to nanoseconds.
    printf("%i\t%ld\n", N_THREADS,elapsed);
}