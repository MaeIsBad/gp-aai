cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (gp-aai "main.cpp" "main.h")

# Enable C++ v17 features
if(MSVC) # If we're using the microsoft compiler
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else() # Everything else will probably be linux
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)