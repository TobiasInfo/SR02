#include "semaph.h"
/* 
éalise les fonctions suivantes :
1. Création d'un segment de mémoire partagée pouvant contenir un entier E.
2. Initialisation à 0 de l'entier E en mémoire partagée.
3. Création d'un process "fils" partageant le segment précédemment créé avec son "père"
*/

int main(){
    int E;
    shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    E = 0;
    pid_t pid;
    pid = fork();
    if(pid == 0){
        printf("Fils : %d\n", E);
        E++;
        printf("Fils : %d\n", E);
    }
    return 0;
}
