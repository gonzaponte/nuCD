# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(nuCD)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
find_package(ROOT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../EI/include)
include_directories(${ROOT_INCLUDE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../EI/lib)

add_library(nuei STATIC IMPORTED)
set_property(TARGET nuei PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../EI/lib/libnuei.dylib)
#add_dependencies(nuei

message(STATUS "G4   " ${Geant4_USE_FILE})
message(STATUS "ROOT " ${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs

message(STATUS "Project source directory: " ${PROJECT_SOURCE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/*/*.cc ${PROJECT_SOURCE_DIR}/*/*/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*/*.hh ${PROJECT_SOURCE_DIR}/*/*/*.hh)

#message(STATUS "sources " ${sources})
#message(STATUS "headers " ${headers})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
set(nucdexe ${PROJECT_SOURCE_DIR}/../nucd)
add_executable(nucdexe ${PROJECT_SOURCE_DIR}/nuCD.cc ${sources} ${headers})
target_link_libraries(nucdexe nuei ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
#set(EXAMPLEB1_SCRIPTS
#  exampleB1.in
#  exampleB1.out
#  init_vis.mac
#  run1.mac
#  run2.mac
#  vis.mac
#  )
#
#foreach(_script ${EXAMPLEB1_SCRIPTS})
#  configure_file(
#    ${PROJECT_SOURCE_DIR}/${_script}
#    ${PROJECT_BINARY_DIR}/${_script}
#    COPYONLY
#    )
#endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(nuCD DEPENDS nucdexe)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS nucdexe DESTINATION bin)
