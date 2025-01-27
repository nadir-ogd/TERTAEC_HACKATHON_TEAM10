# Compiler selection
CXX ?= $(DEFAULT_COMPILER)

# Paths for different libraries
LIBRARY_PATHS_compiler = /tools/acfl/24.10/arm-linux-compiler-24.10.1_AmazonLinux-2
LIBRARY_PATHS_armpl = /tools/acfl/24.10/armpl-24.10.1_AmazonLinux-2_arm-linux-compiler
LIBRARY_PATHS_gcc = /tools/acfl/24.10/armpl-24.10.1_AmazonLinux-2_gcc

# Include paths
INCLUDE_PATHS_compiler = -I$(LIBRARY_PATHS_compiler)/include
INCLUDE_PATHS_armpl = -I$(LIBRARY_PATHS_armpl)/include
INCLUDE_PATHS_gcc = -I$(LIBRARY_PATHS_gcc)/include

# Library linking paths
LINK_PATHS_compiler = -L$(LIBRARY_PATHS_compiler)/lib -liomp5 -lomp
LINK_PATHS_armpl = -L$(LIBRARY_PATHS_armpl)/lib -larmpl_lp64_mp -lamath -lastring
LINK_PATHS_gcc = -L$(LIBRARY_PATHS_gcc)/lib -larmpl -lm

# Combine include and link flags
INCLUDE_FLAGS = $(INCLUDE_PATHS_compiler) $(INCLUDE_PATHS_armpl) $(INCLUDE_PATHS_gcc)
LINK_FLAGS = $(LINK_PATHS_compiler) $(LINK_PATHS_armpl) $(LINK_PATHS_gcc)

# General compilation flags
CXXFLAGS += -O3 -g -fopenmp -mcpu=native \
            -ffast-math -march=armv8-a -mtune=native -funroll-loops \
            -finline-functions -fassociative-math \
            $(INCLUDE_FLAGS)

# Linking flags
LDFLAGS += $(LINK_FLAGS)

# Source and output files
SRC = BSM_v3.cxx
OUT = BSM

# Default target
all: echo_info module_setup set_threads $(OUT)

# Echo compiler and library information
echo_info:
        @echo "Compilation succeeded!"
        @echo "To execute the code, use the following command:"
        @echo "   make run ARGS=\"<num_simulations> <num_runs>\""
        @echo "To remove the executable, use the following command:"
        @echo "   make clean"

# Module setup (load environment dynamically)
module_setup:
        @module use /tools/acfl/24.10/modulefiles && module load acfl && export PATH=/tools/acfl/24.10/bin:$$PATH

# Set threads dynamically based on hostname
#set_threads:
# ifeq ($(shell hostname | grep -o "c8g"), c8g)
# 	export OMP_NUM_THREADS=96
# 	@echo "OMP_NUM_THREADS set to 96 (Node 1)"
# else ifeq ($(shell hostname | grep -o "c7g"), c7g)
# 	export OMP_NUM_THREADS=64
# 	@echo "OMP_NUM_THREADS set to 64 (Node 2)"
# else
# 	export OMP_NUM_THREADS=16
# 	@echo "OMP_NUM_THREADS set to 16 (Head-node)"
# endif

# Build target
$(OUT): $(SRC)
        @$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Run target
run: $(OUT)
        ./$(OUT) $(ARGS)

# Clean target
clean:
        rm -f $(OUT)

# Special targets
.PHONY: all clean run module_setup echo_info #set_threads