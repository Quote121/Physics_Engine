#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

#include "screen.hpp"

int main(int argv, char* args[])
{
    Screen::s_Initalize();
    Screen::s_GetGLInfo();

    // Update window
    while (true)
    {
        Screen::s_SwapWindow();

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Screen::s_Input();
        if (Screen::s_GetQuitStatus())
            break;
    }

    Screen::s_Shutdown();
    return 0;
}
