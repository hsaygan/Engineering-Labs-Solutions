#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t R2, R3, W1, W2;

void *read(void *tid)
{
    int id = *((int *)tid);
    if (id == 2)
        sem_wait(&R2);
    else if (id == 3)
        sem_wait(&R3);

    int i = 0;
    for (i=0;i<5;i++)
        printf("Reader Thread %d reading from database\n", id);

    if (id == 1)
        sem_post(&W1);
    else if (id == 2)
        sem_post(&W2);

    pthread_exit(NULL);
}

void *write(void *tid)
{
    int id = *((int *)tid);
    if (id == 1)
        sem_wait(&W1);
    else if (id == 2)
        sem_wait(&W2);

    int i = 0;
    for (i=0;i<5;i++)
        printf("Writer Thread %d writing to the database\n", id);

    if (id == 1)
        sem_post(&R2);
    else if (id == 2)
        sem_post(&R3);

    pthread_exit(NULL);
}

int main()
{
    sem_init(&R2, 0, 0);
    sem_init(&R3, 0, 0);
    sem_init(&W1, 0, 0);
    sem_init(&W2, 0, 0);

    pthread_t r1, r2, r3, w1, w2;
    int tid1 = 1;
    int tid2 = 2;
    int tid3 = 3;

    pthread_create(&r1, NULL, read, &tid1);
    pthread_create(&r2, NULL, read, &tid2);
    pthread_create(&r3, NULL, read, &tid3);
    pthread_create(&w1, NULL, write, &tid1);
    pthread_create(&w2, NULL, write, &tid2);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    return 0;
}
