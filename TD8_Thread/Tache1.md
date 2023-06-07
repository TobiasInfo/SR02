# Tache 1

### Dérouler l’exécution de cette algorithme avec n=20

1.
A) Initialisation du tableau
A = [Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai]

B) Boucle for sur i
Parcour des valeurs de i de 2 à sqrt(20) , soit i = 2, 3, 4.

i = 2:

    A[2] est vrai,
    On met à faux toutes les valeurs de j = 4, 6, 8, 10, 12, 14, 16, 18, 20 dans le tableau A.
    Le tableau A devient : [Vrai, Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux]

i = 3:

    A[3] est vrai, 
    On met à faux toutes les valeurs de j = 9, 12, 15, 18 dans le tableau A.
    Le tableau A devient : [Vrai, Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux]

i = 4:

    A[4] est faux, on pass à l'itération suivante.

C) Résultat final
Après avoir parcouru toutes les valeurs de i, le tableau A contient les informations sur les nombres premiers jusqu'à 20. Les indices pour lesquels A[i] est vrai correspondent aux nombres premiers.

Le tableau A final est le suivant : [Vrai, Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux]

Donc, les nombres premiers jusqu'à 20 sont : 1, 2, 3, 5, 7, 11, 13, 17, 19.

2. La boucle interne commence à i^2 au lieu de 0 ou i pour des raisons d'efficacité.

L'algorithme utilise le crible d'Ératosthène pour trouver les nombres premiers jusqu'à n. L'idée du crible d'Ératosthène est que tous les multiples d'un nombre ne sont pas premiers, ils peuvent donc être supprimés. Ainsi, au lieu de parcourir tous les multiples de i, la boucle interne commence à i^2 pour éliminer tous les multiples précédents qui ont déjà été marqués comme non premiers par des valeurs de i plus petites.


Supposons que i soit un nombre premier. Si nous commençons à i ou à une valeur inférieure à i^2, on passe sur des multiples de nombres premiers précédents, ce qui serait redondant. Par exemple, si i = 3, en commencant à 3^2 = 9 on ne passe pas par 6 (multiple de 2) et 3 (multiple de 3), car ils a déjà été marqués comme non premiers lors des itérations précédentes.

En commençant à i^2, on est sur que chaque multiple antérieur a déjà été marqué comme non premier, ce qui permet de réduire le nombre  d'itérations. Ce départ à i^2 constitue donc principalement une optimisation de l'algorithme puisque les itérations avant i^2 ne seraient pas nécéssaires.  

3. La première boucle s'exécute jusqu'à sqrt(n) pour des raisons d'efficacité. L'objectif de cette boucle est de marquer tous les multiples des nombres premiers jusqu'à sqrt(n) comme non premiers.

Si sqrt(n) n'est pas un entier, nous prenons la partie entière inférieur de sqrt(n).

Dans le cas où sqrt(n) est un entier, la première boucle s'exécute normalement de 2 à sqrt(n) inclus, couvrant ainsi tous les multiples des nombres premiers jusqu'à sqrt(n).

L'objectif est de limiter le nombre d'itérations nécessaires, car après sqrt(n), nous n'avons plus besoin de vérifier les multiples des nombres premiers plus grands que √n, car ils ont déjà été traités lors des itérations précédentes.(Cette propriété est une propriété toujours vrai pour les nombres premiers.) Cela permet d'optimiser l'algorithme et d'améliorer son efficacité.

# TODO : Ajouter explication Marius