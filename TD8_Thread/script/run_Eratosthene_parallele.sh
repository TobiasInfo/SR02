#!/bin/bash

program="../exe/Eratosthene_parallele"
output_file="../resultats/Eratosthene_parallele.txt"
compile="gcc ../src/Eratosthene_parallele.c -o ../exe/Eratosthene_parallele -lm"
values=(500000 1000000 2000000 4000000)

# Supprimer le fichier de résultats s'il existe déjà
if [ -f "$output_file" ]; then
    rm "$output_file"
fi

# Exécuter le programme pour chaque valeur de n
$compile
for value in "${values[@]}"; do
    echo "Exécution avec n = $value"
    echo "n = $value" >> "$output_file"
    for (( i=1; i<=30; i++ )); do
        echo "Essai $i"
        $program $value >> "$output_file"
    done
    echo "-------------------------------"
    echo "-------------------------------" >> "$output_file"
done

echo "Toutes les exécutions sont terminées. Les résultats sont enregistrés dans le fichier $output_file."