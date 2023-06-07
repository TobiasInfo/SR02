# Tache 1

### Dérouler l’exécution de cette algorithme avec n=20

1. Initialisation du tableau
A = [Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai, Vrai]

2. Boucle for sur i
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

3. Résultat final
Après avoir parcouru toutes les valeurs de i, le tableau A contient les informations sur les nombres premiers jusqu'à 20. Les indices pour lesquels A[i] est vrai correspondent aux nombres premiers.

Le tableau A final est le suivant : [Vrai, Vrai, Vrai, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux, Faux, Faux, Vrai, Faux, Vrai, Faux]

Donc, les nombres premiers jusqu'à 20 sont : 1, 2, 3, 5, 7, 11, 13, 17, 19.

