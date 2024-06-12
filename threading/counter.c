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

int main()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long micros = end.tv_usec- start.tv_usec;
    double elapsed = (double)seconds * 1000000 + micros;
    printf("Elapsed Time %f\n", elapsed);

    counter_t counter;
    init(&counter);
    increment(&counter);
    increment(&counter);
    increment(&counter);
    int rc = get(&counter);
    printf("Single thread counter: %i\n", rc);
    pthread_t p[10];
    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(&p[i], NULL, &increase_counter, &counter);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(p[i], NULL);
    }

    int multi_rc = get(&counter);
    printf("Multi-thread counter: %i\n", multi_rc);
}