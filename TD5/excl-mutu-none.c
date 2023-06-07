#include "semaph.h"
/* 
éalise les fonctions suivantes :
1. Création d'un segment de mémoire partagée pouvant contenir un entier E.
2. Initialisation à 0 de l'entier E en mémoire partagée.
3. Création d'un process "fils" partageant le segment précédemment créé avec son "père"
*/

/*
Créer un programme "excl-mutu-none.c" qui réalise les fonctions suivantes :
1. Création d'un segment de mémoire partagée pouvant contenir un entier E.
2. Initialisation à 0 de l'entier E en mémoire partagée.
3. Création d'un process "fils" partageant le segment précédemment créé avec son "père".
Chaque process (père et fils) exécute ensuite 100 fois le code suivant, dont les quatre premières lignes
constituent une section critique :
1. Affecter E à une variable A, entière, locale au process.
2. Attendre entre 20 et 100 ms (Utilisez les fonctions usleep(3) et rand(3V)).
3. Incrémenter A.
4. Affecter la variable locale A à la variable "partagée" E.
5. Attendre entre 20 et 100 ms (Utilisez les fonctions usleep(3) et rand(3V)).
6. Affichage dans le processus père de la valeur de E.
2022/2023
*/

int main(){
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    pid_t pid;
    init_semaphore();
    val_sem(3, 1);
    pid = fork();
    int* adrE = shmat(shmid, NULL, 0);
    *adrE = 0;
    if(pid == 0){
        // child
        srand(getpid());
        int A;
        for (int i = 0; i < 100; i++){
            P(3);
            A = *adrE;
            usleep(rand() % 80 + 20);
            A++;
            *adrE = A;
            V(3);
            usleep(rand() % 80 + 20);
        }
        shmdt(adrE);
    } else {
        // parent
        srand(getpid());
        int A;
        for (int i = 0; i < 100; i++){
            P(3);
            A = *adrE;
            usleep(rand() % 80 + 20);
            A++;
            *adrE = A;
            V(3);
            usleep(rand() % 80 + 20);
            printf("E Pere= %d\n", *adrE);
            fflush(stdout);
        }
        shmdt(adrE);
        shmctl(shmid, IPC_RMID, NULL);
    }
    detruire_semaphore();
    return 0;
}
