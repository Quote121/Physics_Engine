#include "renderer.hpp"


void Renderer::SetClearScreenColour(const glm::vec3& colour)
{
    backgroundColour = colour;
}

void Renderer::ClearScreen(void)
{
    glClearColor(backgroundColour.x, backgroundColour.y, backgroundColour.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawIndices(const VertexArray* vao, const IndexBuffer* ebo, unsigned int mode)
{
    vao->Bind();
    ebo->Bind();

    glDrawElements(mode, ebo->GetCount(), GL_UNSIGNED_INT, nullptr);

    HandleErrors();
}

void Renderer::DrawArrays(const VertexArray* vao, unsigned int count, unsigned int mode)
{
    vao->Bind();
    glDrawArrays(mode, 0, count);

    HandleErrors();
}
