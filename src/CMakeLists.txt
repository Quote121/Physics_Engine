message(STATUS "Running src/ cmake")

## Set executable name and path
set(EXECUTABLE_NAME "physicsMain")
message(STATUS "Name set as ${EXECUTABLE_NAME}")

set(EXECUTABLE_DIR "${CMAKE_SOURCE_DIR}/bin")
message(STATUS "Install dir set as ${EXECUTABLE_DIR}")


## Add subdirs
add_subdirectory(imgui)

## Set SRC_SOURCES to be all .cpp files in current dir
file(GLOB SRC_SOURCES "*.cpp" "*.c")

add_executable(${EXECUTABLE_NAME}
               ${SRC_SOURCES})


## Setting up SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

message(STATUS "SDL dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL LIB: ${SDL2_LIBRARIES}")

IF (WIN32)
    # Linking
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
        ${SDL2_LIBRARIES}           # SDL libraries
        ssp                         # Stack smashing protector library, not in libc for mingw, has to be linked here
    )

ELSE()
    ## Implement Linux build
    message(ERROR "NO BUILD TARGET FOR NON WIN32 SYSTEMS")
ENDIF()

## Check if our install path exists, if not create it
if (EXISTS "${EXECUTABLE_DIR}")
    message("Install path '${EXECUTABLE_DIR}' exists.")
else()
    message("Install path '${EXECUTABLE_DIR}' does not exist.")
    file(MAKE_DIRECTORY ${EXECUTABLE_DIR})
    message("Created '${EXECUTABLE_DIR}'")
endif()


## Install 
INSTALL(TARGETS ${EXECUTABLE_NAME}
    DESTINATION ${EXECUTABLE_DIR}
)

## Custom commands

add_custom_target(run
    COMMAND ${EXECUTABLE_NAME}
    DEPENDS ${EXECUTABLE_NAME}
    WORKING_DIRECTORY ${EXECUTABLE_DIR}  # Set the working directory to where your executable is located
    COMMENT "Running ${EXECUTABLE_NAME}"
)