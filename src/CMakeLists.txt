###################### FIND SOURCES ######################
# the full list of sources
list(APPEND LIB_SOURCES
  "PREM.cpp"
  "Earth.cpp"
  "SphericalEarth.cpp"
  "ExponentialAtmosphere.cpp"
  )

###################### CREATE LIBRARY ######################
add_library(libApricot SHARED ${LIB_SOURCES})
set_target_properties(libApricot PROPERTIES VERSION ${PROJECT_VERSION})

# define the headers for this library
target_include_directories(libApricot
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

# PyBind11 is very restrictive with how it names the Python library
# so we have to trick the C++ backend into changing the library
# name to something sensible (not liblibApricot)
set_target_properties(libApricot PROPERTIES OUTPUT_NAME "apricot")

# and make sure we use C++-17
target_compile_features(libApricot PUBLIC cxx_std_17)

#################### START FIND PACKAGES ####################
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#################### START INCLUDES ####################
target_include_directories(libApricot PRIVATE "${CMAKE_HOME_DIRECTORY}/include")
#target_include_directories(libApricot SYSTEM PUBLIC "${CMAKE_HOME_DIRECTORY}/extern/units/include")
#target_include_directories(libApricot SYSTEM PRIVATE "${CMAKE_HOME_DIRECTORY}/extern/magic_enum/include")

#################### START LINKING ####################
target_link_libraries(libApricot PUBLIC Eigen3::Eigen)

#################### START COMPILE FLAGS ####################
set(COMPILE_OPTIONS -Wall -Wextra -Wdisabled-optimization -fconcepts
  -pedantic -Wshadow -Wno-sign-conversion -Wno-sign-compare -Wold-style-cast
  -Wno-strict-overflow -Wundef -Wno-unused -Wstack-protector -Wcast-align
  -Wpacked -Wformat-y2k -Warray-bounds -Wreorder -Wmissing-braces
  -Wstrict-overflow=4 -Wwrite-strings -Wpointer-arith
  -Wcast-qual -Wswitch-enum -Wswitch-default -Wunreachable-code
  -Wmaybe-uninitialized -march=native -fmax-errors=5 -O3 -flto -Wfloat-equal)

# add the compile options to the library
target_compile_options(libApricot PRIVATE ${COMPILE_OPTIONS})

# allow us to import the project after install
install(EXPORT libApricotConfig DESTINATION share/libApricot/cmake)

# install to the correct locations (see GNUInstallDirs).
install(TARGETS libApricot EXPORT libApricotConfig
  CONFIGURATIONS Release
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
