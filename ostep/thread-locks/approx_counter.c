#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define NUMCPUS 8

typedef struct __counter_t
{
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold)
{
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++)
    {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

//update
void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        // transfer to global assuming amt > 0
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu]=0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

//get global amount
int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val;
}


void *increase_counter(void *arg)
{
    counter_t *counter = (counter_t *)arg;
    int thread_id = (int)pthread_self();
    for (size_t i = 0; i < 1000; i++)
    {
        update(counter,thread_id,1);
    }
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
    int threshold = 1;
    init(&counter, threshold);
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
    int counter_val = get(&counter);
    printf("%i\t%ld\t%i\n", N_THREADS,elapsed,counter_val);
}