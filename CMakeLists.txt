cmake_minimum_required(VERSION 3.21)
project(metaFun)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)
# add dependencies
include(cmake/CPM.cmake)

cpmaddpackage("gh:fmtlib/fmt#7.1.3")
cpmaddpackage("gh:chriskohlhoff/asio#asio-1-28-1@1.28.1")
# find_package(asip REQUIRED)

find_package(Threads REQUIRED)
if(asio_ADDED)
  add_library(asio INTERFACE)

  target_include_directories(asio SYSTEM
                             INTERFACE ${asio_SOURCE_DIR}/asio/include)
  message("asio is installed at : ${asio_SOURCE_DIR}/n")
  target_compile_definitions(asio INTERFACE ASIO_STANDALONE ASIO_NO_DEPRECATED)

  target_link_libraries(asio INTERFACE Threads::Threads)

  if(WIN32)
    # macro see @ https://stackoverflow.com/a/40217291/1746503
    macro(get_win32_winnt version)
      if(CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
        string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
        # Check for Windows 10, b/c we'll need to convert to hex 'A'.
        if("${verMajor}" MATCHES "10")
          set(verMajor "A")
          string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
        endif("${verMajor}" MATCHES "10")
        # Remove all remaining '.' characters.
        string(REPLACE "." "" ver ${ver})
        # Prepend each digit with a zero.
        string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
        set(${version} "0x${ver}")
      endif()
    endmacro()

    if(NOT DEFINED _WIN32_WINNT)
      get_win32_winnt(ver)
      set(_WIN32_WINNT ${ver})
    endif()

    message(STATUS "Set _WIN32_WINNET=${_WIN32_WINNT}")

    target_compile_definitions(asio INTERFACE _WIN32_WINNT=${_WIN32_WINNT}
                                              WIN32_LEAN_AND_MEAN)
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang" ON)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

cpmaddpackage(
  NAME
  range-v3
  URL
  https://github.com/ericniebler/range-v3/archive/0.12.0.zip
  VERSION
  0.12.0
  # the range-v3 CMakeLists screws with configuration options
  DOWNLOAD_ONLY
  True)

if(range-v3_ADDED)
  add_library(range-v3 INTERFACE IMPORTED)
  target_include_directories(range-v3
                             INTERFACE "${range-v3_SOURCE_DIR}/include")
endif()

add_subdirectory("MetaFunctions")
