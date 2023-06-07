#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Eratosthenes(int n, int *tab) {

    // Initialisation de toutes les valeurs à vrai
    for (int i = 2; i <= n; i++) {
        tab[i] = 1;
    }

    int racine = sqrt(n);
    for (int i = 2; i <= racine; i++) {
        if (tab[i] == 1) {
            // Marquer tous les multiples de i comme faux
            for (int j = i * i; j <= n; j += i) {
                tab[j] = 0;
            }
        }
    }

}

int PrintTab(int n, int *tab) {
    // Affichage des nombres premiers
    for (int i = 0; i <= n; i++) {
        if (tab[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

    
int main() {
    int n;
    int *tab = (int *)malloc((n+1) * sizeof(int));

    printf("Entrez un entier n > 1 : ");
    scanf("%d", &n);

    if (n > 1) {
        Eratosthenes(n, tab);
        PrintTab(n, tab);
    } else {
        printf("n doit être supérieur à 1.\n");
    }
    free(tab);
    return 0;
}
