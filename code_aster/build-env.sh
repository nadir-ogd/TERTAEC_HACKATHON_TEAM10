#!/bin/bash
# Load necessary environment variables for Code_Aster prerequisites
export PATH=/tools/openmpi/5.0.6/acfl/24.10/bin:$PATH
export LD_LIBRARY_PATH=/tools/openmpi/5.0.6/acfl/24.10/lib:$LD_LIBRARY_PATH
export CC=mpicc
export CXX=mpicxx
export FC=gfortran