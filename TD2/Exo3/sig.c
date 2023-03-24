#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>


//Variables globales
struct sigaction ActFils;
struct sigaction ActPere;
pid_t fils_pid;
int cptPere = 0;
int cptFils = 0;


// Fonction fils
void captfils(){
    rectvert(5);
    cptFils++;
    if(cptFils == 3){
        detruitrec();
        exit(0);
    }
}


//Fonction pere
void captpere(){
    cptPere++;
    printf(" PERE %d : signal %d recu\n", getpid(),cptPere);
    fflush(stdout);
    if(cptPere == 3){
        printf("  PERE : fin du pere , trois signals sont deja recu\n");
        fflush(stdout);
        exit(0);
    }
}

int main(){
    fils_pid = fork();
    if (fils_pid == 0){
        initrec();
        ActFils.sa_handler = captfils;
        sigaction(SIGINT, &ActFils, 0);
        int i = attendreclic();
        while (i != -1)
        {
            if(i==0){
            printf("FILS envoit au PERE\nFILS : pid de mon pere est : %d\n", getppid());
            fflush (stdout);
                kill(getppid(), SIGINT);
            }
            printf(" FILS :  pid du mon pere est : %d \n", getppid());
            fflush(stdout);
            i = attendreclic();
        }

        
    } else if (fils_pid > 0){
        ActPere.sa_handler = captpere;
        sigaction(SIGINT, &ActPere, 0);
        sleep(1);
        // kill(fils_pid, SIGINT);
        int n;
        while (1)
        {
            n = sleep(10);
            printf("temps restant : %d \n", n);
            fflush(stdout);
            //printf("temps restant : %d \n", n);
            // fflush(stdout);
            // ecritreceived(n);
        }
    } else {
        printf("Erreur de création du fils");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}
