#pragma once

#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int VAO;
public:
    VertexArray(void);
    ~VertexArray();

    /// @brief Add a vertex buffer and layout to the VAO
    /// @param vb The vertex buffer to bind
    /// @param layout The layout settings to apply
    void AddBuffer(const VertexBuffer* vb, const VertexBufferLayout* layout);

    /// @brief Get the VAO
    /// @return integer representing the VAO
    unsigned int GetVertexArray(void) const;

    /// @brief Bind the vertex array object
    void Bind(void) const;

    /// @brief Unbind the current buffer (set to 0)
    void Unbind(void) const;
};
