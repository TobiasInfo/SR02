#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


void main(int argc, char* argv[]){
    int i;
    struct stat file_stat;
    char* addr;
    int file;
    int* tab1;
     // Ouverture du fichier
    file = open("titi.dat",O_RDWR, 0666);
    if(file == -1){
        printf("Erreur lors de l'ouverture du fichier\n");
        perror("open");
        exit(-1);
    }
    
    // Récupération des informations du fichier
    fstat(file, &file_stat);

    //Ouverture de la mémoire partagé
    tab1 = mmap(NULL,file_stat.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,file,0);
    close(file);
    //Boucle sur i
    while (1){
        printf("Rentrez i \n");
        scanf(" %d",&i);
        if (i == 99){
            // Sortie du programme
            munmap(tab1, file_stat.st_size);
            exit(0);
        }
        // Incrémentation du nombre de 1 à l'indice [i] dans le segment de la mémoire partagée
        else if( i >= 0 && i <= 9){
            tab1[i]++;
        }
    }

    // Libération de la mémoire partagée
    munmap(tab1, file_stat.st_size);
    return 0;
}