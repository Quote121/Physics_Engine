cmake_minimum_required(VERSION 3.0.0)

project(physics-engine VERSION 0.1 DESCRIPTION "Physics based renderer in OpenGL")

message(STATUS "Including directories.")
include_directories((${CMAKE_SOURCE_DIR}/include))

IF (WIN32)
    ## MinGW default install location
    set (CMAKE_PREFIX_PATH, "C:\\msys64\\mingw64")
ENDIF()

## Debug flag
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS "-Wall")

# CFLAGS="-fno-stack-protector" CXXFLAGS="-fno-stack-protector"
## C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## To generate the compile_commands.json file for LSP clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Add subdirectory for other cmake scripts
add_subdirectory(src)

##
## Enable pragma #define sections of code
## e.g.
## #ifdef FEATURE_01
## We can enable with the compile definition
## add_compile_definitions(FEATURE_01)
##