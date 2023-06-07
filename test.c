#include <unistd.h>
#include <stdio.h>
int main(void) {
int i = 0;
for (i = 0; i < 2; ++i) {
    int p = fork();
    if(p == 0){
        printf("\nfils\n");
    }
    else if(p == -1){
        printf("erreur\n");
    }
    else{
        printf("\npere\n");
    }
    printf("%d", i);
}
printf("\n");
return 0;
}