CXXFLAGS=-std=c++17 -O3 -Wall -Wextra

CXXFLAGS+=`pkg-config --cflags --libs ompi` `adios2-config --cxx-flags --cxx-libs` 

# DEBUGOPTIONS=-fsanitize=address -g -fno-omit-frame-pointer

LDFLAGS=

CXX=g++

MPICXX=mpicxx

# src
src/%: src/%.cc dir
	$(MPICXX) -o build/$@ $<  $(CXXFLAGS) $(DEBUGOPTIONS) $(LDFLAGS) $(EXTRA)

dir:
	mkdir -p build/c++

.PHONY: dir

clean:
	rm -rf build/*