#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef struct
{
    int *tab;
    int i;
    int n;
} ArgumentThread;

void *fonctionThread(void *argument)
{
    ArgumentThread *arg = (ArgumentThread *)argument;
    int *tab = arg->tab;
    int i = arg->i;
    int n = arg->n;

    for (int j = i * i; j <= n; j += i)
    {
        tab[j] = 0;
    }
    pthread_exit(NULL);
}

void Eratosthenes(int n, int *tab)
{
    int racine = sqrt(n);
    pthread_t *thread = malloc(sizeof(pthread_t) * racine);
    int indexThread = 0;

    for (int i = 2; i <= racine; i++)
    {
        if (tab[i] == 1)
        {
            ArgumentThread *arg = malloc(sizeof(ArgumentThread));
            arg->tab = tab;
            arg->i = i;
            arg->n = n;
            pthread_create(&thread[indexThread], NULL, fonctionThread, arg);
            indexThread++;
        }
    }

    for (int i = 0; i < indexThread; i++)
    {
        pthread_join(thread[i], NULL);
    }
    free(thread);
}

void PrintTab(int n, int *tab)
{
    // Affichage des nombres premiers
    for (int i = 2; i <= n; i++)
    {
            printf("%d ", tab[i]);
    }
    printf("\n");
}

void PrintIndex(int n, int *tab)
{
    // Affichage des nombres premiers
    for (int i = 2; i <= n; i++)
    {
        if (tab[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Entrez un entier n > 1 : ");
    scanf("%d", &n);
    if (n <= 1)
    {
        printf("n doit être supérieur à 1.\n");
        return 0;
    }
    int *tab = malloc((n + 1) * sizeof(int));
    // Initialisation de toutes les valeurs à vrai
    for (int i = 2; i <= n; i++)
    {
        tab[i] = 1;
    }
    Eratosthenes(n, tab);
    PrintIndex(n, tab);
    PrintTab(n, tab);
    free(tab);
    return 0;
}
