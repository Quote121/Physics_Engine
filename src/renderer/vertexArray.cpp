// #include "vertexBuffer.hpp"
#include "vertexArray.hpp"
#include <glad/glad.h>


VertexArray::VertexArray(void)
{
    glGenVertexArrays(1, &VAO);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &VAO);
}


void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout* vbl) 
{
    // Add each vertexBufferLayout to the vertex array
    Bind();
    vb->Bind();
    const auto elements = vbl->GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        auto element = elements[i];

        // If the layout element has a valid layout index, use that. Otherwise just use default index
        int layoutIndex = element.layout;
        if (layoutIndex == -1)
            layoutIndex = i;

        glEnableVertexAttribArray(layoutIndex);
        glVertexAttribPointer(layoutIndex, element.count, element.type, element.normalized, vbl->GetStride(), (void*)(intptr_t)(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

GLuint VertexArray::GetVertexArray(void) const
{
    return VAO;
}

void VertexArray::Bind(void) const
{
    glBindVertexArray(VAO);
}

void VertexArray::Unbind(void) const
{
    glBindVertexArray(0);
}

