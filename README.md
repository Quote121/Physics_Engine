# Physics_Engine
OpenGL graphical application with physics. Using SDL2 and OpenGL.

So far the application is being built on Windows

# Installation

Many of the headers needed are included in the project such as glad, glm, stb_image but SDL2 is not.
To install SDL2 on MinGW like MSYS2 use the following command:

```bash
pacman -S mingw-w64-x86_64-SDL2
```

The cmake will attempt to locate the library and link it.