#------------------------------------------------------------------------------
# Usage: find_package(SDL2 [REQUIRED] [COMPONENTS main])
#
# Sets variables:
#     SDL2_image_INCLUDE_DIRS
#     SDL2_image_LIBS
#     SDL2_image_DLLS
#------------------------------------------------------------------------------

include(FindPackageHandleStandardArgs)

# Check if "main" was specified as a component
set(_SDL2_image_use_main FALSE)
foreach(_SDL2_image_component ${SDL2_image_FIND_COMPONENTS})
    if(_SDL2_image_component STREQUAL "main")
        set(_SDL2_image_use_main TRUE)
    else()
        message(WARNING "Unrecognized component \"${_SDL2_image_component}\"")
    endif()
endforeach()

if(WIN32)
    # Search for SDL2 Debug CMake build in extern/SDL2-2.0.5-dev/build
    if(NOT SDL2_image_FOUND)
        # Search for SDL2 in extern/SDL2-2.0.5
        find_path(SDL2_image_ROOT "include/SDL_image.h" PATHS "${CMAKE_CURRENT_LIST_DIR}/../extern/SDL2_image-2.0.5" NO_DEFAULT_PATH)
        if(SDL2_image_ROOT)
            set(SDL2_image_INCLUDE_DIRS "${SDL2_image_ROOT}/include")
            set(SDL2_image_LIBS "${SDL2_image_ROOT}/lib/x64/SDL2_image.lib")
            set(SDL2_image_DLLS "${SDL2_image_ROOT}/lib/x64/SDL2_image.dll")
            if(_SDL2_image_use_main)
                list(APPEND SDL2_image_LIBS "${SDL2_image_ROOT}/lib/x64/SDL2main.lib")
            endif()
        endif()
    endif()

    mark_as_advanced(SDL2_image_ROOT)
    find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_image_INCLUDE_DIRS SDL2_image_LIBS SDL2_image_DLLS)
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

    FIND_PATH(SDL2_image_INCLUDE_DIRS SDL_image.h
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES include/SDL2 include
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )

    FIND_LIBRARY(SDL2_image_LIBS
        NAMES SDL2_image
        HINTS
        $ENV{SDL2TTFDIR}
        PATH_SUFFIXES lib64 lib
        PATHS ${SDL2TTF_SEARCH_PATHS}
    )
endif()
