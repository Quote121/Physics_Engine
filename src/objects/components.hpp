#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

#include "renderer/renderer.hpp"
#include "inputHandler.hpp"

class IComponent
{
public:
    IComponent() = default;
    virtual ~IComponent() = default;
    IComponent(const IComponent& component) {}
};


class IEventObserver
{
public:
    // When an event fires
    virtual void OnNotify() = 0;
    
    // To subscribe to the subject
    virtual void Register() = 0;
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
    std::unique_ptr<Renderer> renderer;
public:
    RendererComponent()
    {
        renderer = std::make_unique<Renderer>();
    }
    Renderer* GetRenderer()
    {
        return renderer.get();
    }
};


// Means that an object is waiting on an input
// (keyboard press, mouse movement etc.)
template<typename T>
class KeyBoardEventComponent : public IEventObserver, public IComponent,
                               public std::enable_shared_from_this<KeyBoardEventComponent<T>>
{
    using KeyboardCallback = void (T::*)(unsigned int);
private:
    T* m_pCallbackObject;
    KeyboardCallback m_pCallbackMethod;

public:
    // Register the callback function when OnNotify is called
    KeyBoardEventComponent(T* object, KeyboardCallback callback)
        : m_pCallbackObject(object), m_pCallbackMethod(callback)
    {}

    void Register() override
    {
        InputPublisher::GetInstance()->AddObserver(this);
    }
    
    // When a keyboard event fires
    void OnNotify() override
    {
        // Get publisher state info
        unsigned int keyCode = InputPublisher::GetInstance()->GetState();

        // Dereference our function pointer and call
        (m_pCallbackObject->*m_pCallbackMethod)(keyCode);
    }
};


class MaterialComponent : public IComponent
{
    // various material values/maps
};
