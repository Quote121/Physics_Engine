#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

class IComponent
{
protected:
    ~IComponent() = default;
};


// 3D space component
class PositionComponent : public IComponent
{
public:
    glm::f32quat rotation = glm::f32quat(glm::vec3{0.0f, 0.0f, 0.0f});
    glm::vec3 position = {0,0,0};
};



class ScaleComponent : public IComponent
{
public:
    glm::vec3 scale = glm::vec3{1.0f, 1.0f, 1.0f};
    float scalarScale = 1.0f;
};


// Even make sence???
class RendererComponent : public IComponent
{

};



class MaterialComponent : public IComponent
{
    // various material values/maps
};
