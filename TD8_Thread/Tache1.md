# Tache 1

### Dérouler l’exécution de cette algorithme avec n=20

1.
A) Initialisation du tableau
A = [Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai]

B) Boucle for sur i
Parcour des valeurs de i de 2 à sqrt(20) , soit i = 2, 3, 4.

i = 2:

    A[2] est vrai,
    On met à faux toutes les valeurs de j = 4, 6, 8, 10, 12, 14, 16, 18, 20 dans le tableau A.
    Le tableau A devient : [Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux, Vrai, Faux]

i = 3:

    A[3] est vrai, 
    On met à faux toutes les valeurs de j = 9, 12, 15, 18 dans le tableau A.
    Le tableau A devient : [Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux]

i = 4:

    A[4] est faux, on passe à l'itération suivante.

C) Résultat final
Après avoir parcouru toutes les valeurs de i, le tableau A contient les informations sur les nombres premiers jusqu'à 20. Les indices pour lesquels A[i] est vrai correspondent aux nombres premiers.

Le tableau A final est le suivant : [Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux]

Donc, les nombres premiers jusqu'à 20 sont : 2, 3, 5, 7, 11, 13, 17, 19.

2. La boucle interne commence à i^2 au lieu de 0 ou i pour des raisons d'efficacité.

L'algorithme utilise le crible d'Ératosthène pour trouver les nombres premiers jusqu'à n. L'idée du crible d'Ératosthène est que tous les multiples d'un nombre ne sont pas premiers, ils peuvent donc être supprimés. Ainsi, au lieu de parcourir tous les multiples de i, la boucle interne commence à i^2 pour éliminer tous les multiples précédents qui ont déjà été marqués comme non premiers par des valeurs de i plus petites.


Supposons que i soit un nombre premier. Si nous commençons à i ou à une valeur inférieure à i^2, on passe sur des multiples de nombres premiers précédents, ce qui serait redondant. Par exemple, si i = 3, en commencant à 3^2 = 9 on ne passe pas par 6 (multiple de 2) et 3 (multiple de 3), car ils ont déjà été testés précédemment.

En commençant à i^2, on est sur que chaque multiple antérieur a déjà été marqué comme non premier, ce qui permet de réduire le nombre  d'itérations. Ce départ à i^2 constitue donc principalement une optimisation de l'algorithme puisque les itérations avant i^2 ne seraient pas nécéssaires.  

3. La première boucle s'exécute jusqu'à sqrt(n) pour des raisons d'efficacité. L'objectif de cette boucle est de marquer tous les multiples des nombres premiers jusqu'à sqrt(n) comme non premiers.

Si sqrt(n) n'est pas un entier, nous prenons la partie entière inférieur de sqrt(n).

Dans le cas où sqrt(n) est un entier, la première boucle s'exécute normalement de 2 à sqrt(n) inclus, couvrant ainsi tous les multiples des nombres premiers jusqu'à sqrt(n).

L'objectif est de limiter le nombre d'itérations nécessaires, car après sqrt(n), nous n'avons plus besoin de vérifier les multiples des nombres premiers plus grands que √n, car ils ont déjà été traités lors des itérations précédentes.(Cette propriété est une propriété toujours vrai pour les nombres premiers.) 

Lorsque nous cherchons tous les nombres premiers inférieurs ou égale à N, nous pouvons effectivement itérer sur les entiers i de 2 à N.

Cependant, il n'est pas nécessaire de vérifier tous les nombres jusqu'à N. Il suffit de vérifier jusqu'à la racine carrée de N. Cela est dû au fait que si un nombre non premier a un facteur qui est plus grand que sa racine carrée, il aurait déjà été multiplié par un autre facteur plus petit qui est inférieur à sa racine carrée.

Par conséquent, en vérifiant seulement jusqu'à la racine carrée de N, nous couvrons tous les cas et nous évitons les tests redondants.

"D'après le théorème des diviseurs premiers, si n n'est divisible par aucun des nombres premiers inférieur ou égaux à sa racine carrée, on peut affirmer qu'il est premier."

Cela permet d'optimiser l'algorithme et d'améliorer son efficacité.



# ChatGPT Optimisation de la dernière tache

### 1ère optimisation
Les deux cas distincts à traiter sont les suivants :

    Cas spécial pour le nombre 2 : Le nombre 2 est le seul nombre premier pair. Comme tous les autres nombres pairs sont exclus d'être premiers, nous devons traiter le cas spécial du nombre 2 séparément. Par conséquent, nous devons effectuer la boucle interne avec un pas de 2 au lieu de i lorsque i est égal à 2.

    Boucle interne pour les nombres impairs : Tous les autres nombres premiers sont impairs. Par conséquent, nous pouvons ignorer les nombres pairs lors de la boucle interne pour améliorer l'efficacité de l'algorithme. Nous effectuons donc la boucle interne avec un pas de 2i pour tous les nombres premiers impairs, en commençant par i^2.

En résumé, le premier cas distinct est celui du nombre 2 où nous utilisons un pas de 2 dans la boucle interne, tandis que le deuxième cas distinct est celui des autres nombres premiers impairs, pour lesquels nous utilisons également un pas de 2i dans la boucle interne.

### 2eme optimisation
Pour réduire l'espace mémoire utilisé par l'algorithme, nous pouvons utiliser un tableau plus petit et ne stocker que les booléens pour les nombres impairs supérieurs à 3. Voici comment effectuer cette modification :

    Initialisez un tableau isPrime de valeurs booléennes indexées de 0 à (n-2)/2, toutes initialisées à vrai. Le tableau isPrime sera moitié moins grand que le tableau A précédemment utilisé.
    Pour i = 0, 1, 2, ..., (√n - 3)/2 :
        Si isPrime[i] est vrai, cela signifie que le nombre k = 2 * i + 3 est premier.
        Effectuez la boucle interne avec un pas de 2k, en commençant à j = (k^2 - 3) / 2 et augmentant j de k à chaque itération (j += k).
        Marquez isPrime[j] comme faux.
    Les nombres premiers seront les nombres impairs supérieurs à 2 (i.e., k = 2 * i + 3) pour lesquels isPrime[i] est vrai.

Cette modification permet de réduire l'espace mémoire utilisé par le tableau en ne stockant que les booléens pour les nombres impairs supérieurs à 3. Ainsi, nous évitons de stocker les booléens pour les nombres pairs qui ne peuvent pas être premiers, ce qui réduit la taille du tableau et l'espace mémoire requis.


# TODO :
Clean nom fichiers
### Tache 1
Vérif Marius 
### Tache 4
Commenter graph 
### Tache 5 
Analyser l'impact
