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
    ArgumentThread *arg = (ArgumentThread *)argument;
    int *tab = arg->tab;
    int *i = arg->i;
    int n = arg->n;
    for (int j = *i * *i; j <= n; j += *i)
    {
        tab[j] = 0;
    }
    pthread_exit(0);
}

void Eratosthenes(int n, int *tab)
{
    int *ret;
    int indexThread = 0;
    int racine = sqrt(n);
    pthread_t *thread = malloc(sizeof(pthread_t) * racine);
    for (int i = 2; i <= racine; i++)
    {
        ArgumentThread *arg = (ArgumentThread *)malloc(sizeof(ArgumentThread));
        arg->tab = tab;
        arg->i = &i;
        arg->n = n;
        if (tab[i] == 1)
        {

            pthread_create(&thread[indexThread], NULL, fonctionThread, (void*)arg);
            // Marquer tous les multiples de i comme faux
        }
        indexThread++;
        free(arg);
    }
    printf("indexThread : %d\n", indexThread);

    for (int i = 0; i < indexThread; i++)
    {
        printf("i : %d\n", i);
        pthread_join(thread[i], NULL);
    }
    printf("ICI : %d\n", indexThread);
}

int PrintTab(int n, int *tab)
{
    // Affichage des nombres premiers
    for (int i = 0; i <= n; i++)
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
    // scanf("%d", &n);
    n = 20;
    int *tab = (int *)malloc((n + 1) * sizeof(int));
    // Initialisation de toutes les valeurs à vrai
    for (int i = 2; i <= n; i++)
    {
        tab[i] = 1;
    }

    if (n > 1)
    {
        Eratosthenes(n, tab);
        // PrintTab(n, tab);
    }
    else
    {
        printf("n doit être supérieur à 1.\n");
    }
    free(tab);
    return 0;
}

// typedef struct {
//     int start;
//     int end;
//     int* tab;
// } ThreadArgs;

// void* markMultiples(void* arg) {
//     ThreadArgs* threadArgs = (ThreadArgs*)arg;
//     int start = threadArgs->start;
//     int end = threadArgs->end;
//     int* tab = threadArgs->tab;

//     for (int i = start; i <= end; i++) {
//         if (tab[i] == 1) {
//             for (int j = i * i; j <= end; j += i) {
//                 tab[j] = 0;
//             }
//         }
//     }

//     free(arg);
//     pthread_exit(NULL);
// }

// void EratosthenesParallel(int n, int* tab, int k) {
//     pthread_t* threads = (pthread_t*)malloc(k * sizeof(pthread_t));

//     // Calcul de la taille du travail par thread
//     int sqrt_n = sqrt(n);
//     int range = (n - sqrt_n) / k;

//     // Boucle externe
//     for (int i = 2; i <= sqrt_n; i++) {
//         if (tab[i] == 1) {
//             // Création et exécution des threads de travail
//             for (int t = 0; t < k; t++) {
//                 ThreadArgs* threadArgs = (ThreadArgs*)malloc(sizeof(ThreadArgs));
//                 threadArgs->start = sqrt_n + 1 + t * range;
//                 threadArgs->end = (t == k - 1) ? n : sqrt_n + (t + 1) * range;
//                 threadArgs->tab = tab;
//                 pthread_create(&threads[t], NULL, markMultiples, (void*)threadArgs);
//             }

//             // Attente de la fin des threads de travail
//             for (int t = 0; t < k; t++) {
//                 pthread_join(threads[t], NULL);
//             }
//         }
//     }

//     free(threads);
// }

// int main() {
//     int n;
//     int k;

//     printf("Entrez un entier n > 1 : ");
//     scanf("%d", &n);
//     printf("Entrez le nombre de threads k : ");
//     scanf("%d", &k);

//     if (n > 1) {
//         int* tab = (int*)malloc((n + 1) * sizeof(int));

//         // Initialisation de toutes les valeurs à vrai
//         for (int i = 2; i <= n; i++) {
//             tab[i] = 1;
//         }

//         EratosthenesParallel(n, tab, k);

//         // Affichage des nombres premiers
//         for (int i = 2; i <= n; i++) {
//             if (tab[i] == 1) {
//                 printf("%d ", i);
//             }
//         }
//         printf("\n");

//         free(tab);
//     } else {
//         printf("n doit être supérieur à 1.\n");
//     }

//     return 0;
// }
