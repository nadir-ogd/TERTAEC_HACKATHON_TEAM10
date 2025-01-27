# Teratec Hackathon 2025 - Team 10

This repository contains our team's work for the Teratec Hackathon 2025, focusing on two main challenges:

## Challenges

### 1. Black-Scholes Monte Carlo Optimization
- Provided by Viridien
- Focus on optimization and parallelization for Arm-based architectures
- Implementation and testing on Graviton3/Graviton4 processors (Arm Neoverse)
- Progressive optimization from basic implementation to hybrid parallelization

### 2. Code_Aster Optimization
- Provided by EDF
- Industrial HPC application porting and optimization
- Focus on performance improvement for Arm architecture

The objective was to explore scalability, performance, and optimizations on Graviton3/Graviton4 processors (Arm Neoverse).

---

## Repository Structure

### **Report**
- **`report/`**: Contains a comprehensive report of all the work done, including findings, results, and conclusions.

---

### **Black-Scholes Monte Carlo**
Optimized implementation of the Black-Scholes Monte Carlo model, organized into progressive versions for clarity and reproducibility.

```plaintext
black_scholes_monte_carlo/
├── code/
│   ├── version_1_basic/               # Basic single-threaded implementation
│   │   ├── BSM_v1.cxx                 # Source code for the basic version
│   │   ├── Makefile                   # Makefile for building the basic version
|   |   └── script_1.sh                # Script to execute this version across multiple simulation configurations
|   |   
│   ├── version_2_math_opt/            # Version with mathematical optimizations
│   │   ├── BSM_v2.cxx                 # Added optimized math functions
│   │   ├── Makefile                   # Makefile for this version
|   |   └── script_1.sh                # Script to execute this version across multiple simulation configurations
|   | 
│   ├── version_3_openmp/              # OpenMP-enabled version for thread-level parallelism
│   │   ├── BSM_v3.cxx                 # OpenMP-parallelized source code
│   │   ├── Makefile                   # Makefile for OpenMP
|   |   └── script_2.sh                # Script to execute this version across multiple simulation configurations
|   |                          
│   ├── version_4_mpi/                 # MPI-based parallel version for distributed execution
│   │   ├── BSM_v4.cxx                 # Source code using MPI
│   │   ├── Makefile                   # Makefile for MPI
|   |   └── script_3.sh                # Script to execute the MPI version with varying numbers of simulations and threads
|   |  
│   ├── version_5_armpl/               # Optimized using ARMPL for numerical routines and RNG
│   │   ├── BSM_v5.cxx                 # Uses ARMPL's CBLAS and RNG features
│   │   ├── Makefile                   # Makefile linking ARMPL
|   |   └── script_2.sh                # Script to execute the MPI version with varying numbers of simulations and threads
|   |
│   ├── version_6_armpl_openmp/        # Combines ARMPL and OpenMP for further optimization
│   │   ├── BSM_v6.cxx                 # Hybrid ARMPL + OpenMP implementation
│   │   ├── Makefile                   # Makefile for ARMPL + OpenMP
|   |   └── script_2.sh                # Script to execute the MPI version with varying numbers of simulations and threads
|   |
│   └── version_f_final_hybrid/        # Final hybrid version: MPI + OpenMP + ARMPL
│       ├── BSM_vf.cxx                 # Fully optimized source code
│       ├── Makefile                   # Makefile for MPI + OpenMP + ARMPL
|       └── script_3.sh                # Script to execute the MPI version with varying numbers of simulations and threads
|        
├── results/                           
│   ├── benchmarks/                    # Performance benchmarks
│   │   ├── benchmark_96_threads_script.py
│   │   ├── benchmark_comparison_96_threads_selected.csv
│   │   └── benchmark_final_results.csv
│   │   ├── ...                        # Results for other versions (more details in the report)
|   |   |
│   |   |
│   └── validation/                    # Validation results
│       ├── results_v6_nodes.csv       # Version 6 results across nodes
│       └── results_vf_nodes.csv       # Final version results across nodes
│       ├── ...                        # Results for other versions (more details in the report)
|       
└──
```

Each version directory contains:
- Source code (BSM_vX.cxx)
- Makefile for compilation
- Execution scripts
  
---

### **code_aster** 
- **`build/`**: Build and compilation configurations.

---

## Documentation

- Detailed implementation information can be found in each component's README
- Full analysis and results are available in the project report

---

## Team 10 Members

- @nadir-ogd - Nadir Ouagued
- @raniamerad - Rania Merad
- @zaksquirrel - Zakaria Anzid
- @Amine-Mouloud - Amine Mouloudj 

---

## Acknowledgments

- Viridien for the Black-Scholes challenge
- EDF for the Code_Aster challenge
- Teratec for organizing the hackathon
