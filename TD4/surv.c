#include "sharemem.h"

#define BLKSIZE 1024

int copierfichier(int f1, int f2){
    char buf[BLKSIZE];
    int octets_lus, octets_ecrits, total = 0;
    for(;;){
        if((octets_lus = read(f1, buf, BLKSIZE)) <= 0){
            break;
        }
        if((octets_ecrits = write(f2, buf, octets_lus)) == -1){
            break;
        }
        total += octets_ecrits;
    }
    return total;
}

int main(int argc, char *argv[]){
    int octets_lus, childpid, fd, fd1, fd2;
    if(argc == 3){
        fprintf(stderr,"Usage: %s <fichier1> <fichier2> \n", argv[0]);
        return 1;
    }
    if(((fd1 = open(argv[1], O_RDONLY)) == -1) || (fd2 = open(argv[2], O_RDONLY) == -1)){ // Vérifie si c'est bien ouvert
        perror("Echec");
        return 1;
    }
    if((childpid = fork()) == -1){
        perror("Echec");
        return 1;
    }
    if(childpid>0) // Parent code
        fd = fd1;
    else  // Child code
        fd = fd2;
    octets_lus = copierfichier(fd, STDOUT_FILENO);
    fprintf(stderr, "Octets Lus : %d \n", octets_lus);
    return 0;
}


// Compile : gcc -u prgm surv.c
// Run : ./prgm f1.data fé.data