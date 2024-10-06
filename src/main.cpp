#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

#include "screen.hpp"
#include "log.hpp"
#include "renderer/shader.hpp"

int main(int argv, char* args[])
{
    Log::Open();
    Screen::s_Initalize();

    // Example of shader compilation
    Shader shader("./assets/shaders/defaultShader/default.vert", "./assets/shaders/defaultShader/default.frag");
    Shader shader2("./assets/shaders/defaultShader/default.shader");

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
