UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OMPFLAGS += -fopenmp
else ifeq ($(UNAME_S),Darwin)
	OMPFLAGS += -Xpreprocessor -fopenmp -lomp
endif

processor := $(shell uname -m)
ifeq ($(processor),$(filter $(processor),aarch64 arm64))
    ARCH_C_FLAGS += -march=armv8-a+fp+simd+crc 
	CUSTOM_CODE_FLAGS += -Darm64 -DGOLDEN -DSSE -DNEON -DASSERT 
else ifeq ($(processor),$(filter $(processor),i386 x86_64))
    ARCH_C_FLAGS += -march=native 
	CUSTOM_CODE_FLAGS += -Damd64 -DGOLDEN -DSSE -DAVX -DASSERT 
endif

CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic -I include/

CFLAGS=-std=c99 -Wall -Wextra -pedantic 

# example of pkg-config
CFITSIO=`pkg-config --libs --cflags cfitsio`

ADIOS=`adios2-config --cxx-flags --cxx-libs`

# OPTIMISATION=-fsanitize=address -g
OPTIMISATION=-O3

CXX=mpicxx

CC=gcc

SRC = imstat.out \
      imstat_mpi.out \

all: dir $(SRC)

%.out: src/%.c dir
	$(CC) -o build/$@ $< $(CFLAGS) $(OPTIMISATION) $(OPT) $(CFITSIO)

%.out: src/%.cpp dir
	$(CXX) -o build/$@ $< $(CXXFLAGS) $(OPTIMISATION) $(OPT) $(ADIOS) $(CFITSIO)

clean:
	rm -rf build/*

dir:
	mkdir -p build

.PHONY: all clean dir

