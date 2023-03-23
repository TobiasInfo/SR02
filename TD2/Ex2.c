#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>


struct sigaction ActFils;
struct sigaction ActPere;
pid_t fils_pid;
int cpt = 0;
char cfils = 'a';
char cpere = 'A';

void fonction_fils(){
    cpt++;
    for (int i = 0; i < cpt && cfils <= 'z'; i++){
        printf("%c", cfils);
        fflush(stdout);
        cfils++;
    }
    kill(getppid(), SIGUSR1);
    if(cfils > 'z'){
        exit(0);
    }
}

void fonction_pere(){
    cpt++;
    for (int i = 0; i < cpt && cpere <= 'Z'; i++){
        printf("%c", cpere);
        fflush(stdout);
        cpere++;
    }
    if(cpere > 'Z'){
        exit(0);
    }
    kill(fils_pid, SIGUSR1);
}

int main(){
    fils_pid = fork();
    if (fils_pid == 0){
        ActFils.sa_handler = fonction_fils;
        sigaction(SIGUSR1, &ActFils, 0);
        while (1)
        {
            pause();
        }
        
    } else if (fils_pid > 0){
        ActPere.sa_handler = fonction_pere;
        sigaction(SIGUSR1, &ActPere, 0);
        sleep(1);
        kill(fils_pid, SIGUSR1);
        while (1)
        {
            pause();
        }
    } else {
        printf("Erreur de création du fils");
    }
    printf("\n");

}
