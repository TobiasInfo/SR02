#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define k 1

typedef struct
{
    unsigned long *tab;
    unsigned long i;
    unsigned long n;
    unsigned long racine;
    pthread_mutex_t *mutex;
} ArgumentThread;


void *fonctionThread(void *argument)
{
    ArgumentThread *arg = (ArgumentThread *)argument;
    unsigned long *tab = arg->tab;
    unsigned long i = arg->i;
    unsigned long n = arg->n;
    for (unsigned long t = i; t <= (arg->racine); t += k)
    {
        if (tab[t] == 1)
        {
            unsigned long l = 2 * t + 3;
            pthread_mutex_lock(arg->mutex);
            for (unsigned long j = (l * l - 3) / 2; j < n / 2 - 1; j += l)
            {
                tab[j] = 0;
            }
            pthread_mutex_unlock(arg->mutex);
        }
    }
    pthread_exit(NULL);
}

void Eratosthenes(unsigned long n, unsigned long *tab)
{
    pthread_t *thread = malloc(sizeof(pthread_t) * k);
    unsigned long indexThread = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    for (int cpt = 0; cpt < k; cpt++)
    {
        ArgumentThread *arg = malloc(sizeof(ArgumentThread));
        arg->tab = tab;
        arg->i = 0 + cpt;
        arg->n = n;
        arg->racine = sqrt(n);
        arg->mutex = &mutex;

        pthread_create(&thread[indexThread], NULL, fonctionThread, arg);
        indexThread++;
    }
    for (unsigned int i = 0; i < indexThread; i++)
    {
        pthread_join(thread[i], NULL);
    }
    free(thread);
    pthread_mutex_destroy(&mutex);
}

void PrintTab(unsigned long n, unsigned long *tab)
{
    // Affichage des nombres premiers
    printf("2 ");
    for (unsigned long i = 0; i < (n / 2) -1; i++)
    {
        if (tab[i] == 1)
        {
            unsigned long prime = 2 * i + 3;
            printf("%ld ", prime);
        }
    }
    printf("\n");
}

void PrintIndex(unsigned long n, unsigned long *tab)
{
    int cpt = 1; // Initialisé à 1 pour inclure le nombre premier 2
    for (unsigned long i = 0; i < (n / 2) - 1; i++)
    {
        // printf("%ld ", tab[i]);
        if (tab[i] == 1)
        {
            cpt++;
        }
    }
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
        unsigned long *tab = (unsigned long *)malloc(((n / 2) - 1) * sizeof(unsigned long));
        clock_t start, end;
        double temps_execution;
        // Initialisation du tableau
        for (unsigned long i = 0; i < (n / 2) - 1; i++)
        {
            tab[i] = 1;
        }
        start = clock();
        Eratosthenes(n, tab);
        end = clock();
        temps_execution = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%f\n", temps_execution);

        PrintIndex(n, tab);
        // PrintTab(n, tab);
        free(tab);
    }
    else
    {
        printf("n doit être supérieur à 1.\n");
    }

    return 0;
}
