#include <atomic>
#include <vector>
#include <SDL2/SDL.h>
#include "log.hpp"
#include "screen.hpp"

namespace Input
{
    void ReadInputs(void)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0)
        {
            // OS wants to quit. Such as pressing close button
            if (e.type == SDL_QUIT)
            {
                std::cout << "Quit" << std::endl;
                Screen::s_Shutdown();
            }
            if (e.type == SDL_KEYDOWN)
            {
                // std::cout << "Keydown" << std::endl;
            }
        }

        // Deal with individual key presses
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
        {
            // std::cout << "ESC pressed" << std::endl;
            Screen::s_Shutdown();
        }
        if (state[SDL_SCANCODE_D])
        {
            // std::cout << "D pressed" << std::endl;
        }
    }

    void ProcessInputs(void)
    {

    }
}
