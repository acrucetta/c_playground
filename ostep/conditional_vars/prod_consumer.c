#include <stdio.h>
#include <pthread.h>

#define MAX 10  // Buffer size
#define LOOPS 50  // Number of items each producer/consumer will process

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

pthread_cond_t empty, fill;
pthread_mutex_t mutex;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&mutex);        // p1
        while (count == MAX)               // p2
            pthread_cond_wait(&empty, &mutex);  // p3
        put(i);                            // p4
        pthread_cond_signal(&fill);        // p5
        pthread_mutex_unlock(&mutex);      // p6
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, tmp;
    for (i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&mutex);        // c1
        while (count == 0)                 // c2
            pthread_cond_wait(&fill, &mutex);   // c3
        tmp = get();                       // c4
        pthread_cond_signal(&empty);       // c5
        pthread_mutex_unlock(&mutex);      // c6
        printf("%d\n", tmp);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&fill, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&fill);

    return 0;
}