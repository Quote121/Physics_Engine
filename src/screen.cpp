#include "screen.hpp"
#include "log.hpp"

#include <glad/glad.h>
#include <sstream>
#include <iostream>
#include <cstring>




// Constants
constexpr int winHeight = 720;
constexpr int winWidth = 1280;
constexpr Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

// Define static variables
SDL_Window* Screen::s_applicationWindow = nullptr;
SDL_GLContext Screen::s_openGLContext = nullptr;
bool Screen::s_quit = false;

bool Screen::s_Initalize(void)
{
    // Log file started at top of file
    std::time_t now = std::time(nullptr);

    char fileNameBuffer[128];
    std::memset(fileNameBuffer, 0, sizeof(fileNameBuffer));

    // e.g. Sun Oct 17 04:41:13 2010
    std::strftime(fileNameBuffer, sizeof(fileNameBuffer), "Log file started at %a %d %b %H:%M:%S %Y", std::localtime(&now));
    fileNameBuffer[std::strlen(fileNameBuffer)] = '\n';

    // Recalculate the string length and write the correct number of bytes
    Log::Write(fileNameBuffer, std::strlen(fileNameBuffer));


    Log::Write("SDL init", "Started");
    auto SDLinitStartTime = Log::GetTimePointNow();

    // Init sdl
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cout << "Error init: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);  // Non-deprecated functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);                                     // 24 bits

    // Create window and check if succeeded
    s_applicationWindow = SDL_CreateWindow("Physics project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, windowFlags);
    if (!s_applicationWindow)
    {
        std::cout << "Error createWindow: " << SDL_GetError() << std::endl;
        return false;
    }

    s_openGLContext = SDL_GL_CreateContext(s_applicationWindow);
    if (!s_openGLContext)
    {
        std::cout << "Error createContext: " << SDL_GetError() << std::endl;
        return false;
    }

    // Init glad
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Error glad was not initalized." << std::endl;
        return false;
    }

    std::stringstream ssInfo;
    ssInfo << "-----------------------------------------------------\n";
    ssInfo << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    ssInfo << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    ssInfo << "Version: " << glGetString(GL_VERSION) << "\n";
    ssInfo << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    ssInfo << "-----------------------------------------------------\n";
    Log::Write(ssInfo.str().c_str(), ssInfo.str().size());

    Log::Write("SDL init", "Took ", Log::GetTimeElapsedString(SDLinitStartTime), " to start SDL.");
    return true;
}

void Screen::s_UpdateViewPort(void)
{
    // SDL_assert()
    int width, height;
    SDL_GetWindowSize(s_applicationWindow, &width, &height);
    // SDL_DisplayMode DM;
    // SDL_GetCurrentDisplayMode(0, &DM);
    glViewport(0, 0, width, height);
}

void Screen::s_SwapWindow(void) noexcept
{
    SDL_GL_SwapWindow(s_applicationWindow);
}

void Screen::s_ClearColour(const glm::vec3& colour)
{
    glClearColor(colour.x, colour.y, colour.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::s_Shutdown(void)
{
    s_quit = true;
}


void Screen::s_CleanUp(void)
{
    SDL_DestroyWindow(s_applicationWindow);
    SDL_GL_DeleteContext(s_openGLContext);
    SDL_Quit();
}


void Screen::s_Input(void)
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        // OS wants to quit. Such as pressing close button
        if (e.type == SDL_QUIT)
        {
            std::cout << "Quit" << std::endl;
            s_quit = true;
        }
        if (e.type == SDL_KEYDOWN)
        {
            std::cout << "Keydown" << std::endl;
        }
    }

    // Deal with individual key presses
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        std::cout << "ESC pressed" << std::endl;
        s_quit = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        std::cout << "D pressed" << std::endl;
    }
}

bool Screen::s_GetQuitStatus(void)
{
    return s_quit;
}
