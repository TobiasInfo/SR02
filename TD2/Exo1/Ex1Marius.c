#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
 
pid_t pid_fils;
struct sigaction act_pere;
struct sigaction act_fils;
 
void fonction_fils(){
    int t = rand()%30+10;
    printf("%d",t);
    fflush(stdout);
}
 
void fonction_pere(){
    kill(pid_fils,SIGUSR1);
    alarm(5);
    
}
 
 
 
int main (){
 
    printf("Init\n");
    pid_fils = fork();
    if (pid_fils==0){
        act_fils.sa_handler=fonction_fils;
        sigaction(SIGUSR1,&act_fils,0);
        while(1)
            pause();
    }else{
        act_pere.sa_handler=fonction_pere;
        sigaction(SIGALRM,&act_pere,0);
        alarm(5);
        while(1){
            sleep(1);
            printf("-");
            fflush(stdout);
        }
    }
    return 0;
}