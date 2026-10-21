#include <stdio.h>
#include <pthread.h>

void *function(void *arg)
{
    printf("Thread ID = %lu\n",
           (unsigned long)pthread_self());

    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, function, NULL);
    pthread_create(&t2, NULL, function, NULL);
    pthread_create(&t3, NULL, function, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
