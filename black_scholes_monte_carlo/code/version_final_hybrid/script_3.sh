#!/bin/bash

# Définir les nombres de simulations et de runs à tester
SIMULATIONS=(100 1000 10000 1000000 10000000 50000000 100000000 200000000)
NUM_THREADS=(64 96 256 512)

# Fichier pour enregistrer les résultats
OUTPUT_FILE="results_vf.txt"

# Vider le fichier de sortie si il existe déjà
> $OUTPUT_FILE

# Boucle sur les différentes valeurs de num_simulations
for num_simulations in "${SIMULATIONS[@]}"; do
    # Boucle sur les différents nombres de threads
    for np in "${NUM_THREADS[@]}"; do
        echo "Running with $num_simulations simulations and $np threads..."

        # Exécuter le programme avec la configuration actuelle
        mpirun --oversubscribe -np $np ./BSM2 $num_simulations 1000000 >> $OUTPUT_FILE 2>&1

        # Ajouter un séparateur pour chaque exécution
        echo "--------------------------------------------------" >> $OUTPUT_FILE
    done
done

echo "All simulations completed. Results saved in $OUTPUT_FILE."

