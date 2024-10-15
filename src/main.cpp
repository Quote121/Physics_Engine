#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <memory>

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


    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    float verts[] = 
    {
        1.0f, 0.7f, 0.0f,
        0.0f, -0.4f, 0.0f,
        -0.8f, 0.0f, 0.0f
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
        Screen::s_SwapWindow();

        // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glViewport(10, 10, 1000, 1000);
        shader2.Use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        inputHandler->ReadInputs();

        // Check if screen quit variable is set, if so we need to break out of the game loop and clean up resources
        if (Screen::s_GetQuitStatus())
            break;
    }

    Screen::s_CleanUp();
    return 0;
}
