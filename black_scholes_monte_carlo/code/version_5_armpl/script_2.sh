#!/bin/bash

# Nom du fichier de sortie
OUTPUT_FILE="results_v5.csv"

# Ajouter les en-têtes au fichier CSV
echo "Price,Time" > $OUTPUT_FILE

# Liste des configurations à tester (num_simulations et num_runs)
CONFIGURATIONS=(
    "100 1000000"
    "1000 1000000"
    "10000 1000000"
    "100000 1000000"
)

# Boucle pour chaque configuration
for CONFIG in "${CONFIGURATIONS[@]}"; do
    # Extraire les valeurs de num_simulations et num_runs
    NUM_SIMULATIONS=$(echo $CONFIG | cut -d' ' -f1)
    NUM_RUNS=$(echo $CONFIG | cut -d' ' -f2)

    # Exécution du programme C++ avec les paramètres
    RESULT=$(./BSM $NUM_SIMULATIONS $NUM_RUNS)
    
    # Extraire le prix et le temps d'exécution du résultat
    PRICE=$(echo $RESULT | grep -oP 'value= \K[0-9.]+')
    TIME=$(echo $RESULT | grep -oP 'in \K[0-9.]+')

    # Ajouter les résultats au fichier CSV
    echo "$PRICE,$TIME" >> $OUTPUT_FILE

    # Affichage des résultats
    echo "Configuration: $NUM_SIMULATIONS simulations, $NUM_RUNS runs"
    echo "Prix estimé: $PRICE, Temps d'exécution: $TIME"
    echo "-----------------------------"
done

echo "Les résultats ont été enregistrés dans $OUTPUT_FILE"