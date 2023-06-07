#include <stdio.h>
#include "time.h"

int main(void){
    printf("init : %d\n", init_semaphore());
    printf("val_sem : %d\n", val_sem(2, 0));
    printf("P : %d \n",P(2));
    sleep(5);
    printf("V : %d \n",V(2));
    printf("Detruire : %d \n",detruire_semaphore());
    return 0;
}