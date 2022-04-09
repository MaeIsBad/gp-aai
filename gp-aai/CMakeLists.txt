cmake_minimum_required(VERSION 3.1)
project(gp-aai)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

    # baaaaa
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-unused-result")
endif(MSVC)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")
find_package(SDL2 REQUIRED COMPONENTS main)
find_package(SDL_ttf REQUIRED COMPONENTS)

message("SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message("SDL2_LIBS: ${SDL2_LIBS}")
message("SDL2_DLLS: ${SDL2_DLLS}")

message("SDL2_ttf_INCLUDE_DIRS: ${SDL2_ttf_INCLUDE_DIRS}")
message("SDL2_ttf_LIBS: ${SDL2_ttf_LIBS}")
message("SDL2_ttf_DLLS: ${SDL2_ttf_DLLS}")

# Define executable target
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${CMAKE_BINARY_DIR})
add_executable(gp-aai ${SOURCES} gl2/Context.cpp)
target_link_libraries(gp-aai ${SDL2_LIBS} ${SDL2_ttf_LIBS} ${OPENGL_LIBRARIES})


# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET gp-aai POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:gp-aai>)
    endforeach()
    foreach(DLL ${SDL2_ttf_DLLS})
        add_custom_command(TARGET gp-aai POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:gp-aai>)
    endforeach()
endif()
