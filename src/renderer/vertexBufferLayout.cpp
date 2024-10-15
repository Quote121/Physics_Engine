#include "vertexBufferLayout.hpp"

#include <glad/glad.h>
#include <stdexcept>

// Inspired from the Cherno : https://www.youtube.com/@TheCherno
unsigned int VertexBufferElement::GetSizeOfType(const unsigned int type)
{
    switch(type)
    {
        case GL_FLOAT         : return sizeof(GLfloat);
        case GL_UNSIGNED_INT  : return sizeof(GLuint);
        case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
    }
    throw std::runtime_error("Invalid type passed.");
    return 0;
}


void VertexBufferLayout::Push(unsigned int type, unsigned int count, unsigned char normalized, int location)
{
    VertexBufferElement vbe = {type, count, normalized, location};
    elementVector.push_back(vbe);
    stride += count * VertexBufferElement::GetSizeOfType(type);
}


VertexBufferLayout::VertexBufferLayout() : stride(0) {}

// All add types
void VertexBufferLayout::AddFloat(unsigned int count, int location)        { Push(GL_FLOAT, count, GL_FALSE, location);        }
void VertexBufferLayout::AddUnsignedInt(unsigned int count, int location)  { Push(GL_UNSIGNED_INT, count, GL_FALSE, location); }
void VertexBufferLayout::AddUnsignedByte(unsigned int count, int location) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE, location); }


const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const 
{
    return elementVector;
}


unsigned int VertexBufferLayout::GetStride() const 
{
    return stride;
}

