#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct
{
    unsigned long *tab;
    unsigned long i;
    unsigned long n;
} ArgumentThread;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    unsigned long current_i;
    unsigned long *tab;
    unsigned long n;
    ArgumentThread *taskQueue;
    int queueSize;
    int queueCapacity;
} ThreadInfo;

void *fonctionThread(void *argument)
{
    ArgumentThread *arg = (ArgumentThread *)argument;
    unsigned long *tab = arg->tab;
    unsigned long i = arg->i;
    unsigned long n = arg->n;

    for (unsigned long j = i * i; j <= n; j += i)
    {
        tab[j] = 0;
    }
    pthread_exit(NULL);
}

void initTaskQueue(ThreadInfo *threadInfo, int capacity)
{
    threadInfo->taskQueue = malloc(capacity * sizeof(ArgumentThread));
    threadInfo->queueSize = 0;
    threadInfo->queueCapacity = capacity;
}

void enqueueTask(ThreadInfo *threadInfo, ArgumentThread task)
{
    pthread_mutex_lock(&threadInfo->mutex);

    // Vérifie si la file d'attente est pleine
    if (threadInfo->queueSize >= threadInfo->queueCapacity)
    {
        // Double la capacité de la file d'attente
        threadInfo->queueCapacity *= 2;
        threadInfo->taskQueue = realloc(threadInfo->taskQueue, threadInfo->queueCapacity * sizeof(ArgumentThread));
    }

    // Ajoute la tâche à la file d'attente
    threadInfo->taskQueue[threadInfo->queueSize] = task;
    threadInfo->queueSize++;

    pthread_cond_signal(&threadInfo->cond);
    pthread_mutex_unlock(&threadInfo->mutex);
}

void *threadWorker(void *argument)
{
    ThreadInfo *threadInfo = (ThreadInfo *)argument;
    ArgumentThread task;

    while (1)
    {
        pthread_mutex_lock(&threadInfo->mutex);

        // Vérifie si la file d'attente est vide
        while (threadInfo->queueSize == 0 && threadInfo->current_i <= sqrt(threadInfo->n))
        {
            pthread_cond_wait(&threadInfo->cond, &threadInfo->mutex);
        }

        // Vérifie si la file d'attente est vide et il n'y a plus de tâches à ajouter
        if (threadInfo->queueSize == 0 && threadInfo->current_i > sqrt(threadInfo->n))
        {
            pthread_mutex_unlock(&threadInfo->mutex);
            break;
        }

        // Prend la prochaine tâche dans la file d'attente
        task = threadInfo->taskQueue[threadInfo->queueSize - 1];
        threadInfo->queueSize--;

        pthread_mutex_unlock(&threadInfo->mutex);

        // Traite la tâche
        fonctionThread(&task);
    }

    pthread_exit(NULL);
}

void Eratosthenes(unsigned long n, unsigned long *tab)
{
    unsigned long racine = sqrt(n);
    pthread_t thread[7];
    ThreadInfo threadInfo;
    threadInfo.current_i = 2;
    threadInfo.tab = tab;
    threadInfo.n = n;
    pthread_mutex_init(&threadInfo.mutex, NULL);
    pthread_cond_init(&threadInfo.cond, NULL);
    initTaskQueue(&threadInfo, 7);

    for (unsigned long i = 2; i <= racine; i++)
    {
        if (tab[i] == 1)
        {
            ArgumentThread task;
            task.i = i;
            task.n = n;
            enqueueTask(&threadInfo, task);
        }
    }

    for (int i = 0; i < 7; i++)
    {
        pthread_create(&thread[i], NULL, threadWorker, &threadInfo);
    }

    for (int i = 0; i < 7; i++)
    {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&threadInfo.mutex);
    pthread_cond_destroy(&threadInfo.cond);
    free(threadInfo.taskQueue);
}

void PrintTab(unsigned long n, unsigned long *tab)
{
    // Affichage des nombres premiers
    for (unsigned long i = 2; i <= n; i++)
    {
        if (tab[i] == 1)
        {
            printf("%ld ", i);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s n\n", argv[0]);
        return 0;
    }
    unsigned long n = atol(argv[1]);

    if (n > 1)
    {
        unsigned long *tab = (unsigned long *)malloc((n + 1) * sizeof(unsigned long));
        clock_t start, end;
        double temps_execution;
        // Initialisation du tableau
        for (unsigned long i = 2; i <= n; i++)
        {
            tab[i] = 1;
        }
        start = clock();

        Eratosthenes(n, tab);

        end = clock();
        temps_execution = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%f\n", temps_execution);

        PrintTab(n, tab);
        free(tab);
    }
    else
    {
        printf("n doit être supérieur à 1.\n");
    }

    return 0;
}
