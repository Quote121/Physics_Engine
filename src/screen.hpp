#pragma once

#include <SDL2/SDL.h>
#include <ostream>
#include <glm/glm.hpp>

class Screen
{
private:
    static SDL_Window* s_applicationWindow;
    static SDL_GLContext s_openGLContext;
    static bool s_quit;

public:
    static bool s_Initalize(void);

    static void s_UpdateViewPort(void);

    static void s_SwapWindow(void) noexcept;

    static void s_ClearColour(glm::vec3 colour);

    static void s_Shutdown(void);

    static void s_CleanUp(void);

    static void s_Input(void);

    static bool s_GetQuitStatus(void);
};
