.PHONY := all debug build run gdb

all: clean build run clean
debug: clean build gdb clean
mem: clean build valgrind clean

build:
	mkdir build || true
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && time make
	
run:
	./build/gp-aai/gp-aai
	
gdb:
	gdb ./build/gp-aai/gp-aai

valgrind:
	valgrind ./build/gp-aai/gp-aai

clean:
	rm -rf build
