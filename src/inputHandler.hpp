#pragma once

#include <memory>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "publisher.hpp"
#include "screen.hpp"

//
// Our keyboard functions, if any of these mapped keys are with one of the actions then we dispactch our 
// notification to all listeneres with the action that has just occured.
//
// SDL keycodes should be mapped to one of these at startup and in a hashmap. This can be done via a config
// file or with a console command similar to that in goldsrc
//
enum class KeyboardActions : unsigned int
{
    // Example place holder
    Forward,
    Backwards,
    Left,
    Right,
    Jump,
    Interact
};

// Singleton input handler publisher
class InputPublisher : public IPublisher
{
private:
    // For mappind SDL scan codes to our keyboard Actions
    // TODO not hardcode and load from a config file
    std::unordered_map<SDL_Scancode, KeyboardActions> keyBindingMap = 
    {
        {SDL_SCANCODE_W, KeyboardActions::Forward},
        {SDL_SCANCODE_A, KeyboardActions::Left},
        {SDL_SCANCODE_S, KeyboardActions::Backwards},
        {SDL_SCANCODE_D, KeyboardActions::Right},
        {SDL_SCANCODE_E, KeyboardActions::Interact}
    };

    static InputPublisher* m_pInstance;

    unsigned int currentState;

    void NotifyAll() override;


    // Singleton
    InputPublisher(InputPublisher&) = delete;
    void operator=(const InputPublisher&) = delete;
    InputPublisher() = default;
    ~InputPublisher()
    {
        delete m_pInstance;
    }

public:
    unsigned int GetState()
    {
        return currentState;
    }

    static InputPublisher* GetInstance()
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new InputPublisher();
        }
        return m_pInstance;
    }

    //
    // Will do two things
    // Will read sld poll states to check for quits, etc and will handle them
    // Will read SDL_GetKeyboardState and send the mapped function over to any observers
    //
    void ReadInputs(void);
};
