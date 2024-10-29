#pragma once

#include "renderer/renderer.hpp"
#include "objects/gameObjects.hpp"
#include <memory>

class GameEngine
{
private:
    std::shared_ptr<Renderer> m_renderTarget;
    std::shared_ptr<MeshObject> m_meshObject;
public:
    void SetCurrentRenderTarget(std::shared_ptr<Renderer> renderer);
    std::shared_ptr<Renderer> GetCurrentRenderTarget();
    void Init();
    void GameLoop();
};
