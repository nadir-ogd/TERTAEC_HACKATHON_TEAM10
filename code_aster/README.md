# Code_Aster Implementation

This repository provides scripts and configuration files to automate the installation and exportation of prerequisites for *Code_Aster*. It is designed to work seamlessly on your cluster environment with dynamic module loading and dependency handling.

---

## Prerequisites

### System Requirements
- **Compilers**:
  - GCC 14.2.0
  - GFortran 14.2.0
- **MPI**: OpenMPI 5.0.6
- **Modules**: /tools/acfl/24.10
- **Python Version**: Python 3.7.18

### Cluster-Specific Setup
- **Environment Variables**:
  - `ROOT`: Root directory for installation.
  - `ARCH`: Architecture identifier (e.g., gcc8-openblas-seq).

---

## Installation Steps

### 1. Clone the Repository
Clone the repository containing all scripts and configurations:

```bash
git clone <repository_url>
cd <repository_directory>
```

### 2. Load Environment Variables

Before starting the installation, load the required environment variables:

```bash
source global_variables.sh
source build_env.sh
```

- `global_variables.sh`: Defines global paths and directories.
- `build_env.sh`: Exports environment variables for compilers, MPI, and library paths.

### 3. Install Prerequisites

#### Install All Products
To install all the products listed in the Makefile:

```bash
make ROOT=${ROOT} ARCH=${ARCH} products
```

#### Install Specific Products
To install a specific prerequisite (e.g., hdf5, petsc):

```bash
./install_prerequisite.sh hdf5
./install_prerequisite.sh petsc
```

### 4. Check the Environment

Verify the environment setup and validate installed products:

```bash
make check
```

### 5. Clean Up

Remove build artifacts, logs, and temporary files:

```bash
make distclean
```

---

## Files Overview

### Scripts
- `install_prerequisite.sh`: Automates the installation of individual prerequisites by calling their respective scripts and managing logs.
- `build_env.sh`: Exports compilers, MPI, and library paths to the environment.
- `global_variables.sh`: Defines global paths and ensures necessary directories exist.
- `reqs_pyenv.txt`: Defines the necessary requirements to install the pyenv *Python env*

### Makefile
The Makefile provides targets for managing the build process:

#### Default Target:

```bash
make
```
Installs all prerequisites and sets up the environment.

#### Install Specific Products:

```bash
make <product_name>
```

#### Environment Check:

```bash
make check
```

#### Clean Up:

```bash
make distclean
```

---

## Execution Commands

### Complete Workflow

```bash
# Load the environment
source global_variables.sh
source build_env.sh

# Build prerequisites
make ROOT=$(pwd) ARCH=gcc8-openblas-seq products

# Verify the environment
make check

# Clean up build files
make distclean
```

### Individual Product Installation

```bash
# Install specific products
./install_prerequisite.sh hdf5
./install_prerequisite.sh petsc
```

Note : More details about errors will be shown in the report.