#include "sem_pv.h"

static int semid = -1;

union semun{
    int val ; // pour SETVAL
    struct semid_ds *buf ; // pour IPC_SET et IPC_STAT
    int *array ; // pour GETALL et SETALL
};

// struct sembuf{
//     unsigned short int sem_num; /* numéro de sémaphore cible de l'opération */
//     short sem_op ; /* opération sur le sémaphore */
//     short sem_flg ; /* option : IPC_NOWAIT, SEM_UNDO */ 
// };

int init_semaphore(void){
    int i;
    union semun arg;
    arg.val = 0;
    if(semid != -1){
        printf("Semaphore already initialized\n");
        return -1;
    }
    if((semid = semget(IPC_PRIVATE, N_SEM, IPC_CREAT | 0666)) == -1){
        printf("Error creating semaphore\n");
        return -2;
    }
    for(i = 0; i < N_SEM; i++){
        semctl(semid, i, SETVAL, arg);
    }
    return 0;
}

int detruire_semaphore(void){
    int retour = -1;
    if(semid == -1){
        printf("Semaphore not initialized\n");
        return -1;
    }
    if((retour = semctl(semid, 0, IPC_RMID, 0) )== -1){
        // 0 is ignored in this case
        printf("Error destroying semaphore\n");
        return -2;
    }
    semid = -1;
    return retour;
}

/* int val_sem(int sem, int val)
Attribue la valeur "val" au sémaphore "sem" du groupe de sémaphores créé par "init_semaphore".
Retourne la valeur de retour de "semctl" en cas de réussite, -1 si "init_semaphore" n'a pas été
appelé avant, -2 si le numéro de sémaphore est incorrect.*/


int val_sem(int sem, int val){
    int retour = -1;
    union semun arg;
    if(semid == -1){
        printf("Semaphore not initialized\n");
        return -1;
    }
    if(sem < 0 || sem >= N_SEM){
        printf("Semaphore number incorrect\n");
        return -2;
    }
    arg.val = val;
    if((retour = semctl(semid, sem, SETVAL, arg) )== -1){
        printf("Error setting semaphore value\n");
        return -2;
    }
    return retour;
}

/* int P(int sem)
Réalise l'opération (P) sur le sémaphore numéro "sem" du groupe de sémaphores créé par
"init_semaphore".
Retourne la valeur de retour de "semop" en cas de réussite, -1 si "init_semaphore" n'a pas été
appelé avant, -2 si le numéro de sémaphore est incorrect.*/


int P(int sem){
    int retour = -1;
    struct sembuf op;
    if(semid == -1){
        printf("Semaphore not initialized\n");
        return -1;
    }
    if(sem < 0 || sem >= N_SEM){
        printf("Semaphore number incorrect\n");
        return -2;
    }
    op.sem_num = sem;
    op.sem_op = -1;   
    // op.sem_flg = 0; // On ne l'utilise pas, c'est pour voir si on peut faire des opérations en mode bloquant ou non
    if((retour = semop(semid, &op, 1)) == -1){
        printf("Error performing P operation\n");
        return -2;
    }
    return retour;
}


/* int V(int sem)
Réalise l'opération (V) sur le sémaphore numéro "sem" du groupe de sémaphores créé par
"init_semaphore".
Retourne la valeur de retour de "semop" en cas de réussite, -1 si "init_semaphore" n'a pas été
appelé avant, -2 si le numéro de sémaphore est incorrect.*/

int V(int sem){
    int retour = -1;
    struct sembuf op;
    if(semid == -1){
        printf("Semaphore not initialized\n");
        return -1;
    }
    if(sem < 0 || sem >= N_SEM){
        printf("Semaphore number incorrect\n");
        return -2;
    }
    op.sem_num = sem;
    op.sem_op = 1;
    // op.sem_flg = 0;
    if((retour = semop(semid, &op, 1)) == -1){
        printf("Error performing V operation\n");
        return -3;
    }
    return retour;
}


// int main() {
//     int E;
//     int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
//     int *shmaddr = (int*)shmat(shmid, NULL, 0);
//     *shmaddr = 0;
    
//     pid_t pid;
//     pid = fork();
    
//     if (pid == 0) {
//         // child
//         srand(getpid()); // Seed the random number generator with child's process ID
//         for (int i = 0; i < 100; i++) {
//             int A = *shmaddr;
//             usleep(rand() % 81 + 20);
//             A++;
//             *shmaddr = A;
//             usleep(rand() % 81 + 20);
//         }
//         shmdt(shmaddr); // Detach shared memory segment from the child process
//     } else {
//         // parent
//         srand(getpid()); // Seed the random number generator with parent's process ID
//         for (int i = 0; i < 100; i++) {
//             int A = *shmaddr;
//             usleep(rand() % 81 + 20);
//             A++;
//             *shmaddr = A;
//             usleep(rand() % 81 + 20);
//             printf("E Pere = %d\n", *shmaddr);
//             fflush(stdout);
//         }
//         shmdt(shmaddr); // Detach shared memory segment from the parent process
//         shmctl(shmid, IPC_RMID, NULL); // Mark shared memory segment for deletion
//     }
    
//     return 0;
// }