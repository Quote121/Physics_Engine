#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexBufferLayout.hpp"

#include "log.hpp"

#define OPENGL
#ifdef OPENGL



class Renderer
{
private:
    
    glm::vec3 backgroundColour;

public:
    Renderer() : backgroundColour(glm::vec3{0.4f, 0.4f, 0.4f}) {};

    /// @brief Handle OpenGL errors
    static void HandleErrors(void);

    /// @brief Set the backround colour, will refersh next clear screen call
    /// @param colour Colour to set
    void SetClearScreenColour(const glm::vec3& colour);

    /// @brief Clear the screen, set the colour and clear col and depth buffer bits
    void ClearScreen(void);

    /// @brief Draw the mesh using index buffers
    /// @param vao Vertex array object
    /// @param ebo Index buffer
    /// @param mode Drawing primative 
    void DrawIndices(const VertexArray* vao, const IndexBuffer* ebo, unsigned int mode = GL_TRIANGLES);

    /// @brief Draw the mesh using regular vertex array
    /// @param vao Vertex array object
    /// @param count Number of primatives to draw
    /// @param mode Drawing primative
    void DrawArrays(const VertexArray* vao, unsigned int count, unsigned int mode = GL_TRIANGLES);

};

#else // Vulkan
#endif // OPENGL