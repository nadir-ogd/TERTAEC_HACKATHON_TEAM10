# Teratec Hackathon 2025 - Team 10

This repository contains the work done for the Teratec Hackathon 2025, centered around two challenges:
- **Optimization and parallelization of Black-Scholes Monte Carlo** for Arm-based architectures (provided by Viridien).
- **Porting and optimization of Code_Aster**, an industrial HPC application (provided by EDF).

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
├── results/                           # Results folder
│   ├── benchmarks/                    # Benchmarking results
│   │   ├── version_1.csv              # Results for version 1
│   │   ├── version_2.csv              # Results for version 2
│   │   ├── ...                        # Results for other versions
|   |   |
│   ├── profiling/                     # Profiling reports
│   │   ├── version_1_report.txt       # Profiling report for version 1
│   │   ├── version_2_report.txt       # Profiling report for version 2
│   │   ├── ...                        # Reports for other versions
|   |   |
│   └── validation/                    # Validation outputs
│       ├── test_1_output.txt          # Test output for case 1
│       ├── test_2_output.txt          # Test output for case 2
│       ├── ...                        # Outputs for other tests
```

---

### **code_aster** 
- **`build/`**: Build and compilation configurations.
