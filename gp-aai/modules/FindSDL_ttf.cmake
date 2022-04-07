#------------------------------------------------------------------------------
# Usage: find_package(SDL2 [REQUIRED] [COMPONENTS main])
#
# Sets variables:
#     SDL2_ttf_INCLUDE_DIRS
#     SDL2_ttf_LIBS
#     SDL2_ttf_DLLS
#------------------------------------------------------------------------------

include(FindPackageHandleStandardArgs)

# Check if "main" was specified as a component
set(_SDL2_ttf_use_main FALSE)
foreach(_SDL2_ttf_component ${SDL2_ttf_FIND_COMPONENTS})
    if(_SDL2_ttf_component STREQUAL "main")
        set(_SDL2_ttf_use_main TRUE)
    else()
        message(WARNING "Unrecognized component \"${_SDL2_ttf_component}\"")
    endif()
endforeach()

if(WIN32)
    # Search for SDL2 Debug CMake build in extern/SDL2-2.0.5-dev/build
    if(NOT SDL2_ttf_FOUND)
        # Search for SDL2 in extern/SDL2-2.0.5
        find_path(SDL2_ttf_ROOT "include/SDL_ttf.h" PATHS "${CMAKE_CURRENT_LIST_DIR}/../extern/SDL2_ttf-2.0.18" NO_DEFAULT_PATH)
        if(SDL2_ttf_ROOT)
            set(SDL2_ttf_INCLUDE_DIRS "${SDL2_ttf_ROOT}/include")
            set(SDL2_ttf_LIBS "${SDL2_ttf_ROOT}/lib/x64/SDL2_ttf.lib")
            set(SDL2_ttf_DLLS "${SDL2_ttf_ROOT}/lib/x64/SDL2_ttf.dll")
            if(_SDL2_ttf_use_main)
                list(APPEND SDL2_ttf_LIBS "${SDL2_ttf_ROOT}/lib/x64/SDL2main.lib")
            endif()
        endif()
    endif()

    mark_as_advanced(SDL2_ttf_ROOT)
    find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_ttf_INCLUDE_DIRS SDL2_ttf_LIBS SDL2_ttf_DLLS)
else()
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

    FIND_PATH(SDL2_ttf_INCLUDE_DIRS SDL_ttf.h
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES include/SDL2 include
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )

    FIND_LIBRARY(SDL2_ttf_LIBS
        NAMES SDL2_ttf
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )
endif()
