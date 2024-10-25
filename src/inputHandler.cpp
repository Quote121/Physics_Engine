#include "inputHandler.hpp"
#include "objects/components.hpp"

// Static initalization
InputPublisher* InputPublisher::m_pInstance{nullptr};

void InputPublisher::NotifyAll()
{
    for (auto& s : m_observers)
    {
        s->OnNotify();
    }
}

//
// Will do two things
// Will read sld poll states to check for quits, etc and will handle them
// Will read SDL_GetKeyboardState and send the mapped function over to any observers
//
void InputPublisher::ReadInputs(void)
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
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                std::cout << "ESC pressed." << std::endl;
                Screen::s_Shutdown();
            }
        }
    }

    // Read key inputs
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // For each binding, check if the key is pressed. If so, set the current state and notify
    for (auto& i : keyBindingMap)
    {
        if (state[i.first])
        {
            currentState = static_cast<unsigned int>(i.second);
            NotifyAll();
        }
    }
}
