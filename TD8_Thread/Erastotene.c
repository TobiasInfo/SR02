#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void Eratosthenes(unsigned long n, unsigned long *tab) {
    for (unsigned long i = 2; i <= n; i++) {
        tab[i] = 1;
    }

    unsigned long racine = sqrt(n);
    for (unsigned long i = 2; i <= racine; i++) {
        if (tab[i] == 1) {
            for (unsigned long j = i * i; j <= n; j += i) {
                tab[j] = 0;
            }
        }
    }
}

void PrintTab(unsigned long n, unsigned long *tab) {
    for (unsigned long i = 2; i <= n; i++) {
        if (tab[i] == 1) {
            printf("%lu ", i);
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    unsigned long n = atol(argv[1]);
    
    // printf("Entrez un entier n > 1 : ");
    // scanf("%lu", &n);

    if (n > 1) {
        unsigned long *tab = (unsigned long *)malloc((n+1) * sizeof(unsigned long));
        clock_t start, end;
        double temps_execution;

        start = clock();
        Eratosthenes(n, tab);
        end = clock();

        temps_execution = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%f\n", temps_execution);
        // PrintTab(100, tab);

        free(tab);
    } else {
        printf("n doit être supérieur à 1.\n");
    }

    return 0;
}
