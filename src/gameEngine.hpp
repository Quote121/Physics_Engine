#pragma once

#include "renderer/renderer.hpp"
#include <memory>

class GameEngine
{
private:
    Renderer* m_renderTarget;

public:
    void SetCurrentRenderTarget(Renderer* renderer);
    Renderer* GetCurrentRenderTarget();
    void Init();
    void GameLoop();
};