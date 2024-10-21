#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "components.hpp"


enum class GameObjectType {
    MESHOBJECT,
    SPRITEOBJECT,
    CAMERAOBJECT
};

// Mesh object - 3d object from .obj
// Sprite object - 2d sprite from image file

// Future?
// Light object - point/directional
// Camera object - player and cinematic
//      Render - screenspace
//      Update - any player inputs or cinematic track position
// UI object - UI assets like health bars
//      Render - Display information
//      Update - update the values they have/animation
// DecalObject - Projected textures such as bullet holes/blood
// ParticleObject

// General game object interface
class IGameObject
{
private:
    using ComponentID = std::size_t;

    // Map of all components, indexed by a hash of their type
    std::unordered_map<ComponentID, std::shared_ptr<IComponent>> componentMap;

protected:
    // Display to the screen
    // Find which renderer to pass draw calls to
    // i.e. if we have 3 cameras, get the active camera's renderer and make your call
    virtual void Render() = 0;

    // Update any components of the objects such as physics elements
    virtual void Update() = 0;

    // Component based methods
    template<typename T>
    void AddComponent(const T& component)
    {
        componentMap[typeid(T).hash_code()] = component;
    }

    template<typename T>
    void AddComponent(const T&& component)
    {
        componentMap[typeid(T).hash_code()] = std::make_shared<IComponent>(component);
    }

    // Default type constructor
    template<typename T>
    void AddComponent(void)
    {
        componentMap[typeid(T).hash_code()] = std::make_shared<T>();
    }

    template<typename T>
    void RemoveComponent()
    {
        auto index = componentMap.find(typeid(T).hash_code());
        if (index != componentMap.end())
        {
            componentMap.erase(index);
        }
    }

public:
    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        auto index = componentMap.find(typeid(T).hash_code());
        if (index != componentMap.end())
        {
            return std::dynamic_pointer_cast<T>(index->second);
        }
        return nullptr;
    }
};



// Singleton IGameObjectFactory
// Extensable factory, we can keep adding methods as long as they have the Create() method
class GameObjectFactory
{
    using GameObjectCallback = std::shared_ptr<IGameObject> (*)();
    using factoryCallBackMap = std::unordered_map<GameObjectType, GameObjectCallback>;

private:
    static factoryCallBackMap callbackMap;

public:
    static void RegisterObject(const GameObjectType type, GameObjectCallback cb)
    {
        callbackMap[type] = cb;
    }

    static void UnRegisterObject(const GameObjectType type)
    {
        callbackMap.erase(type);
    }

    static std::shared_ptr<IGameObject> CreateObject(const GameObjectType type)
    {
        const auto& entry = callbackMap.find(type);
        if (entry != callbackMap.end())
        {
            return (entry->second)(); 
        }
        return nullptr;
    }
};

// Example object becuase I cant think rn
class MeshObject : public IGameObject
{
private:

public:
    void Render() {}
    void Update() {}

    void MeshPrint() {}

    // Call back function for factory
    static std::shared_ptr<IGameObject> Create()
    {
        return std::make_shared<MeshObject>();
    }
};

constexpr float fov = 45.0f;
constexpr float nearPlane = 0.1f;
constexpr float farPlane = 10000.0f;
constexpr float aspectRadio = 16.0f/9.0f;

class CameraObject : public IGameObject
{
private:
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    const glm::vec3 m_worldSpaceUp{0.0f, 1.0f, 0.0f};

    // Euler angles instead of quat component
    float m_yaw;
    float m_pitch;


    void UpdateCameraVectors(void)
    {
        // If our pitch exceeds the top or bottom, make sure we stop it from reversing
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        m_front.x = glm::cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y = glm::sin(glm::radians(m_pitch));
        m_front.z = glm::sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        // Then we get the new right and up vectors
        m_right = glm::normalize(glm::cross(m_front, m_worldSpaceUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }


public:
    // Cant access constructor so that we can only construct through create()
    // Constructor adds a position component
    CameraObject(glm::vec3 position = {0,0,0})
        : m_yaw(0.0f), m_pitch(0.0f)
    {
        std::cout << "CAM CONSTRUCT\n";
        // Construct component with non-default data
        this->AddComponent(PositionComponent(position));
        
        // Construct component with default data and constructor
        this->AddComponent<RendererComponent>();
    }

    inline glm::mat4 GetViewMatrix(void)
    {
        glm::vec3 pos = this->GetComponent<PositionComponent>()->m_position;
        return glm::lookAt(pos, pos + m_front, m_up);
    }

    inline glm::mat4 GetProjectionMatrix(void) const
    {
        return glm::perspective(glm::radians(45.0f), aspectRadio, nearPlane, farPlane);
    }

    // Updating viewspacing etc.
    //
    // All objects that need to be rendererd will check every available renderer
    // for which one is currently being used. And therefore which camera
    void Render() 
    {

    }

    void Update() 
    {
        // Update view matrix based on camera position
        UpdateCameraVectors();
    }

    static std::shared_ptr<IGameObject> Create()
    {
        return std::make_shared<CameraObject>();
    }
};
