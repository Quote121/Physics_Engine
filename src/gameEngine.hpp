#pragma once

#include "renderer/renderer.hpp"
#include "objects/gameObjects.hpp"

class GameEngine
{
private:
    MeshObject* m_meshObject;
    Renderer* m_renderTarget;
public:
    void SetCurrentRenderTarget(Renderer* renderer);
    Renderer* GetCurrentRenderTarget();
    void Init();
    void GameLoop();
};
