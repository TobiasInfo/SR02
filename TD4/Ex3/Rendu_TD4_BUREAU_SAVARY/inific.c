#include <stdio.h>
#include <fcntl.h>

void main(){
    int tab1[10]={11,22,33,44,55,66,77,88,99,1000};
    int fd = open("titi.dat", O_RDWR|O_CREAT|O_TRUNC, 0666);
    if(fd == -1){
        printf("Erreur lors de l'ouverture du fichier\n");
        perror("open");
        exit(-1);
    }
    write(fd, tab1, 10*sizeof(int));
    close(fd);
    printf("Fichier initialisé\n");
}