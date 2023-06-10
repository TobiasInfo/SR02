
## Interprétation des résultats

La similarité des points pour 500 000 et 1 000 000 indique que les temps d'exécution sont assez uniformes, ce qui suggère que les différentes implémentations ne génèrent pas de performances nettement meilleures.  

À partir de la valeur 2 000 000, une dispersion des valeurs devient apparente, ce qui met en évidence les différences d'implémentation de manière plus marquée. On peut observer deux groupes principaux de valeurs. Le premier groupe se situe autour de 0,030 secondes, tandis que le second groupe se situe autour de 0,036 secondes.  

Le premier groupe est constitué des implémentations utilisant des threads pour les valeurs de k égales à 1, 2, 3, 4 et 6. Le second groupe comprend l'implémentation séquentielle ainsi que celle utilisant des threads pour les valeurs de k égales à 5 et 7.  

En utilisant la valeur 4 000 000, ces résultats précédents sont confirmés, et la valeur optimale de k (k=3) est obtenue. On observe que pour les valeurs de k égales à 1, 2, 4 et 6, les temps d'exécution restent assez proches. Ainsi, les différences de nombre de threads n'ont pas d'impact significatif sur le temps d'exécution des programmes.  

Afin de calculer l'intervalle de confiance sur ces valeurs, nous pouvons poser X la variable aléatoire repésentant le temps d'exécution du programme. Ensuite, nous devons calculer la moyenne de x ainsi que son équart type.  
Nous pouvons poser un niveau de confiance alpha*.  
Dans notre cas, on peut prendre un niveau de confiance alpha* = 95%.  
L'intervalle de confiance est donné par la formule : IC = [Moyenne de X + (quantile_d'une_loi_de_student_à_1_degre_de_liverte_au_niveau_alpha* * Ecart type / sqrt(nombre de valeurs)), Moyenne de X + (quantile_d'une_loi_de_student_à_1_degre_de_liverte_au_niveau_alpha* * Ecart type / sqrt(nombre de valeurs))].  