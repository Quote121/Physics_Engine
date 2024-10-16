#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <memory>

// Testing the renderer buffer classes
#define TESTRENDERER
#ifdef TESTRENDERER
#include "renderer/renderer.hpp"
#include "renderer/vertexArray.hpp"
#include "renderer/vertexBuffer.hpp"
#include "renderer/vertexBufferLayout.hpp"
#endif

#include "screen.hpp"
#include "log.hpp"
#include "renderer/shader.hpp"
#include "inputHandler.hpp"

std::unique_ptr<Input> inputHandler;

int main(int argv, char* args[])
{
    Log::Open();
    Screen::s_Initalize();


    inputHandler = std::make_unique<Input>();


    // Example of shader compilation
    Shader shader("./assets/shaders/defaultShader/default.vert", "./assets/shaders/defaultShader/default.frag");
    Shader shader2("./assets/shaders/defaultShader/default.shader");

    Renderer renderer;
    VertexArray VAO;
    VertexBuffer VBO;
    VertexBufferLayout VBL;

    float verts[] = 
    {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    VBL.AddFloat(3);
    VBO.SetData<float>(verts, sizeof(verts));
    VAO.AddBuffer(&VBO, &VBL);

    // SDL_GL_SetSwapInterval(0);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    // Update window
    while (true)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );


    //     static double sampleVal = 0;
    //     sampleVal += deltaTime;
    //     // std::cout << sampleVal << std::endl;
    //     if (1000 < static_cast<Uint64>(sampleVal))
    //    {
    //         sampleVal = 0;
    //         std::cout << SDL_GetPerformanceCounter() << 
    //         " - " << SDL_GetPerformanceFrequency() << 
    //         " - " << deltaTime << 
    //         " - fps : " << 1/deltaTime*1000 << std::endl;
    //     }

        Screen::s_ClearColour({0.2f, 0.0f, 0.4f});

        Screen::s_UpdateViewPort();
        shader2.Use();

        renderer.DrawArrays(&VAO, 3);
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        Screen::s_SwapWindow();

        inputHandler->ReadInputs();

        // Check if screen quit variable is set, if so we need to break out of the game loop and clean up resources
        if (Screen::s_GetQuitStatus())
            break;
    }

    Screen::s_CleanUp();
    return 0;
}
