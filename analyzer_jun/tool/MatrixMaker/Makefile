#!/usr/bin/make

bin_dir		= bin
src_dir		= src
build_dir	= $(src_dir)/build

FC	= gfortran
CXX	= g++ -O3 -Wall

target	= $(bin_dir)/MatrixMaker $(bin_dir)/orbit

all: $(target)

$(bin_dir)/MatrixMaker: $(build_dir)/MatrixMaker.o
	@ echo "=== Linking $@"
	@ mkdir -p $(bin_dir)
	$(CXX) -o $@ $^

$(bin_dir)/orbit: orbit/orbit.f
	@ echo "=== Linking $@"
	@ mkdir -p $(bin_dir)
	$(FC) orbit/orbit.f -o $@

$(build_dir)/%.o: $(src_dir)/%.cc
	@ echo "=== Compiling $@"
	@ mkdir -p $(build_dir)
	$(CXX) -o $@ -c $<

clean:
	@echo "=== Cleaning"
	@rm -rfv $(build_dir)
	@find . \( -name "*~" -o -name "\#*\#" \) -exec rm -fv \{\} \;

