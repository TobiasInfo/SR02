#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>


struct sigaction ActFils;
struct sigaction ActPere;
pid_t fils_pid;

void fonction_fils(){
    int val = rand() % 30 + 10;
    printf("%d", val);
    fflush(stdout);
}

void fonction_pere(){
    kill(fils_pid, SIGUSR1);
    alarm(5);
}

int main(){
    printf("INIT");
    fils_pid = fork();
    if (fils_pid == 0){
        // printf("Je suis le fils");
        ActFils.sa_handler = fonction_fils;
        sigaction(SIGUSR1, &ActFils, 0);
        while(1){
            pause();
        }
    } else if (fils_pid > 0){
        // printf("Je suis le pere");
        ActPere.sa_handler = fonction_pere;
        sigaction(SIGALRM, &ActPere, 0);
        alarm(5);
        while(1){
            sleep(1);
            printf("-");
            fflush(stdout); // Pour afficher le printf sans attendre le retour à la ligne (vide le buffer)
        }
    } else {
        printf("Erreur de création du fils");
    }

}
