#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE 10
#define MAX_ITMS 20

int buf[BUF_SIZE];
int cnt = 0;
int in = 0;
int out = 0;
int prod_cnt = 0;
int cons_cnt = 0;

pthread_mutex_t mtx;
pthread_cond_t cond_prod;
pthread_cond_t cond_cons;

void* prod(void* param) {
    while (1) {
        int item = rand() % 100;

        pthread_mutex_lock(&mtx);

        if (prod_cnt >= MAX_ITMS) {
            pthread_mutex_unlock(&mtx);
            break;
        }

        while (cnt == BUF_SIZE) {
            pthread_cond_wait(&cond_prod, &mtx);
        }

        buf[in] = item;
        in = (in + 1) % BUF_SIZE;
        cnt++;
        prod_cnt++;
        printf("Produced: %d\n", item);

        pthread_cond_signal(&cond_cons);
        pthread_mutex_unlock(&mtx);

        sleep(rand() % 2);
    }
    return NULL;
}

void* cons(void* param) {
    while (1) {
        pthread_mutex_lock(&mtx);

        if (cons_cnt >= MAX_ITMS) {
            pthread_mutex_unlock(&mtx);
            break;
        }

        while (cnt == 0) {
            pthread_cond_wait(&cond_cons, &mtx);
        }

        int item = buf[out];
        out = (out + 1) % BUF_SIZE;
        cnt--;
        cons_cnt++;
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&cond_prod);
        pthread_mutex_unlock(&mtx);

        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t tid_prod, tid_cons;

    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cond_prod, NULL);
    pthread_cond_init(&cond_cons, NULL);

    pthread_create(&tid_prod, NULL, prod, NULL);
    pthread_create(&tid_cons, NULL, cons, NULL);

    pthread_join(tid_prod, NULL);
    pthread_join(tid_cons, NULL);

    printf("Production & Consumption complete\n");

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond_prod);
    pthread_cond_destroy(&cond_cons);

    return 0;
}
