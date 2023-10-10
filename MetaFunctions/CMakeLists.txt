cmake_minimum_required(VERSION 3.21)
project(metaFunctions)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
  -O1 -g -flto #[[ -S ]] 
  #[[ -fsanitize=address ]] #[[ -fsanitize=memory ]]
  #[[ -fno-omit-frame-pointer ]]
)
add_link_options(
  -g -flto #[[ -S ]]
  #[[ -fsanitize=address ]]
)

include(../cmake/warning.cmake)
project_warnings()

# added to use precompiled headers
add_library(metafunctionsPCH INTERFACE)
target_precompile_headers(metafunctionsPCH INTERFACE [["metafunctionsPCH.hpp"]])

target_include_directories(
  metafunctionsPCH INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

add_library(
  metaFunLib
  src/MetaFuncUtilities/metafuncUtils.hpp
  src/MetaFuncUtilities/metafuncUtils.cpp
  src/MetaFuncUtilities/VoidtCornerCases.hpp
  src/MetaFuncUtilities/metaLinearSearch.hpp
  src/MetaFuncUtilities/metaInheritanceSearch.hpp
  src/MetaFuncUtilities/InheritanceSearchStruct.hpp
  src/MetaFuncUtilities/enumeratePack.hpp
  src/MetaFuncUtilities/apply_to_Index.hpp)

target_include_directories(metaFunLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(metaFunLib PRIVATE metafunctionsPCH)

add_executable(MetaFun src/metafunctions_Test.cpp)
# if Ranges is used in another project as a library then make it INTERFACE or
# PUBLIC if only Ranges needs the specified list then use PRIVATE
target_link_libraries(MetaFun PRIVATE project_options metaFunLib asio fmt
                                      range-v3)
