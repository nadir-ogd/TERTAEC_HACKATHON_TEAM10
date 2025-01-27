#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <num_simulations> <num_runs>"
    exit 1
fi

SIMULATIONS=$1
RUNS=$2

LINAFORGE_DIR="linaforge_dir"
EXECUTABLE="./BSM"  

TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
RESULTS_DIR="${LINAFORGE_DIR}/linaforge_results_${TIMESTAMP}"

mkdir -p "$RESULTS_DIR"

echo "Running Linaro Forge MAP hotspot analysis with $SIMULATIONS simulations and $RUNS runs..."

# Profiler avec Linaro Forge MAP
map --profile --output=$RESULTS_DIR/map_output.map -- $EXECUTABLE $SIMULATIONS $RUNS

if [ $? -eq 0 ]; then
    echo "Linaro Forge MAP hotspot analysis completed successfully. Results stored in $RESULTS_DIR"
else
    echo "Linaro Forge profiling failed. Check the output for errors."
    exit 1
fi

map --export-functions=$RESULTS_DIR/hotspot_report.csv --input=$RESULTS_DIR/map_output.map
map --report summary --input=$RESULTS_DIR/map_output.map --output=$RESULTS_DIR/summary.txt

# Fichier de résultats CSV
OUTPUT_FILE="results_v2.csv"
echo "Price,Time" > $OUTPUT_FILE

# Liste des configurations à tester
CONFIGURATIONS=(
    "100 1000000"
    "1000 1000000"
    "10000 1000000"
    "100000 1000000"
)

# Boucle pour chaque configuration
for CONFIG in "${CONFIGURATIONS[@]}"; do
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
exit 0

