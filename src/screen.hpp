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
    /// @brief Initalize and startup SDL
    /// @return Bool - success
    static bool s_Initalize(void);

    /// @brief Update the openGL viewport to the current SDL screen
    /// @todo Move this code to the renderer as all opengl specific calls should
    /// be in the renderer
    static void s_UpdateViewPort(void);

    /// @brief Swap the current frame with the one currently being renderered
    static void s_SwapWindow(void) noexcept;

    /// @brief Clear screen, colour, depth bits
    /// @param colour to set the screen on a clear
    static void s_ClearColour(const glm::vec3& colour);

    /// @brief Set the s_quit flag to false, indicating a shutdown
    static void s_Shutdown(void);

    /// @brief Cleaning up the SDL,OpenGL context and quiting
    static void s_CleanUp(void);

    /// @brief Get the quit flag
    /// @return Bool - quit
    static bool s_GetQuitStatus(void);
};
