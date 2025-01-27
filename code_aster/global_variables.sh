#!/bin/bash
# Define global variables for the installation
export ROOT=$(pwd)
export ARCH=gcc8-openblas-seq
export DEST=${ROOT}/prerequisites/${ARCH}
export BUILD=${ROOT}/.build-${ARCH}
export CACHE=/tmp/.cache_$(whoami)
export ARCHIVESDIR=${ROOT}/archives

# Ensure directories exist
mkdir -p $DEST/.installed $BUILD $CACHE $ARCHIVESDIR