#pragma once

#include "renderer/renderer.hpp"
#include <memory>

class GameEngine
{
private:
    std::shared_ptr<Renderer> m_renderTarget;

public:
    void SetCurrentRenderTarget(std::shared_ptr<Renderer> renderer);
    std::shared_ptr<Renderer> GetCurrentRenderTarget();
    void Init();
    void GameLoop();
};