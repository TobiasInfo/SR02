#include "sharemem.h"

#define BLKSIZE 1024

#define PERM (S_IRUSR | S_IWUSR)
#define SHMZ 27

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

int statchAndRemove(int shmid, char *shmdt){
    int error = 0;
    if(shmdt(shmdt) == -1){
        error = errno;
    }
    if(shmdt(shmid, IPC_RMID, NULL) == -1 && !error){
        error = errno;
    }
    if(!error){
        return 0;
    }
}