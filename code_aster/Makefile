BASE := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

ROOT := $(shell pwd)
export ROOT

ARCH ?= gcc8-openblas-seq
export ARCH

# Module setup
module_setup:
	module use /tools/acfl/24.10/modulefiles
	module load acfl

include $(BASE)/VERSION

PRODUCTS ?= hdf5 med petsc parmetis mpi4py ...

.NOTPARALLEL:

default: module_setup products env_file

products: module_setup _check $(PRODUCTS) version_file

NUMVERS = $(shell echo ${VERSION})

export DEST ?= $(ROOT)/$(NUMVERS)/$(ARCH)
export BUILD ?= $(BASE)/.build-$(ARCH)
export CACHE ?= /tmp/.cache_$(shell whoami)
export ARCHIVESDIR = $(BASE)/archives

# Call install_prerequisite.sh for each product
$(PRODUCTS): % : _check $(DEST)/.installed/%

$(DEST)/.installed/%:
	./install_prerequisite.sh $* && \
	echo "Installation of $* successful" > $(DEST)/.installed/$* || \
	(echo "Installation of $* failed"; exit 1)

version_file: module_setup _check $(DEST)/VERSION

check: module_setup _check $(DEST)/.installed/env_check

env: module_setup _check $(DEST)/.installed/env_file

setup_venv: module_setup _check $(DEST)/.installed/setup_venv

env_file: module_setup products env

.PHONY: module_setup archive distclean dist download _check clean $(PRODUCTS)