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

//Compteurs de SIGINT
//Hypothèse : les compteurs de SIGINT sont indépendants 
int cptPere = 0;
int cptFils = 0;


// Fonction fils
void captfils(){
    rectvert(5);
    cptFils++;
    
    // 3 SIGINT Recu pour le processus fils
    if(cptFils == 3){
        detruitrec();
        exit(0);
    }
}


//Fonction pere
void captpere(){
    cptPere++;
    printf("PERE %d : signal %d recu\n", getpid(),cptPere);
    fflush(stdout);
    
    //Si 3 SIGINT reçus pour le père
    if(cptPere == 3){
        printf("PERE : fin du pere , trois signals sont deja recu\n");
        fflush(stdout);
        exit(0);
    }
}


//------------------------------------------------------------------------------------------

//Main

int main(){
    fils_pid = fork();
    
    //Partie Processus fils
    if (fils_pid == 0){
    int i =0;
        initrec();
        ActFils.sa_handler = captfils;
        sigaction(SIGINT, &ActFils, 0);
        
        //Tant qu'on ne clic pas sur le boutton de fin
        while (i != -1)
        {
            i = attendreclic();
            
            //On clic sur 0
            if(i==0){
            	printf("FILS envoit au PERE\nFILS :  pid du mon pere est : %d\n", getppid());
            	fflush (stdout);
            
            //Envoie du SIGINT au père
                kill(getppid(), SIGINT);
            }
            
            //On clic sur autre chose que 0
            else {
            printf("FILS :  pid de mon pere est : %d \n", getppid());
            fflush(stdout);
            }
        }
        
        // Après clic sur fin 
	printf("FILS :fin du fils apres clic sur FIN\n");
	fflush(stdout);
	exit(0);
    } 
    
    // Partie processus père
    else if (fils_pid > 0){
        ActPere.sa_handler = captpere;
        sigaction(SIGINT, &ActPere, 0);
        
        // Attente pour être sur que le sigaction 
        // du fils a bien été pris en compte
        sleep(1);
        int n;
        while (1)
        {
            n = sleep(10);
            printf("temps restant : %d \n", n);
            fflush(stdout);
        }
        
    } 
    
    // Si on a pas réussi à créer le fils
    else {
        printf("Erreur de création du fils");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}
