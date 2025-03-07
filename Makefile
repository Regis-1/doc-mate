ROOT_DIR = $(shell pwd)

CXX = g++
CXXFLAGS = -Wall -I$(ROOT_DIR)/include \
	-I$(ROOT_DIR)/extlibs/googletest/include

export ROOT_DIR

export CXX
export CXXFLAGS

all: doc_mate
build: doc_mate

.PHONY: doc-mate
doc_mate:
	@$(MAKE) -C src;
	@echo "Building finished.";

.PHONY: tests
tests:
	@$(MAKE) -C tests;
	@echo "Building tests finished.";

.PHONY: clean
clean:
	@$(MAKE) -C src clean;
	@$(MAKE) -C tests clean;
	@echo "Cleaning finished.";
