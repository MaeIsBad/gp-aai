.PHONY := all debug build run gdb

all: clean build run clean
debug: clean build gdb clean

build:
	mkdir build || true
	cd build && cmake .. && make
	
run:
	./build/gp-aai/gp-aai
	
gdb:
	gdb ./build/gp-aai/gp-aai

clean:
	rm -rf build
