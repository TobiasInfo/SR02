#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Syntaxe: %s fichier_à_inverser\n", argv[0]);
        exit(-1);
    }

    int fd = open(argv[1], O_RDWR);
    if(fd == -1) {
        printf("Erreur lors de l'ouverture du fichier\n");
        perror("open");
        exit(-1);
    }

    struct stat sb;
    fstat(fd, &sb); // Cette fonction nous permet de récupérer les informations sur le fichier (dans notre cas la taille)

    int *fichier = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int *fichier_inverse = malloc(sb.st_size); // nouvelle zone de mémoire pr le contenu inversé
    int i = sb.st_size / sizeof(int) - 1; // On commence à la fin du premier fichier
    int j = 0; // On écrit au début du fichier à inverser
    while (i >= 0) {
        fichier_inverse[j] = fichier[i]; // copie des caractères inversés
        i--;
        j++;
    }
    memcpy(fichier, fichier_inverse, sb.st_size); // copie de la nouvelle zone de mémoire dans le fichier
    printf("Le contenu du fichier a été inversé avec succès\n");
    munmap(fichier, sb.st_size); // libération de la mémoire
    free(fichier_inverse); // libération de la mémoire alouée dynamiquement
    close(fd);
    return 0;
}