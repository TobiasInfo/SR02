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