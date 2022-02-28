all:
	rm -rf build
	mkdir build
	cd build && cmake .. && make
	./build/CMakeProject1/CMakeDemo
	rm -rf build
