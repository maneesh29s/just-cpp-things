CXXFLAGS=-std=c++17 -O3 -Wall -Wextra -I include

CXXFLAGS+=#pkg-config falgs

# DEBUGOPTIONS=-fsanitize=address -g -fno-omit-frame-pointer

LDFLAGS=#linker library flags then pkg-config

CXX=g++

MPICXX=mpicxx

# src
src/%: src/%.cc dir
	$(CXX) -o build/$@ $<  $(CXXFLAGS) $(DEBUGOPTIONS) $(LDFLAGS) $(EXTRA)

.PHONY: clean dir

dir:
	mkdir -p build/src

clean:
	rm -rf build/*