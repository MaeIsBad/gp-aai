cmake_minimum_required(VERSION 3.1)
project(gp-aai)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)

# Threading support
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Write demo-config.h
message("Generating header file: ${CMAKE_BINARY_DIR}/demo-config.h")
set(DEMO_ENABLE_MULTISAMPLE 0 CACHE BOOL "Enable multisample anti-aliasing")
configure_file(demo-config.h.in "${CMAKE_BINARY_DIR}/demo-config.h")

# Find SDL2 and OpenGL
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")
#     SDL2_INCLUDE_DIRS
#     SDL2_LIBS
#     SDL2_DLLS
message("SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message("SDL2_LIBS: ${SDL2_LIBS}")
message("SDL2_DLLS: ${SDL2_DLLS}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
find_package(SDL2 REQUIRED COMPONENTS main)
if(NOT WIN32)
    find_package(OpenGL REQUIRED)
endif()

# Define executable target
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
message("SOURCES: ${SOURCES}")
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${CMAKE_BINARY_DIR})
add_executable(gp-aai ${SOURCES} gl2/Context.cpp)
target_link_libraries(gp-aai ${SDL2_LIBS} ${OPENGL_LIBRARIES})

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET gp-aai POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:gp-aai>)
    endforeach()
endif()
