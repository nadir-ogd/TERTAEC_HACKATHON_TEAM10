# Black-Scholes Monte Carlo Implementation

This directory contains our implementation and optimization of the Black-Scholes Monte Carlo model for Arm-based architectures, developed during the Teratec Hackathon 2025.

## Implementation Versions

### 1. Basic Implementation (version_1_basic)
- Single-threaded baseline implementation
- Basic Black-Scholes Monte Carlo algorithm
- Components:
  - BSM_v1.cxx: Core implementation
  - Makefile: Basic compilation setup
  - script_1.sh: Execution script for various simulation configurations

### 2. Mathematical Optimizations (version_2_math_opt)
- Optimized mathematical functions
- Improved random number generation
- Components:
  - BSM_v2.cxx: Mathematically optimized implementation
  - Makefile: Compilation with math optimization flags
  - script_1.sh: Testing script

### 3. OpenMP Implementation (version_3_openmp)
- Thread-level parallelization
- Optimized for shared memory systems
- Components:
  - BSM_v3.cxx: OpenMP-enabled source code
  - Makefile: OpenMP compilation settings
  - script_2.sh: Multi-threaded execution script

### 4. MPI Implementation (version_4_mpi)
- Distributed computing support
- Scalable across multiple nodes
- Components:
  - BSM_v4.cxx: MPI-based implementation
  - Makefile: MPI compilation configuration
  - script_3.sh: Distributed execution script

### 5. ARMPL Optimization (version_5_armpl)
- Integration with Arm Performance Libraries
- Optimized numerical routines
- Components:
  - BSM_v5.cxx: ARMPL-optimized implementation
  - Makefile: ARMPL linking configuration
  - script_2.sh: Performance testing script

### 6. ARMPL + OpenMP Hybrid (version_6_armpl_openmp)
- Combined ARMPL and OpenMP optimizations
- Enhanced thread-level performance
- Components:
  - BSM_v6.cxx: Hybrid implementation
  - Makefile: ARMPL and OpenMP configuration
  - script_2.sh: Hybrid execution script

### 7. Final Hybrid Version (version_final_hybrid)
- Full optimization: MPI + OpenMP + ARMPL
- Maximum performance configuration
- Components:
  - BSM_vf.cxx: Final optimized implementation
  - Makefile: Complete hybrid configuration
  - script_3.sh: Comprehensive testing script

## Results

### Benchmarks
Due to time constraints, we focused on benchmarking the two most optimized versions (which contain all optimizations from previous versions):
- version_6_armpl_openmp
- version_f_final_hybrid

Two benchmark studies were performed:

1. Fixed Thread Comparison:
   - benchmark_96_threads_script.py: Script for running tests
   - benchmark_comparison_96_threads_selected.csv: Results comparing v6 and vf at 96 threads

2. Comprehensive Performance Analysis:
   - benchmark_final_results.csv: Extended comparison varying threads (16-512) and simulation sizes (100-200M iterations)
   - v6 tested up to 100K iterations/96 threads
   - vf scaled to 200M iterations/512 threads

Note: For larger simulations (e.g., +10M iterations), **The generation times were identified and optimized in version VF**, 
whereas in version V7, they were significantly higher and not addressed. and some results are pending completion. 
**Full details will be available in the project report.**

### Validation
Results validation across different cluster nodes:
- results_v6_nodes.csv: Version 6 validation across nodes
- results_vf_nodes.csv: Final version validation across nodes

Example of validation data format:
```plaintext
Node,Value (100s),Threads,Time (seconds)
C8G,100,96,1.311187
...
C7G,100000,96,379.086692
```

## Compilation and Execution

Each version includes its own Makefile and execution scripts. Detailed instructions for building and running each version are provided in the project report.

## Performance Analysis

Complete performance analysis, including:
- Scaling across different thread counts
- Node-specific performance characteristics
- Comparison between different optimization strategies
- Memory usage and efficiency metrics

Full details are available in the project report.
