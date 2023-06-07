#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct {
    int* tab;
    int* i;
    int n;
} ArgumentThread;

void fonctionThread(void * argument)
{
    printf("Dans fct thr\n");
    ArgumentThread *arg = (ArgumentThread *)argument;
    int *tab = arg->tab;
    int i = *(arg->i);
    int n = arg->n;
    for (int j = i * i; j <= n; j += i)
    {
        tab[j] = 0;
    }
    pthread_exit(NULL);
}

void Eratosthenes(int n, int *tab)
{
    int ret;
    int indexThread = 0;
    int racine = sqrt(n);
    pthread_t *thread = malloc(sizeof(pthread_t) * racine);
    for (int i = 2; i <= racine; i++)
    {
        PrintTab(n, tab);
        ArgumentThread *arg = (ArgumentThread *)malloc(sizeof(ArgumentThread));
        arg->tab = tab;
        arg->i = &i;
        arg->n = n;
        if (tab[i] == 1)
        {
            pthread_create(&thread[indexThread], NULL, fonctionThread, (void*)arg);
            indexThread++;
        }
        else
        {
            free(arg);
        }
    }

    for (int i = 0; i < indexThread; i++)
    {
        pthread_join(thread[i], (void**)&ret);
    }
    printf("INDEX : %d\n", indexThread);

    free(thread);
}

int PrintTab(int n, int *tab)
{
    // Affichage des nombres premiers
    for (int i = 0; i <= n; i++)
    {
        if (tab[i] == 1)
        {
            printf("%d |", tab[i]);

        }
    }
    printf("\n");
}

int main()
{
    int n;    
    printf("Entrez un entier n > 1 : ");
    scanf("%d", &n);

    int *tab = (int *)malloc((n + 1) * sizeof(int));
    // Initialisation de toutes les valeurs à vrai
    for (int i = 2; i <= n; i++)
    {
        tab[i] = 1;
    }

    if (n > 1)
    {
        Eratosthenes(n, tab);
        PrintTab(n, tab);
    }
    else
    {
        printf("n doit être supérieur à 1.\n");
    }

    free(tab);
    return 0;
}
