#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

#include "renderer/renderer.hpp"

class IComponent
{
public:
    IComponent() = default;
    virtual ~IComponent() = default;
    IComponent(const IComponent& component) {}
};


// 3D space component
class PositionComponent : public IComponent
{
public:

    glm::vec3 m_position = {0,0,0};

    PositionComponent(glm::vec3 position)
        : m_position(position) {}    
};

class RotationComponent : public IComponent
{
    // face is -z direction (forwards)
    glm::f32quat m_rotation = glm::f32quat(glm::vec3{0.0f, 0.0f, -1.0f});

    RotationComponent(glm::vec3 rotation)
        : m_rotation(glm::f32quat(glm::vec3(rotation))) {}
};




class ScaleComponent : public IComponent
{
public:
    glm::vec3 scale = glm::vec3{1.0f, 1.0f, 1.0f};
    float scalarScale = 1.0f;
};


// Renderer component contains a renderer, this is to render to the screen
// Cameras have render component as it needs to display to the screen
class RendererComponent : public IComponent
{
private:

public:
    std::shared_ptr<Renderer> renderer;
    RendererComponent()
    {
        renderer = std::make_shared<Renderer>();
    }
};

// Means that an object is waiting on an input
// (keyboard press, mouse movement etc.)
class InputComponent : public IComponent
{
public:

};



class MaterialComponent : public IComponent
{
    // various material values/maps
};
