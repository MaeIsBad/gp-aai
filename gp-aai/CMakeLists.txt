cmake_minimum_required(VERSION 3.1)
project(gp-aai)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif(MSVC)

# SDL2 stuff
if(MSVC) 
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL2-2.0.5/include")
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL2-2.0.5/lib/x64/SDL2.lib;${CMAKE_CURRENT_SOURCE_DIR}/extern/SDL2-2.0.5/lib/x64/SDL2main.lib")
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
else()
    find_package(SDL2 REQUIRED)
    SET(SDL2TTF_SEARCH_PATHS
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /opt
    )

    FIND_PATH(SDL2TTF_INCLUDE_DIR SDL_ttf.h
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES include/SDL2 include
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )

    FIND_LIBRARY(SDL2TTF_LIBRARY_TEMP
        NAMES SDL2_ttf
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )

    message("SDL2TTF_INCLUDE_DIR: ${SDL2TTF_INCLUDE_DIR}")
    message("SDL2TTF_LIBRARY_TEMP: ${SDL2TTF_LIBRARY_TEMP}")
endif()

# Define executable target
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${CMAKE_BINARY_DIR})
add_executable(gp-aai ${SOURCES} gl2/Context.cpp)
target_link_libraries(gp-aai ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY_TEMP} ${OPENGL_LIBRARIES})

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET gp-aai POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:gp-aai>)
    endforeach()
endif()
