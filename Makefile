all:
	mkdir build
	cd build && cmake .. && make
	./build/CMakeProject1/CMakeDemo
	rm -rf build
