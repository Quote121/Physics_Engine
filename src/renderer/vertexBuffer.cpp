#include "vertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(void)
{
    // If 0 (not initalized, we generate a value)
    if (!VBO) glGenBuffers(1, &VBO);
}

VertexBuffer::~VertexBuffer(void)
{
    glDeleteBuffers(1, &VBO);
}


void VertexBuffer::CreateBuffer(const unsigned int bytes)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bytes, nullptr, GL_STATIC_DRAW);
}

// Update section of buffer with data
void VertexBuffer::UpdateBuffer(const void* data, const unsigned int offset, const unsigned int sizeBytes)
{
    this->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeBytes, data); 
}


void VertexBuffer::Bind(void) const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void VertexBuffer::Unbind(void) const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
