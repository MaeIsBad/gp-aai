all: clean build run clean
debug: clean build gdb clean

build:
	mkdir build || true
	cd build && cmake .. && make
	
run:
	./build/CMakeProject1/CMakeDemo
	
clean:
	rm -rf build
	
gdb:
	gdb ./build/CMakeProject1/CMakeDemo
