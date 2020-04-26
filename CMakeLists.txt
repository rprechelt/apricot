# this minimum version hasn't been tested extensively
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# setup our project
project(Apricot
  VERSION 0.1
  LANGUAGES CXX)

# make sure we can install libraries into correct
# locations on a variety of platforms
include(GNUInstallDirs)

# get the latest abberivate commit hash that we can store
# in the output files to provide some reproducibility
execute_process(COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# enable ccache support if it is available
find_program(CCACHE_FOUND "ccache")
set(CCACHE_SUPPORT ON CACHE BOOL "Enable ccache support")
if (CCACHE_FOUND AND CCACHE_SUPPORT)
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" # GNU is GNU GCC
      OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # without this compiler messages in `make` backend would be uncolored
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
  endif()
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "ccache")
endif()

# build the src/ directory into a shared library
add_subdirectory(src)

# and build our Python wrapper
add_subdirectory(python)

# make sure all our apricot data files are installed
# file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
