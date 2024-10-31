#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include <SDL2/SDL.h>

#include "publisher.hpp"
#include "screen.hpp"
#include "log.hpp"

//
// Our keyboard functions, if any of these mapped keys are with one of the actions then we dispactch our 
// notification to all listeneres with the action that has just occured.
//
// SDL keycodes should be mapped to one of these at startup and in a hashmap. This can be done via a config
// file or with a console command similar to that in goldsrc
//
enum class KeyboardActions : unsigned int
{
    Unknown,
    // Example place holder
    Forward,
    Backward,
    Left,
    Right,
    Jump,
    Interact
};

namespace InputHandler
{
    constexpr std::pair<const char*, unsigned int> keyMapping[] = 
    {
        {"a", SDL_SCANCODE_A},
        {"b", SDL_SCANCODE_B},
        {"c", SDL_SCANCODE_C},
        {"d", SDL_SCANCODE_D},
        {"e", SDL_SCANCODE_E},
        {"f", SDL_SCANCODE_F},
        {"g", SDL_SCANCODE_G},
        {"h", SDL_SCANCODE_H},
        {"i", SDL_SCANCODE_I},
        {"j", SDL_SCANCODE_J},
        {"k", SDL_SCANCODE_K},
        {"l", SDL_SCANCODE_L},
        {"m", SDL_SCANCODE_M},
        {"n", SDL_SCANCODE_N},
        {"o", SDL_SCANCODE_O},
        {"p", SDL_SCANCODE_P},
        {"q", SDL_SCANCODE_Q},
        {"r", SDL_SCANCODE_R},
        {"s", SDL_SCANCODE_S},
        {"t", SDL_SCANCODE_T},
        {"u", SDL_SCANCODE_U},
        {"v", SDL_SCANCODE_V},
        {"w", SDL_SCANCODE_W},
        {"x", SDL_SCANCODE_X},
        {"y", SDL_SCANCODE_Y},
        {"z", SDL_SCANCODE_Z},
        {"1", SDL_SCANCODE_1},
        {"2", SDL_SCANCODE_2},
        {"3", SDL_SCANCODE_3},
        {"4", SDL_SCANCODE_4},
        {"5", SDL_SCANCODE_5},
        {"6", SDL_SCANCODE_6},
        {"7", SDL_SCANCODE_7},
        {"8", SDL_SCANCODE_8},
        {"9", SDL_SCANCODE_9},
        {"0", SDL_SCANCODE_0},
        {"return", SDL_SCANCODE_RETURN},
        // {"escape", SDL_SCANCODE_ESCAPE}, // Reserved menu key
        {"backspace", SDL_SCANCODE_BACKSPACE},
        {"tab", SDL_SCANCODE_TAB},
        {"space", SDL_SCANCODE_SPACE},
        {"-", SDL_SCANCODE_MINUS},
        {"=", SDL_SCANCODE_EQUALS},
        {"\\", SDL_SCANCODE_BACKSLASH},
        {";", SDL_SCANCODE_SEMICOLON},
        {"'", SDL_SCANCODE_APOSTROPHE},
        {"`", SDL_SCANCODE_GRAVE},
        {",", SDL_SCANCODE_COMMA},
        {".", SDL_SCANCODE_PERIOD},
        {"/", SDL_SCANCODE_SLASH},
        {"f1", SDL_SCANCODE_F1},
        {"f2", SDL_SCANCODE_F2},
        {"f3", SDL_SCANCODE_F3},
        {"f4", SDL_SCANCODE_F4},
        {"f5", SDL_SCANCODE_F5},
        {"f6", SDL_SCANCODE_F6},
        {"f7", SDL_SCANCODE_F7},
        {"f8", SDL_SCANCODE_F8},
        {"f9", SDL_SCANCODE_F9},
        {"f10", SDL_SCANCODE_F10},
        {"f11", SDL_SCANCODE_F11},
        {"f12", SDL_SCANCODE_F12},
        {"pause", SDL_SCANCODE_PAUSE},
        {"insert", SDL_SCANCODE_INSERT},
        {"home", SDL_SCANCODE_HOME},
        {"pageup", SDL_SCANCODE_PAGEUP},
        {"delete", SDL_SCANCODE_DELETE},
        {"end", SDL_SCANCODE_END},
        {"pagedown", SDL_SCANCODE_PAGEDOWN},
        {"right", SDL_SCANCODE_RIGHT},
        {"left", SDL_SCANCODE_LEFT},
        {"down", SDL_SCANCODE_DOWN},
        {"up", SDL_SCANCODE_UP},
        {"*", SDL_SCANCODE_KP_MULTIPLY},
        {"-", SDL_SCANCODE_KP_MINUS},
        {"+", SDL_SCANCODE_KP_PLUS},
        {"ctrl", SDL_SCANCODE_LCTRL},
        {"shift", SDL_SCANCODE_LSHIFT},
        {"alt", SDL_SCANCODE_LALT}
    };

    constexpr std::pair<const char*, KeyboardActions> actionMapping[] = 
    {
        {"forward", KeyboardActions::Forward},
        {"backward", KeyboardActions::Backward},
        {"left", KeyboardActions::Left},
        {"right", KeyboardActions::Right},
        {"jump", KeyboardActions::Jump},
        {"interact", KeyboardActions::Interact}
    };
}



// Singleton input handler publisher
class InputPublisher : public IPublisher
{
private:
    // For mappind SDL scan codes to our keyboard Actions
    // TODO not hardcode and load from a config file
    std::unordered_map<unsigned int, KeyboardActions> keyBindingMap{};

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

    void AddBinding(unsigned int keyScanCode, KeyboardActions keyboardAction)
    {
        keyBindingMap.insert_or_assign(keyScanCode, keyboardAction);
    }

    bool RemoveBinding(unsigned int keyScanCode)
    {
        auto itr = keyBindingMap.find(keyScanCode);
        if (itr != keyBindingMap.end())
        {
            keyBindingMap.erase(itr);
            return true;
        }
        return false;
    }


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
