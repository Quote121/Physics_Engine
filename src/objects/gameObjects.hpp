#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "components.hpp"
#include "renderer/vertexArray.hpp"
#include "objectLoader.hpp"

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

// Forward decl
class CameraObject;
class MeshObject;

// General game object interface
class IGameObject
{
private:
    using ComponentID = std::size_t;

    // Map of all components, indexed by a hash of their type
    std::unordered_map<ComponentID, std::unique_ptr<IComponent>> componentMap;

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
    T* AddComponent(const T&& component)
    {
        componentMap[typeid(T).hash_code()] = std::make_unique<T>(std::forward<const T>(component));
        return this->GetComponent<T>();
    }

    // Default type constructor
    template<typename T>
    void AddComponent(void)
    {
        componentMap[typeid(T).hash_code()] = std::make_unique<T>();
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
    T* GetComponent()
    {
        auto index = componentMap.find(typeid(T).hash_code());
        if (index != componentMap.end())
        {
            // Compile time pointer cast
            return dynamic_cast<T*>(index->second.get());
        }
        Log::Write("GetComponent", "Warning, map miss, returning nullptr.");
        return nullptr;
    }
};




// Singleton IGameObjectFactory
// Extensable factory, we can keep adding methods as long as they have the Create() method
class GameObjectFactory
{
    using GameObjectCallback = IGameObject* (*)();
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

    static IGameObject* CreateObject(const GameObjectType type)
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
public:
    // Mesh data
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    // Texture data
    std::vector<float> m_textureCoords;
    std::vector<unsigned int> m_textureIndices;

    // Normal data
    std::vector<float> m_normals;
    std::vector<unsigned int> m_normalIndices;


    void Render() {}
    void Update() {}

    void MeshPrint() {}
    VertexArray m_VAO;
    VertexBuffer m_VBO;

    MeshObject(glm::vec3 position = {0,0,0}, const char* objFile = nullptr)
    {
        // Construct component with non-default data
        this->AddComponent(PositionComponent(position));
        //this->AddComponent(RotationComponent({0, 0, 0})); for some reason this doesnt work?
        this->AddComponent(ScaleComponent());

        // if(objFile)
        // {
        //     // Load obj file
        //     // LoadMesh(objFile);
        //     ObjectLoader::LoadMesh(objFile, this);
        // }

        // Construct component with default data and constructor
        this->AddComponent<RendererComponent>();
    }
    // Call back function for factory
    static IGameObject* Create()
    {
        // TODO have object handler
        return new MeshObject();
    }
};


////////////////////////////////
//                            //
//        CameraObject        //
//                            //
////////////////////////////////

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
        // Construct component with non-default data
        this->AddComponent(PositionComponent(position));

        // Construct component with default data and constructor
        this->AddComponent<RendererComponent>();

        // Add a keyboard event listener that uses this->KeyboardCallback to execute any keyboard events
        // We then also have to register it once its been allocated
        this->AddComponent(KeyBoardEventComponent<CameraObject>(this, &KeyboardCallback))->Register();
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

    // The keyboard callback method to process inputs for us
    void KeyboardCallback(unsigned int keyCode)
    {
        Log::Write("KeyboardCallback", "Keypressed: ", keyCode);
    }


    static IGameObject* Create()
    {
        // TODO have object handler
        return new CameraObject();
    }
};
