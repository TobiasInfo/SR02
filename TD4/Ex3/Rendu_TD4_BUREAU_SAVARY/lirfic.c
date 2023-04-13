#include <stdio.h>
#include <fcntl.h>

void main(){
    int tab2[10];
    int i;
    // Ouverture du fichier
    int fd = open("titi.dat", O_RDWR, 0666);
    if(fd == -1){
        printf("Erreur lors de l'ouverture du fichier\n");
        perror("open");
        exit(-1);
    }
    //Lecture du fichier
    read(fd, tab2, 10*sizeof(int));
    close(fd);
    for(i=0; i<10; i++) 
        printf("%d\n",tab2[i]);
}