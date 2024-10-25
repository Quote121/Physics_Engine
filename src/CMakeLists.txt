message(STATUS "Running src/ cmake")

## Set executable name and path
set(EXECUTABLE_NAME "physicsMain")
message(STATUS "Name set as ${EXECUTABLE_NAME}")

set(EXECUTABLE_INSTALL_DIR ".")
message(STATUS "Install dir set as ${EXECUTABLE_INSTALL_DIR}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

## Add subdirs
add_subdirectory(imgui)

## All includes are done relative to 
include_directories("${CMAKE_SOURCE_DIR}/src")

## Check if the variable is passed in terminal, if so apply it as compile def
## Everytime this changes the files will be recompiled
if(CONSOLE_LOG_OUTPUT)
    message("CONSOLE_LOG_OUPUT is enabled")
    add_compile_definitions(CONSOLE_LOG_OUTPUT)
else()
    message("CONSOLE_LOG_OUPUT is disabled")
endif()

## Specifically list the source files for compilation
set(SRC_SOURCES
    gameEngine.cpp
    main.cpp
    glad.c
    log.cpp
    screen.cpp
    inputHandler.cpp    
    stb_image.cpp
    time.cpp
    publisher.cpp
)

## All components that are to do with the graphics API interaction
set(RENDERER_SOURCES
    renderer/shader.cpp
    renderer/renderer.cpp
    renderer/indexBuffer.cpp
    renderer/vertexArray.cpp
    renderer/vertexBuffer.cpp
    renderer/vertexBufferLayout.cpp
)

set(OBJECTS_SOURCES
    objects/gameObjects.cpp
)

## ImGui source files
set(IMGUI_SOURCES
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
)


add_executable(${EXECUTABLE_NAME}
               ${SRC_SOURCES}
               ${RENDERER_SOURCES}
               ${OBJECTS_SOURCES}
)

## Install 
INSTALL(TARGETS ${EXECUTABLE_NAME}
    DESTINATION ${EXECUTABLE_INSTALL_DIR}
)

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
