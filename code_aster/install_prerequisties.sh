#!/bin/bash

# Répertoire racine
ROOT=$(pwd)
ARCH=gcc8-openblas-seq  # Par défaut, peut être ajusté si nécessaire
NUMVERS=20240327        # Version par défaut

# Définir les chemins
export DEST="$ROOT/$NUMVERS/$ARCH"
export BUILD="$ROOT/.build-$ARCH"
export CACHE="/tmp/.cache_$(whoami)"
export ARCHIVESDIR="$ROOT/archives"

# Créer les répertoires nécessaires
mkdir -p "$DEST/.installed" "$BUILD" "$CACHE" "$ARCHIVESDIR"

# Fonction pour installer un produit
install_product() {
  PRODUCT=$1
  echo -e "\n***************** Installing $PRODUCT *******************\n"

  # Définir les chemins spécifiques au produit
  LOG_FILE="$BUILD/$PRODUCT.log"
  LOG_GZ_FILE="$DEST/.installed/$PRODUCT.log.gz"
  PASSED_FILE="$BUILD/$PRODUCT.passed"

  # Exécuter le script d'installation pour le produit
  rm -f "$PASSED_FILE"
  ./src/"$PRODUCT".sh 2>&1 | tee "$LOG_FILE"

  if [ $? -eq 0 ]; then
    gzip -c "$LOG_FILE" > "$LOG_GZ_FILE"
    echo "passed" > "$PASSED_FILE"
    echo "$PRODUCT installed successfully."
  else
    echo "Error installing $PRODUCT. Check the logs at $LOG_FILE."
    exit 1
  fi
}

# Exporter les variables spécifiques pour HDF5
export_hdf5() {
  export HDF5_HOME="$DEST/hdf5-1.10.9"
  export CPPFLAGS="-I$HDF5_HOME/include"
  export LDFLAGS="-L$HDF5_HOME/lib"
  echo "HDF5 environment variables set."
}

# Exporter les variables spécifiques pour MED
export_med() {
  export MED_HOME="$DEST/med-4.1.1"
  export CPPFLAGS="-I$MED_HOME/include"
  export LDFLAGS="-L$MED_HOME/lib"
  echo "MED environment variables set."
}

# Lancer l'installation des prérequis
install_all() {
  PRODUCTS=("hdf5" "med" "metis" "parmetis" "mumps" "petsc" "medcoupling")
  
  for PRODUCT in "${PRODUCTS[@]}"; do
    install_product "$PRODUCT"
  done
}

# Option pour récapituler l'installation
recap() {
  echo "Installation recap:"
  for PRODUCT in "${PRODUCTS[@]}"; do
    if [ -f "$DEST/.installed/$PRODUCT.passed" ]; then
      echo "$PRODUCT: Installed successfully."
    else
      echo "$PRODUCT: Not installed."
    fi
  done
}

# Menu principal
echo "Starting the installation of prerequisites for Code_Aster..."
install_all
export_hdf5
export_med
recap

echo "All prerequisites installed successfully. Exiting."