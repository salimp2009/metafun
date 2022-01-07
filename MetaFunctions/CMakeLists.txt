cmake_minimum_required(VERSION 3.21)
project(metaFunctions)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(IS_GNU On)
    add_definitions(-DIS_GCC=true)
else()
    set(IS_GNU Off)
    add_definitions(-DIS_GCC=false)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(IS_CLANG On)
    add_definitions(-DIS_CLANG=true)
else()
    set(IS_CLANG Off)
    add_definitions(-DIS_CLANG=false)
endif()

if(MSVC)
    add_definitions(-DIS_MSVC=true)
    #add_definitions(/WX)
    add_definitions(/W3)
    add_definitions(/wd4189)
    add_definitions(/wd4100)
    add_definitions(/wd4996) # 'fopen': This function or variable may be unsafe. Consider using fopen_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
    add_definitions(/wd4267)
    add_definitions(/wd4505)
    #add_definitions(/await) # enable coroutine support

    # Use sane and nice C++ for MSVC.
    # This makes alternative tokens (not, and, ...) as actual keywords and
    # enables more conformant C++ in general
    add_definitions(/permissive-)
    #add_definitions(/std:c++latest)

else()
    add_definitions(-DIS_MSVC=false)
    #add_definitions(-Werror)
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wold-style-cast)
    add_definitions(-Wno-unused-variable)
    add_definitions(-Wno-unused-parameter)
    add_definitions(-Wno-unused-value)
    add_definitions(-Wno-cpp)

    if(IS_CLANG)
        add_definitions(-Wno-unused-private-field)
        add_definitions(-Wno-unneeded-internal-declaration)

    else()
        add_definitions(-fcoroutines) # required for GCC-10
        #add_definitions(-fpermissive) # to relax typename requirement

    endif()
endif()

#added to use precompiled headers
add_library(metafunctionsPCH INTERFACE)
target_precompile_headers(metafunctionsPCH INTERFACE
        [["metafunctionsPCH.hpp"]]
        )

target_include_directories(metafunctionsPCH  INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        )


add_library(metaFunLib
        src/MetaFuncUtilities/metafuncUtils.hpp
        src/MetaFuncUtilities/metafuncUtils.cpp src/MetaFuncUtilities/VoidtCornerCases.hpp)

target_include_directories(metaFunLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(metaFunLib PRIVATE metafunctionsPCH)

add_executable (MetaFun src/metafunctions_Test.cpp)
# if Ranges is used in another project as a library then make it INTERFACE or PUBLIC
# if only Ranges needs the specified list then use PRIVATE
target_link_libraries(MetaFun PRIVATE project_options metaFunLib)

