# Compiler selection
CXX ?= mpicc

# Paths for different libraries
LIBRARY_PATHS_compiler = /tools/acfl/24.10/arm-linux-compiler-24.10.1_AmazonLinux-2
LIBRARY_PATHS_armpl = /tools/acfl/24.10/armpl-24.10.1_AmazonLinux-2_arm-linux-compiler
LIBRARY_PATHS_gcc = /tools/acfl/24.10/armpl-24.10.1_AmazonLinux-2_gcc
LIBRARY_PATHS_mpi = /tools/openmpi/5.0.6/acfl/24.10

# Include paths
INCLUDE_PATHS_compiler = -I$(LIBRARY_PATHS_compiler)/include
INCLUDE_PATHS_armpl = -I$(LIBRARY_PATHS_armpl)/include
INCLUDE_PATHS_gcc = -I$(LIBRARY_PATHS_gcc)/include
INCLUDE_PATHS_mpi = -I$(LIBRARY_PATHS_mpi)/include

# Library linking paths
LINK_PATHS_compiler = -L$(LIBRARY_PATHS_compiler)/lib -liomp5 -lomp
LINK_PATHS_armpl = -L$(LIBRARY_PATHS_armpl)/lib -larmpl_lp64_mp -lamath -lastring
LINK_PATHS_gcc = -L$(LIBRARY_PATHS_gcc)/lib -larmpl -lm -lstdc++
LINK_PATHS_mpi = -L$(LIBRARY_PATHS_mpi)/lib -lmpi

# Combine include and link flags
INCLUDE_FLAGS = $(INCLUDE_PATHS_compiler) $(INCLUDE_PATHS_armpl) $(INCLUDE_PATHS_gcc) $(INCLUDE_PATHS_mpi)
LINK_FLAGS = $(LINK_PATHS_compiler) $(LINK_PATHS_armpl) $(LINK_PATHS_gcc) $(LINK_PATHS_mpi)

# General compilation flags
CXXFLAGS += -O3 -g -fopenmp -mcpu=native \
            -ffast-math -march=armv8-a+sve -mtune=neoverse-n1 -funroll-loops \
            -finline-functions -fassociative-math -std=c++17 \
            $(INCLUDE_FLAGS)

# Linking flags
LDFLAGS += $(LINK_FLAGS)

# Source and output files
SRC = BSM2.cxx
OUT = BSM2

# Default target
all: echo_info module_setup $(OUT)

# Echo compiler and library information
echo_info:
        @echo "Compiler used = $(CXX)"
        @echo "Libraries linked = $(LINK_FLAGS)"

# Module setup (load environment dynamically)
module_setup:
        module use /tools/acfl/24.10/modulefiles && module load acfl && export PATH=/tools/acfl/24.10/bin:$$PATH

# Build target
$(OUT): $(SRC)
        $(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Run target with configurable number of processes
run: $(OUT)
        mpirun --oversubscribe -np $(N) ./$(OUT) $(ARGS)

# Clean target
clean:
        rm -f $(OUT)

# Special targets
.PHONY: all clean run module_setup echo_info